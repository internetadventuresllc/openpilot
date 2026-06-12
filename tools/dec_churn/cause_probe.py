#!/usr/bin/env python3
"""Classify each baseline acc<->blended transition by its proximate cause, to see whether the churn
is emergency-driven (untouchable) or non-emergency-hysteresis-suppressible.

Usage: cause_probe.py <ROUTE_PREFIX> <BASELINE_DEC_PATH>
"""
import sys, os, io, json, importlib.util
import zstandard, capnp
capnp.remove_import_hook()
LOG = capnp.load("/data/openpilot/cereal/log.capnp")

def load_dec(path, modname):
    spec = importlib.util.spec_from_file_location(modname, path)
    mod = importlib.util.module_from_spec(spec); sys.modules[modname] = mod
    spec.loader.exec_module(mod); return mod

class CPStub:
    def __init__(self, r=False): self.radarUnavailable = r
class MpcStub:
    def __init__(self): self.crash_cnt = 0
class ParamsStub:
    def get_bool(self, n): return True
    def get(self, n, *a, **k): return b""
    def get_int(self, n): return 0

route = sys.argv[1]; basepath = sys.argv[2]
segs = list(range(19))
mod = load_dec(basepath, "decb")
DEC = mod.DynamicExperimentalController
ctrl = DEC(CPStub(False), MpcStub(), params=ParamsStub())

lc = lr = ls = None
prev_mode = 'acc'
causes = {}
emerg_trans = 0; nonemerg_trans = 0; total_trans = 0

def parse(path):
    raw = open(path, "rb").read()
    data = zstandard.ZstdDecompressor().stream_reader(io.BytesIO(raw)).read()
    evs = []
    try:
        for ev in LOG.Event.read_multiple_bytes(data): evs.append(ev)
    except Exception: pass
    return evs

for s in segs:
    p = f"{route}--{s}/rlog.zst"
    if not os.path.exists(p): continue
    for ev in parse(p):
        try: w = ev.which()
        except Exception: continue
        if w == 'carState': lc = ev.carState
        elif w == 'radarState': lr = ev.radarState
        elif w == 'selfdriveState': ls = ev.selfdriveState
        elif w == 'modelV2':
            if lc is None or lr is None or ls is None: continue
            sm = {'carState': lc, 'radarState': lr, 'modelV2': ev.modelV2, 'selfdriveState': ls}
            ctrl.update(sm)
            m = ctrl.mode(); mm = str(m).lower()
            mm = 'blended' if 'blend' in mm else ('acc' if 'acc' in mm else mm)
            if mm != prev_mode:
                total_trans += 1
                emo = ctrl._mode_manager.emergency_override
                urg = ctrl._urgency
                lead = ctrl._has_lead_filtered
                sd = ctrl._has_slow_down
                if emo: emerg_trans += 1
                else: nonemerg_trans += 1
                key = (mm, 'EMERG' if emo else 'norm', 'urg>0.7' if urg > 0.7 else 'urg<=0.7', f"lead={lead}", f"sd={sd}")
                causes[str(key)] = causes.get(str(key), 0) + 1
                prev_mode = mm

print(json.dumps({
    "total_transitions": total_trans,
    "emergency_override_set_at_transition": emerg_trans,
    "nonemergency_at_transition": nonemerg_trans,
    "cause_breakdown": causes,
}, indent=2))
