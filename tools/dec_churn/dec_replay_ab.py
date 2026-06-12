#!/usr/bin/env python3
"""dec_replay_ab.py — A/B replay of two explicit DEC variants with churn + blended-entry latency.

Extends tools/dec_replay_swarm/dec_replay.py for the x9k churn study. Differences vs the original:

  1. BOTH dec.py paths are explicit argv (the original hardcodes the baseline to the on-device
     /data/openpilot copy, which on this device is one commit BEHIND a6eae7b). For x9k the baseline
     MUST be a6eae7b, so we pass it explicitly.
  2. Adds a blended-entry LATENCY metric: for every contiguous blended interval the BASELINE enters,
     measure how many frames later the PATCHED variant first reaches blended within a match window.
     Reports p50/p95/max lag in frames and the count of baseline blended-entries the patched variant
     MISSED entirely (never entered blended within the window) — this is the genuine-braking-delay guard.
  3. Reports divergent-frame direction split (baseline=acc/patched=blended vs baseline=blended/patched=acc).

The replay driving cadence, cross-segment continuity, stubs, and capnp parsing are byte-faithful to the
original (same C1/C2/C3 guarantees). Output is a single JSON object to stdout; progress to stderr.

Usage: dec_replay_ab.py <ROUTE_PREFIX> <BASELINE_DEC_PATH> <PATCHED_DEC_PATH> [SEGMENTS_CSV]
"""
import sys, os, io, json, importlib, importlib.util
import zstandard, capnp

capnp.remove_import_hook()
LOG = capnp.load("/data/openpilot/cereal/log.capnp")

def eprint(*a, **kw):
    print(*a, file=sys.stderr, **kw)

def load_dec(path, modname):
    spec = importlib.util.spec_from_file_location(modname, path)
    mod = importlib.util.module_from_spec(spec)
    sys.modules[modname] = mod
    spec.loader.exec_module(mod)
    return mod.DynamicExperimentalController

class CPStub:
    def __init__(self, radar_unavailable=False):
        self.radarUnavailable = radar_unavailable

class MpcStub:
    def __init__(self):
        self.crash_cnt = 0

class ParamsStub:
    def get_bool(self, name):
        return True
    def get(self, name, *a, **kw):
        return b""
    def get_int(self, name):
        return 0

def normalize_mode(m):
    s = str(m).lower().strip()
    if 'blend' in s:
        return 'blended'
    if 'acc' in s:
        return 'acc'
    return s

def parse_segment(path):
    try:
        raw = open(path, "rb").read()
        data = zstandard.ZstdDecompressor().stream_reader(io.BytesIO(raw)).read()
    except Exception as e:
        eprint(f"  Decompression failed for {path}: {e}")
        return None
    events = []
    try:
        for ev in LOG.Event.read_multiple_bytes(data):
            events.append(ev)
    except Exception as e:
        eprint(f"  Partial parse of {path}: {e} ({len(events)} events read)")
    return events

def find_car_params(route_prefix, segments):
    for seg_idx in segments:
        path = f"{route_prefix}--{seg_idx}/rlog.zst"
        if not os.path.exists(path):
            continue
        events = parse_segment(path)
        if events is None:
            continue
        for ev in events:
            try:
                if ev.which() == 'carParams':
                    return bool(ev.carParams.radarUnavailable)
            except Exception:
                pass
    return None

def compute_metrics(modes_list):
    n = len(modes_list)
    if n == 0:
        return {
            "total_frames": 0, "transitions": 0, "worst_minute_transitions": 0,
            "max_consecutive_flip_run": 0,
            "time_in_mode": {"acc": 0.0, "blended": 0.0},
            "per_segment_transitions": [],
        }
    transitions = 0
    transition_times = []
    is_flip = [False] * n
    for i in range(1, n):
        if modes_list[i][1] != modes_list[i-1][1]:
            transitions += 1
            transition_times.append(modes_list[i][0])
            is_flip[i] = True

    worst_minute = 0
    if transition_times:
        j = 0
        for i in range(len(transition_times)):
            if j < i:
                j = i
            while j < len(transition_times) and transition_times[j] - transition_times[i] <= 60.0:
                j += 1
            count = j - i
            if count > worst_minute:
                worst_minute = count

    max_flip_run = 0
    current_run = 0
    for i in range(1, n):
        if is_flip[i]:
            current_run += 1
            if current_run > max_flip_run:
                max_flip_run = current_run
        else:
            current_run = 0

    time_in_mode = {"acc": 0.0, "blended": 0.0}
    for i in range(n - 1):
        dt = modes_list[i+1][0] - modes_list[i][0]
        dt = max(0.0, min(dt, 0.5))
        mode = modes_list[i][1]
        if mode in time_in_mode:
            time_in_mode[mode] += dt

    seg_trans = {}
    for i in range(1, n):
        if modes_list[i][1] != modes_list[i-1][1]:
            seg = modes_list[i][2]
            seg_trans[seg] = seg_trans.get(seg, 0) + 1
    per_segment_transitions = sorted([[s, c] for s, c in seg_trans.items()])

    return {
        "total_frames": n,
        "transitions": transitions,
        "worst_minute_transitions": worst_minute,
        "max_consecutive_flip_run": max_flip_run,
        "time_in_mode": {k: round(v, 2) for k, v in time_in_mode.items()},
        "per_segment_transitions": per_segment_transitions,
    }

def percentile(sorted_vals, pct):
    if not sorted_vals:
        return None
    if len(sorted_vals) == 1:
        return sorted_vals[0]
    k = (len(sorted_vals) - 1) * pct
    f = int(k)
    c = min(f + 1, len(sorted_vals) - 1)
    if f == c:
        return float(sorted_vals[f])
    return float(sorted_vals[f] + (sorted_vals[c] - sorted_vals[f]) * (k - f))

def blended_entry_latency(base_modes, patch_modes, match_window_frames=40):
    """For each frame where BASELINE *enters* blended (acc->blended), find how many frames later the
    PATCHED variant first shows blended within [0, match_window_frames]. Frames are the index in the
    aligned per-modelV2 sequence (DT_MDL=0.05s, so 1 frame = 0.05s; 10 frames = 0.5s). If patched never
    reaches blended within the window, count it as a MISS (genuine braking entry the candidate dropped).
    Only entries with a clean preceding acc frame are considered (true onset, not stream start)."""
    n = len(base_modes)
    lags = []
    misses = 0
    entries = 0
    for i in range(1, n):
        if base_modes[i][1] == 'blended' and base_modes[i-1][1] == 'acc':
            entries += 1
            found = None
            hi = min(n, i + match_window_frames + 1)
            for j in range(i, hi):
                if patch_modes[j][1] == 'blended':
                    found = j - i
                    break
            if found is None:
                misses += 1
            else:
                lags.append(found)
    lags_sorted = sorted(lags)
    return {
        "baseline_blended_entries": entries,
        "patched_matched_entries": len(lags),
        "patched_missed_entries": misses,
        "match_window_frames": match_window_frames,
        "lag_frames_p50": percentile(lags_sorted, 0.50),
        "lag_frames_p95": percentile(lags_sorted, 0.95),
        "lag_frames_max": (lags_sorted[-1] if lags_sorted else None),
        "lag_frames_mean": (round(sum(lags) / len(lags), 2) if lags else None),
    }

def divergence(base_modes, patch_modes):
    n = len(base_modes)
    diverged = 0
    base_acc_patch_blended = 0  # patched MORE blended (held longer / entered earlier)
    base_blended_patch_acc = 0  # patched LESS blended (dropped / delayed)
    for i in range(n):
        if base_modes[i][1] != patch_modes[i][1]:
            diverged += 1
            if base_modes[i][1] == 'acc' and patch_modes[i][1] == 'blended':
                base_acc_patch_blended += 1
            elif base_modes[i][1] == 'blended' and patch_modes[i][1] == 'acc':
                base_blended_patch_acc += 1
    return {
        "frames_diverged": diverged,
        "base_acc_patch_blended": base_acc_patch_blended,
        "base_blended_patch_acc": base_blended_patch_acc,
        "pct_diverged": round(100.0 * diverged / n, 3) if n else 0.0,
    }

def main():
    if len(sys.argv) < 4:
        eprint("Usage: dec_replay_ab.py <ROUTE_PREFIX> <BASELINE_DEC_PATH> <PATCHED_DEC_PATH> [SEGMENTS_CSV]")
        sys.exit(1)

    route_prefix = sys.argv[1]
    baseline_path = sys.argv[2]
    patched_dec_path = sys.argv[3]

    if len(sys.argv) >= 5:
        segments = [int(x.strip()) for x in sys.argv[4].split(",") if x.strip()]
    else:
        segments = list(range(19))

    eprint(f"Route: {route_prefix}")
    eprint(f"Baseline DEC: {baseline_path}")
    eprint(f"Patched DEC: {patched_dec_path}")
    eprint(f"Segments: {segments}")

    eprint("Pre-scanning for carParams...")
    radar_unavail = find_car_params(route_prefix, segments)
    if radar_unavail is None:
        radar_unavail = False
        cp_source = "default (not found in route)"
    else:
        cp_source = "from carParams event in route"
    eprint(f"  radarUnavailable = {radar_unavail} ({cp_source})")

    eprint("Loading baseline DEC...")
    BaseDEC = load_dec(baseline_path, "dec_baseline")
    eprint("Loading patched DEC...")
    PatchDEC = load_dec(patched_dec_path, "dec_patched")

    base_ctrl = BaseDEC(CPStub(radar_unavail), MpcStub(), params=ParamsStub())
    patch_ctrl = PatchDEC(CPStub(radar_unavail), MpcStub(), params=ParamsStub())

    eprint("Starting main replay...")

    latest_carState = None
    latest_radarState = None
    latest_selfdriveState = None

    base_modes = []
    patch_modes = []

    frames_skipped_warmup = 0
    segments_read = []
    segments_failed = []

    for seg_idx in segments:
        path = f"{route_prefix}--{seg_idx}/rlog.zst"
        eprint(f"  Segment {seg_idx}...")

        if not os.path.exists(path):
            eprint(f"    Not found, skipping")
            segments_failed.append(seg_idx)
            continue

        events = parse_segment(path)
        if events is None:
            segments_failed.append(seg_idx)
            continue

        segments_read.append(seg_idx)
        seg_frame_count = 0

        for ev in events:
            try:
                w = ev.which()
            except Exception:
                continue

            if w == 'carState':
                try:
                    latest_carState = ev.carState
                except Exception:
                    pass
            elif w == 'radarState':
                try:
                    latest_radarState = ev.radarState
                except Exception:
                    pass
            elif w == 'selfdriveState':
                try:
                    latest_selfdriveState = ev.selfdriveState
                except Exception:
                    pass
            elif w == 'modelV2':
                if latest_carState is None or latest_radarState is None or latest_selfdriveState is None:
                    frames_skipped_warmup += 1
                    continue

                mono = ev.logMonoTime * 1e-9

                try:
                    modelV2_data = ev.modelV2
                except Exception:
                    continue

                sm = {
                    'carState': latest_carState,
                    'radarState': latest_radarState,
                    'modelV2': modelV2_data,
                    'selfdriveState': latest_selfdriveState,
                }

                try:
                    base_ctrl.update(sm)
                    bm = normalize_mode(base_ctrl.mode())
                except Exception as e:
                    eprint(f"    Base DEC error at seg {seg_idx}: {e}")
                    bm = base_modes[-1][1] if base_modes else 'acc'

                try:
                    patch_ctrl.update(sm)
                    pm = normalize_mode(patch_ctrl.mode())
                except Exception as e:
                    eprint(f"    Patch DEC error at seg {seg_idx}: {e}")
                    pm = patch_modes[-1][1] if patch_modes else 'acc'

                base_modes.append((mono, bm, seg_idx))
                patch_modes.append((mono, pm, seg_idx))
                seg_frame_count += 1

        eprint(f"    {seg_frame_count} modelV2 frames processed")

    total_frames = len(base_modes)
    eprint(f"Total frames: {total_frames}, warmup skipped: {frames_skipped_warmup}")

    base_metrics = compute_metrics(base_modes)
    patch_metrics = compute_metrics(patch_modes)
    latency = blended_entry_latency(base_modes, patch_modes)
    div = divergence(base_modes, patch_modes)

    bt = base_metrics["transitions"]
    pt = patch_metrics["transitions"]
    reduction_pct = round(100.0 * (bt - pt) / bt, 2) if bt > 0 else 0.0

    # time-in-mode shift (blended fraction) baseline vs patched
    b_tim = base_metrics["time_in_mode"]
    p_tim = patch_metrics["time_in_mode"]
    b_total = b_tim["acc"] + b_tim["blended"]
    p_total = p_tim["acc"] + p_tim["blended"]
    b_blended_frac = round(b_tim["blended"] / b_total, 4) if b_total else 0.0
    p_blended_frac = round(p_tim["blended"] / p_total, 4) if p_total else 0.0

    notes = (
        f"mpc.crash_cnt stubbed to 0 (identical for both variants); Params stubbed True; "
        f"CP.radarUnavailable={radar_unavail} ({cp_source}); {frames_skipped_warmup} warmup frames skipped. "
        f"BASELINE path explicit (NOT the on-device hardcode) = {baseline_path}."
    )

    result = {
        "baseline": base_metrics,
        "patched": patch_metrics,
        "blended_entry_latency": latency,
        "divergence": div,
        "summary": {
            "baseline_transitions": bt,
            "patched_transitions": pt,
            "reduction_pct": reduction_pct,
            "baseline_worst_minute": base_metrics["worst_minute_transitions"],
            "patched_worst_minute": patch_metrics["worst_minute_transitions"],
            "baseline_blended_frac": b_blended_frac,
            "patched_blended_frac": p_blended_frac,
            "blended_frac_shift_pct": round(100.0 * (p_blended_frac - b_blended_frac), 3),
            "notes": notes,
        },
        "frames_skipped_warmup": frames_skipped_warmup,
        "segments_read": segments_read,
        "segments_failed": segments_failed,
        "radar_unavailable": radar_unavail,
    }

    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
