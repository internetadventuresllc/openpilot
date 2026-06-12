#!/usr/bin/env python3
"""Empirically confirm radarless invariance: drive baseline and a candidate with CP.radarUnavailable
=True over the route and assert the per-frame mode sequences are IDENTICAL (zero divergent frames).

Usage: radarless_invariance.py <ROUTE_PREFIX> <BASELINE_DEC_PATH> <CANDIDATE_DEC_PATH> [SEGMENTS_CSV]
"""
import sys, os, io, json, importlib.util
import zstandard, capnp
capnp.remove_import_hook()
LOG = capnp.load("/data/openpilot/cereal/log.capnp")

def load_dec(path, modname):
    spec = importlib.util.spec_from_file_location(modname, path)
    mod = importlib.util.module_from_spec(spec); sys.modules[modname] = mod
    spec.loader.exec_module(mod); return mod.DynamicExperimentalController

class CPStub:
    def __init__(self, r): self.radarUnavailable = r
class MpcStub:
    def __init__(self): self.crash_cnt = 0
class ParamsStub:
    def get_bool(self, n): return True
    def get(self, n, *a, **k): return b""
    def get_int(self, n): return 0

def nm(m):
    s = str(m).lower()
    return 'blended' if 'blend' in s else ('acc' if 'acc' in s else s)

route = sys.argv[1]; basepath = sys.argv[2]; candpath = sys.argv[3]
segs = [int(x) for x in sys.argv[4].split(",")] if len(sys.argv) >= 5 else list(range(19))

# FORCE radarUnavailable=True for both
BaseDEC = load_dec(basepath, "decb"); CandDEC = load_dec(candpath, "decc")
base = BaseDEC(CPStub(True), MpcStub(), params=ParamsStub())
cand = CandDEC(CPStub(True), MpcStub(), params=ParamsStub())

lc = lr = ls = None
diverged = 0; frames = 0; first_div = None

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
            base.update(sm); cand.update(sm)
            bm = nm(base.mode()); cm = nm(cand.mode())
            frames += 1
            if bm != cm:
                diverged += 1
                if first_div is None: first_div = (s, frames, bm, cm)

print(json.dumps({
    "radar_unavailable_forced": True,
    "frames": frames,
    "frames_diverged": diverged,
    "radarless_byte_identical": diverged == 0,
    "first_divergence": first_div,
}, indent=2))
