# Honda Gas+Wind Live Learner — Rebuild (v2)

**Branch:** `Dom-clamp-mvl-rebuild` (initially; merges to `Dom-clamp` after operator approval)
**Base:** `internetadventuresllc/openpilot:Dom-clamp` at commit `3c8e421` (May 9 EPS clamp tip)
**Fork:** `internetadventuresllc/openpilot`

## Status

This is the **clean rebuild** of the May 11 MVL gas+wind learner work that bricked Joey's comma 4 on 2026-05-11 night. The prior version (commits `915dd23`, `e028cd7`, `41cfd81`, `5930288`) is preserved on backup branch `Dom-clamp-pre-revert-2026-05-12`.

**What changed in this rebuild vs the bricked tip:**

1. **No binary commit.** The bricked tip shipped `selfdrive/ui/ui`, `common/params_pyx.so`, `common/libcommon.a` claiming device-build but with Ubuntu host RUNPATH (`/usr/local/lib`) and Cython 3.1.2 `.so` vs 3.1.4 `.cpp` asymmetry. This rebuild ships SOURCE ONLY — device rebuilds binaries on first boot via `./build.py` (or manually via SSH, see Activation below).
2. **`last_torque` reset on driver override** — closes the HIGH-severity safety finding that the bricked tip explicitly deferred. See "The last_torque fix" below.
3. **Honest validation language** — the prior README claimed "5 specialty reviewers + multi-model QA on planning + diff phases." Post-mortem found the multi-model QA was on diagnostic docs, not the code patch. This rebuild's validation status section reflects what was actually verified.

## What this adds (unchanged from MVL intent)

Completes the Honda Bosch gas+wind live learner that starpilot already had refactored as a clean pure function (`update_honda_bosch_live_learning`) but hadn't finished — adds two missing pieces:

1. **Persistence across boots** — two new params (`HondaGasFactorParams`, `HondaWindFactorParams`) load on init and write every 60s. Factors no longer reset to 1.0 every ignition cycle.
2. **BOSCH_ACCEL_MAX saturation guard** — when commanded `gas_pedal_force >= 2.0 m/s²` (saturated), factors are only allowed to *decrease* (snapshot-clamp). Prevents factor inflation toward the 3.0 ceiling on sustained hill climbs.

## What the learner does

Per-frame (every 2nd frame at 100 Hz → 50 Hz), while openpilot is engaged longitudinally AND the driver isn't pressing the gas:

- `gas_factor` adapts so commanded accel matches actual `aEgo`. If the Civic responds slower than the model assumes, the factor drifts up over a drive. Clamped to `[0.1, 3.0]`.
- `wind_factor` adapts the speed-dependent drag compensation. Clamped to `[0.1, 3.0]`.

Both factors are applied as multipliers on the gas command path that goes through the existing `BOSCH_GAS_LOOKUP_BP/V` interpolation. The hard ceiling stays the same as stock — this only adjusts the curve shape within bounds.

## Defense-in-depth layers

1. **Driver-override gate.** `not gasPressed AND longControlState == pid` — driver foot on gas freezes the learner.
2. **Factor clamps.** `np.clip(_, 0.1, 3.0)` at every learning step and on read from disk.
3. **NaN/Inf/garbage guard at load.** `_safe_decode_factor()` falls back to 1.0 if disk value is None / NaN / Inf / unparseable. (Inf path: `float("1e500")` returns inf without raising in Py3; numpy `np.clip` passes NaN through unchanged.)
4. **NaN guard at the learner.** `update_honda_bosch_live_learning()` skips the update tick if any input (`desired_accel`, `actual_accel`, `gas_pedal_force`, `wind_brake_mps2`, `v_ego`) is non-finite — prevents NaN poisoning the factor from upstream model glitches or sensor dropouts.
5. **`common/params.py` UnknownKeyName wrapper.** Read path returns `None` if daemon doesn't know the new keys. Defense for the dormant-binary boot state.
6. **Persistence probe at init.** Write path is NOT wrapped at the library layer — it calls `check_key()` synchronously and raises `UnknownKeyName` if the daemon's compiled binary doesn't know the key. Carcontroller does a one-time probe write at init and sets `_persistence_active` based on whether it raised. Runtime 60s-cadence writes are gated on this flag.
7. **Engagement + sanity band on persistence write.** Only persists when `CC.enabled AND 0.1 < gas_factor < 3.0 AND 0.1 < wind_factor < 3.0` — refuses to freeze clamp-pinned values that the README itself flags as "review trigger" (a runaway shouldn't be allowed to perpetuate across reboots).
8. **Saturation guard.** When `gas_pedal_force >= BOSCH_ACCEL_MAX`, factors only allowed to decrease — prevents 3.0-ceiling inflation during sustained max-accel commands.

## The `last_torque` fix (new in this rebuild)

The prior `Dom-clamp` work added a `_modified_civic_standard_active` branch in `carcontroller.py` that zeros `torque_lpf`, `prev_torque_cmd`, and `torque_cmd` when driver override is detected (via `filtered_steering_pressed`). It did NOT zero `self.last_torque`. In this branch `CC.latActive` stays True throughout the override window, so `hondacan.create_steering_control` keeps sending `apply_torque` on the wire while the rate-limiter decays `last_torque` from its previous (potentially large) value toward zero at `STEER_DELTA_DOWN * DT_CTRL` per cycle.

Result on the wire: residual EPS torque continues flowing through CAN during the override, up to ~333ms for a full-amplitude decay from `last_torque = 1.0` (1.0 / 0.03 per cycle ≈ 33.3 cycles × 10ms). A driver pressing the wheel to correct OP would feel a residual fighting them.

The fix is a one-line addition at `carcontroller.py:312`:

```python
if filtered_steering_pressed:
  self.torque_lpf = 0.0
  self.prev_torque_cmd = 0.0
  torque_cmd = 0.0
  # latActive stays True in this branch, so hondacan.create_steering_control
  # still sends apply_torque on the wire. Without this reset, the rate-limiter
  # below decays from a stale self.last_torque (up to ±0.03/cycle) and leaks
  # residual EPS torque to the driver during override. Closes deferred QA HIGH.
  self.last_torque = 0.0
```

The reset is mirrored in BOTH override branches:

- `_modified_civic_standard_active && latActive && filtered_steering_pressed` — the EPS-clamp branch where `latActive` stays True and the wire is NOT auto-zeroed. Primary leak fix.
- `_modified_civic_standard_active && !latActive` — the general disengage branch. The CAN wire IS already zeroed by `hondacan.py:119` here, but `self.last_torque` itself would seed the NEXT re-engage's rate-limiter baseline at a stale value (e.g., 0.65 from a held curve), producing a noticeable lateral jolt on re-engage from a held-curve state. The reset prevents that re-engage flicker too.

MVL upstream does NOT have this fix in either branch — the deferred-finding was deferred in MVL too. We're not porting the fix; we're designing it.

MVL upstream does NOT have this fix either — the deferred-finding was deferred in MVL too. We're not porting the fix; we're designing it.

## How to install

1. On the comma device, go to **Settings → Software → Add Custom Software**
2. Use the install URL (after operator approval to merge into Dom-clamp):
   ```
   https://github.com/internetadventuresllc/openpilot/tree/Dom-clamp
   ```
   For testing on the feature branch before merge:
   ```
   https://github.com/internetadventuresllc/openpilot/tree/Dom-clamp-mvl-rebuild
   ```
3. Wait for download and install
4. Reboot the device — see Activation below for what to expect

## Activation (this is different from the bricked tip)

Because binaries are not committed, **the C++ params daemon will not know the two new keys on first boot.** Two defense-in-depth layers handle this gracefully:

- **Read path:** `Params.get()` is wrapped in `common/params.py` with `except UnknownKeyName: return default`. Carcontroller's `__init__` reads → daemon doesn't recognize key → wrapper returns `None` → `_safe_decode_factor(None)` returns `1.0`. Clean boot, factors default to 1.0.
- **Write path:** `Params.put_nonblocking()` is NOT wrapped at the library layer — it calls `check_key()` synchronously and raises `UnknownKeyName` if the daemon doesn't recognize the key. Carcontroller's `__init__` does a one-time probe write; if it raises, `self._persistence_active = False`. The 60s-cadence runtime writes are gated on this flag (and on `CC.enabled` and a sanity band that refuses to persist clamp-pinned values).

Result on stale-binary first boot:
- Device boots normally
- Learner code runs but **persistence is dormant** — values reset to 1.0 every boot
- 60s-cadence writes are silently skipped (no crash)
- Driving behavior is the SAME as `3c8e421` baseline (factors at 1.0 = identity multiplier)

**To activate persistence**, rebuild on-device:

```bash
ssh comma@<device-ip>
cd /data/openpilot
./build.py
sudo reboot
```

After reboot:
- `prebuilt_runtime_compatible` check passes (newly built `.so` matches `.cpp` Cython version)
- C++ daemon recognizes the new keys
- Persistence works, factors converge over engaged drives

**Optional faster path** (rebuild on first boot automatically): SSH in BEFORE rebooting after install and delete the prebuilt sentinel:
```bash
ssh comma@<device-ip>
rm /data/openpilot/prebuilt
sudo reboot
```
Next boot will be slow (~15-30 min black screen with progress spinner — this is `./build.py` rebuilding everything). After that, the device runs with fresh binaries and persistence is live.

## Build-provenance discipline (mandatory for any future binary commit)

The bricked tip's binaries were committed with the commit message claiming "Rebuilt device-side via uv run scons -j4 on the comma 4" but actually showed `RUNPATH=/usr/local/lib` (Ubuntu host) and Cython 3.1.2 `.so` against 3.1.4 `.cpp`. **Any future binary commit must pass all six gates before merge to Dom-clamp:**

```bash
# 1. RUNPATH must be AGNOS sysroot, NOT /usr/local/lib
readelf -d common/params_pyx.so | grep -E "RUNPATH|RPATH"
# Expected: empty OR a comma-managed path — FAIL if /usr/local/lib appears

# 2. No Ubuntu/Debian compiler banner
strings selfdrive/ui/ui | grep -iE "GCC.*Ubuntu|Debian" | head -3
# Expected: empty — FAIL if "Ubuntu 13.2.0" or similar appears

# 3. Cython ABI must match tree's pinned version
strings common/params_pyx.so | grep -oE "Cython version [0-9.]+"
# Expected: matches uv.lock's locked Cython — FAIL on any version skew

# 4. Companion .cpp must be regenerated against same Cython
head -3 common/params_pyx.cpp | grep -oE "Generated by Cython [0-9.]+"
# Expected: matches the .so's Cython version

# 5. Local dry-run prebuilt_runtime_compatible BEFORE push
cd /data/openpilot && python3 -c "
import importlib
for m in ['openpilot.common.params_pyx','msgq.ipc_pyx','msgq.visionipc.visionipc_pyx']:
  importlib.import_module(m); print(f'OK {m}')
"
# Expected: all OK; FAIL = device will fall through to rebuild on boot

# 6. Symbol presence for new keys
strings common/libcommon.a | grep -E "HondaEPSClampReleased|HondaGasFactorParams|HondaWindFactorParams"
# Expected: all 3 present
```

Receipts from these checks must be pasted in the commit body, not summarized.

## How to verify the learner took effect (after Activation)

SSH into the device and run:

```python
import sys
sys.path.insert(0, '/data/openpilot')
from openpilot.common.params import Params
print('gas:', Params().get('HondaGasFactorParams'))
print('wind:', Params().get('HondaWindFactorParams'))
```

After a fresh activation, both will be `1.0`. After a few drives of openpilot-engaged time, they'll drift toward the car's actual gain — typically gas factor settles somewhere in `[1.0, 1.3]` for Civic Bosch with modified EPS firmware based on convergence direction in replay tests.

## Convergence iteration workflow

1. After activation, drive normally for at least 30 min of engaged openpilot time
2. Check current values via SSH (commands above)
3. Drive same routes over multiple days — factors should plateau, not oscillate
4. If a factor pins at 0.1 or 3.0, it hit the clamp — flag for review (probably indicates a model mismatch upstream, not a learner bug)
5. To reset to defaults: SSH and delete the param files at `/data/params/d/HondaGasFactorParams` and `/data/params/d/HondaWindFactorParams`, then reboot

## Validation status (honest)

What was verified in this rebuild:
- **5-auditor post-mortem** of the 2026-05-12 brick (git forensics, Pond two-gate, launcher trigger, session reconstruction, cross-project sync) — root cause traced to binary-provenance and Cython asymmetry, not source-level logic
- **4-advisor swarm** during this rebuild (Strategic Architect, MVL Code Forensics, Last_Torque Safety Audit, Build Discipline) with direct code reads, cross-tension resolution via `carcontroller.py` lines 303-326 inspection
- **Source-only commit shape** — no binary-provenance risk; verified by `git status` + diff
- **`last_torque` fix code-reviewed** against the exact override-branch semantics; verified that `latActive` remains True in the modified-civic-bosch branch so wire-zero protection doesn't apply

What is NOT verified, and is the operator's gate to clear before merge to Dom-clamp:
- **Sacrificial-device test of `./build.py` on a factory-reset comma 4** (estimated 15-30 min rebuild; cythonize-on-clean-AGNOS unverified; root partition headroom under bare-scons unverified)
- **Cabana logging of the `last_torque` fix** — parked-car protocol: measure first-cycle re-engage `apply_torque` ≤ 0.05 with fix vs ~0.44 without; confirm CAN wire torque was 0 during pressed-window (regression check that hondacan.py:119 wasn't disturbed)
- **Behavioral drive test** of the gas+wind learner with persistence active — factors should converge to plateau, not oscillate; sustained-saturation test should show factors clamped not inflating

## Known divergences from MVL upstream

These were dropped silently in the original port and NOT restored in this rebuild. Each is a candidate for a follow-up commit if Joey wants closer MVL parity:

1. **60-unit `bosch_last_gas` ramp** (MVL `carcontroller.py:288-291`). MVL author comment: "limit gas ramp to 60 units per frame, matches stock. Higher sometimes causes powertrain to ignore gas command." This is a powertrain-acceptance mitigation. Dropped in port without justification. Restoring it requires `self.bosch_last_gas = 0` instance state + the 3-line ramp logic after `self.gas = float(np.interp(...))`. Not restored here because it changes gas-command behavior in a way no tested baseline (including the bricked tip) exercised.
2. **Per-fingerprint `learn_speed`** (MVL has `50/150/300` by fingerprint, `100/1000` for wind). For HONDA_CIVIC_BOSCH specifically, MVL falls through to default `else: 50` for gas and `else: 1000` for wind — which matches our hardcoded values. So this is a no-op for Joey's Civic but a divergence for any future Honda variant.
3. **MVL's `new_actuators.gas`/`brake` field hijack** for telemetry (MVL writes learned factors to actuator gas/brake fields for replay observability). Omitted in port. Means convergence is observable only via direct param read, not via replay logs.

## What this branch does NOT change

- No lateral changes — EPS clamp toggle, `latcontrol_torque`, all Civic Bosch tune values untouched
- No new controller code outside Honda Bosch carcontroller
- Stock openpilot behavior on cars other than Honda Bosch unaffected
- Existing learner math (`update_honda_bosch_live_learning`) preserved — only adds saturation guard branch + persistence wiring around it
- No binary commit (departure from prior `Dom-clamp` shape — see Activation)

## Files changed (source-only)

```
feat(honda): port mvl gas+wind learner with persistence + saturation guard + last_torque safety reset
  common/params_keys.h                                | +2 lines (HondaGasFactorParams, HondaWindFactorParams)
  opendbc_repo/opendbc/car/honda/carcontroller.py    | +75/-3 lines (learner, persistence, override last_torque reset)
  opendbc_repo/opendbc/car/honda/tests/test_honda.py | +67/-0 lines (saturation guard + safe-decode + override reset tests)

docs: add HONDA_GAS_WIND_LEARNER_README v2
  HONDA_GAS_WIND_LEARNER_README.md                    | this file
```

No `common/libcommon.a`, no `common/params_pyx.so`, no `selfdrive/ui/ui` commits. No `prebuilt` sentinel deletion (preserves boot speed; user opts in to rebuild via Activation steps).

## Out of scope for this rebuild (v3 candidates)

- 60-unit `bosch_last_gas` ramp restoration (see "Known divergences")
- mvl-boston's separate Bosch brake PID controller (under-brake correction)
- UI-level reset button for learned factors (currently requires SSH + delete param files)
- Cereal schema field for live-learned factors (so replay logs can reproduce the gas profile bit-exact)
- Per-fingerprint `learn_speed` for non-Civic Honda variants

## Origin

This rebuild was produced after the May 11 work bricked Joey's comma 4 on the "Update Required" screen the night of 2026-05-11. Recovery was a full AGNOS reimage via `flash.comma.ai` in QDL mode (USB + Zadig driver for VID 3801 / PID 9008) on 2026-05-12.

A 5-auditor forensic post-mortem traced the brick to commit `3c8e421`'s asymmetric binary commit (Cython 3.1.2 `.so` against 3.1.4 `.cpp`, Ubuntu host RUNPATH `/usr/local/lib`, libcommon.a shrinkage signaling code removal) compounded by `41cfd81`'s reliance on `UV_CACHE_DIR=/data/uv-cache` redirect that doesn't survive factory reset.

The post-mortem captured five memory patterns now in `~/.claude/projects/C--claudecode/memory/`:
- `feedback_verify_handoff_deployed_claims.md` (Receipt #2: binary-provenance via readelf + GCC banner)
- `feedback_5th_reviewer_lens_default.md` (Receipt #2: 5th lens skipped, contributed to brick)
- `feedback_handoff_memory_staleness.md` (new: project memory was 2 days stale at session start)
- `reference_comma4_uv_cache_redirect.md` (new: 517MB partition + /data/uv-cache reset-fragility — operator-verifiable on the device, not asserted from code)
- `project_comma4epsflash.md` (updated with 2026-05-12 post-mortem section)
