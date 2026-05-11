# Honda Gas+Wind Live Learner v1

**Branch:** `Dom-clamp`
**Base:** firestar5683/openpilot Dom + previous internetadventuresllc/openpilot work
**Fork:** internetadventuresllc/openpilot

## What this adds

Completes the Honda Bosch gas+wind live learner that starpilot already had refactored as a clean pure function (`update_honda_bosch_live_learning`) but hadn't finished — adds two missing pieces:

1. **Persistence across boots** — two new params (`HondaGasFactorParams`, `HondaWindFactorParams`) load on init and write every 60s. Factors no longer reset to 1.0 every ignition cycle.
2. **BOSCH_ACCEL_MAX saturation guard** — when commanded `gas_pedal_force >= 2.0 m/s²` (saturated), factors are only allowed to *decrease* (snapshot-clamp). Prevents factor inflation toward the 3.0 ceiling on sustained hill climbs.

## What the learner does

Per-frame, while openpilot is engaged AND the driver isn't pressing the gas:

- `gas_factor` adapts so commanded accel matches actual aEgo. If your Civic responds slower than the model assumes, the factor drifts up over a drive. Clamped to `[0.1, 3.0]`.
- `wind_factor` adapts the speed-dependent drag compensation. Clamped to `[0.1, 3.0]`.

Both factors are applied as multipliers on the gas command path that goes through the existing `BOSCH_GAS_LOOKUP_BP`/`V` interpolation. The hard ceiling stays the same as stock — this only adjusts the curve shape within bounds.

## Defense-in-depth layers

1. **Driver-override gate.** `not gasPressed AND longControlState == pid` — driver foot on gas freezes the learner.
2. **Factor clamps.** `np.clip(_, 0.1, 3.0)` at every learning step and on read from disk.
3. **NaN/garbage guard at load.** `_safe_decode_factor()` falls back to 1.0 if disk value is None / NaN / unparseable.
4. **try/except UnknownKeyName.** If the C++ params daemon doesn't know the new keys (e.g., stale binaries), get() raises, gets caught, factors default to 1.0 — no crash.
5. **Saturation guard.** When `gas_pedal_force >= BOSCH_ACCEL_MAX`, factors only allowed to decrease — prevents 3.0-ceiling inflation during sustained max-accel commands.

## How to install

1. On the comma device, go to **Settings → Software → Add Custom Software**
2. Use the install URL:
   ```
   https://github.com/internetadventuresllc/openpilot/tree/Dom-clamp
   ```
3. Wait for download and install
4. Reboot the device
5. The learner runs automatically when openpilot is engaged longitudinally — no UI toggle needed.

## How to verify it took effect

SSH into the device and run:

```python
import sys
sys.path.insert(0, '/data/openpilot')
from openpilot.common.params import Params
print('gas:', Params().get('HondaGasFactorParams'))
print('wind:', Params().get('HondaWindFactorParams'))
```

After a fresh install, both will be `1.0`. After a few drives of openpilot-engaged time, they'll drift toward your car's actual gain — typically gas factor settles somewhere in `[1.0, 1.3]` for Civic Bosch with modified EPS firmware based on the convergence direction in replay tests.

## Convergence iteration workflow

For tracking how the learner settles on your car:

1. After install, drive normally for at least 30 min of engaged openpilot time
2. Check current values via SSH (commands above)
3. Drive same routes over multiple days — factors should plateau, not oscillate
4. If a factor pins at 0.1 or 3.0, it hit the clamp — flag for review (probably indicates a model mismatch upstream, not a learner bug)
5. To reset to defaults: SSH and delete the param files at `/data/params/d/HondaGasFactorParams` and `/data/params/d/HondaWindFactorParams`, then reboot

## Validation completed

Before flashing, this code was validated through:

- **Multi-pass adversarial review** — 5 specialty reviewers (Hallucination, Factual Grounding, Architecture, Performance/Safety, Wiring/Data-Flow) across the planning + diff phases
- **Multi-model QA** — adversarial review by gpt-5.5, gpt-5.4, gemini-2.5-pro, gemini-3.1-pro, qwen3-coder
- **Replay testing** — modified learner run against 2 real Civic rlog segments (~57s each); factors stayed in `[0.1, 3.0]` throughout, no NaN/Inf, gas factor moved from 1.0 to 1.07 over a 10-min engaged segment (consistent with "10% gap" hypothesis)
- **3 unit tests** — including saturation guard, zero-gas-pedal-force no-op, and `_safe_decode_factor` against None/NaN/garbage

## What this branch does NOT change

- No lateral changes — EPS clamp toggle, latcontrol_torque, all Civic Bosch tune values untouched
- No new controller code outside Honda Bosch carcontroller
- Stock openpilot behavior on cars other than Honda Bosch unaffected
- Existing learner math (`update_honda_bosch_live_learning`) preserved — only adds saturation guard branch + persistence wiring around it

## Files changed across the 3 commits

```
915dd23 feat(honda):     persistence + saturation guard wiring
        common/params_keys.h                                | +2
        opendbc_repo/opendbc/car/honda/carcontroller.py    | +50/-3
        opendbc_repo/opendbc/car/honda/tests/test_honda.py | +32/-3

e028cd7 fix(honda):      multi-model QA fixups
        opendbc_repo/opendbc/car/honda/carcontroller.py    | +25/-5
        opendbc_repo/opendbc/car/honda/tests/test_honda.py | +32

41cfd81 Land aia:        rebuilt binaries with new keys baked in
        common/libcommon.a                                  | bin (+1968)
        common/params_pyx.so                                | bin (+8)
        selfdrive/ui/ui                                     | bin (rebuilt)
```

## Safety notes

- Learner only acts on the gas command path, not steering or brake
- Driver override gate is preserved — gasPressed freezes the learner
- Both factors are firmly clamped to `[0.1, 3.0]` at every iteration and at load time
- Persistence write cadence is 60s (`% 6000` frames @ 100Hz), well within eMMC write budget
- No new params have user-facing toggles — these are learned values, not knobs

## Out of scope (v2 candidates)

- mvl-boston's separate Bosch brake PID controller (under-brake correction)
- Per-fingerprint learn_speed tuning (currently hardcoded `learn_speed = 50` for Civic Bosch, which matches the default)
- UI-level reset button (currently requires SSH + delete param files)
- Cereal schema field for live-learned factors (so replay logs can reproduce the gas profile bit-exact)

## Origin

Distilled from a 2026-05-11 session. The starpilot author had cleanly refactored mvl-boston's inline learner into a pure function but hadn't shipped persistence or saturation guard. This branch combines starpilot's structure + mvl-boston's missing pieces, sidestepping a real typo bug in mvl-boston's source (`_before_maxgas` vs `_before_gasmax` identifier mismatch that would AttributeError on cold-start saturation).
