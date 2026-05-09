# StarPilot Dom — Civic Bosch EPS Clamp Released v1

**Branch:** `Dom-clamp`
**Base:** firestar5683/openpilot Dom
**Fork:** internetadventuresllc/openpilot

## What this branch adds

A single galaxy toggle — **"Honda EPS Modified Override"** — under Lateral (Steering) → Advanced Lateral Tuning.

Use it if you have a Honda Civic Bosch (2017-2021) with EPS firmware that has been modified to release the torque saturation clamp **but the firmware version string was NOT updated with the comma-byte signature** (e.g., TBA-C120 binary mods that leave the version identical to stock).

## Why this is needed

Stock openpilot/Dom auto-detects modified Honda EPS firmware by checking for a comma byte (`,`) in the EPS firmware version string at `honda/interface.py:93-99`:

```python
if fw.ecu == "eps" and b"," in fw.fwVersion:
    eps_modified = True
```

This works for firmwares that follow the convention (`TGG-A020` → `TGG,A020`), but skips binary mods that don't update the version string. Without `EPS_MODIFIED` flagged:

- The `modified_civic_force_torque` path (`opendbc/car/interfaces.py:185-194`) doesn't fire
- Controller stays on PID — friction slider doesn't apply
- The civic-bosch-modified special tuning in `latcontrol_torque.py` is dormant

## What the toggle does

When enabled (and you reboot):

1. `HondaFlags.EPS_MODIFIED` is forced on for `HONDA_CIVIC_BOSCH`
2. `modified_civic_force_torque=True` triggers `configure_torque_tune()` — switches the lateral controller to torque mode
3. `is_civic_bosch_modified=True` everywhere that condition is checked, activating:
   - `get_civic_bosch_modified_b_friction_scale()` in `latcontrol_torque.py:473`
   - The civic-bosch-modified pressed-detection in `honda/carcontroller.py:234`
4. Galaxy sliders **SteerFriction**, **SteerLatAccel** become live (because `is_torque_car=True`)

## Tune values you'll inherit

`configure_torque_tune()` reads from `opendbc/car/torque_data/params.toml`:

```
"HONDA_CIVIC_BOSCH" = [1.6917, 0.4013, 0.2546]
                       LAT_ACCEL_FACTOR, MAX_LAT_ACCEL_MEASURED, FRICTION
```

Sets:
- `tune.torque.latAccelFactor = 1.6917`
- `tune.torque.friction = 0.2546`
- `tune.torque.latAccelOffset = 0.0`
- `tune.torque.steeringAngleDeadzoneDeg = 0.0`
- `kp/ki/kf` use latcontrol_torque's `KP_INTERP` defaults (not per-car)

**Important:** params.toml indexes by car *candidate*, not firmware family. So if your friend on TGG,A020/A120 has working tune, you inherit the **identical** torque-tune defaults. You can fine-tune from there via the galaxy SteerFriction / SteerLatAccel sliders.

## How to install

1. On the comma device, go to **Settings → Software → Add Custom Software**
2. Use the install URL pattern for this fork's branch:
   ```
   https://github.com/internetadventuresllc/openpilot/tree/Dom-clamp
   ```
   Or via the comma installer URL pattern (depends on your device's installer flow — see your device's docs for "Add Custom Software").
3. Wait for download and install
4. Once on this branch:
   - Galaxy → **Lateral (Steering)** → **Advanced Lateral Tuning** → enable
   - Toggle **"Honda EPS Modified Override"** ON
   - Reboot the device (toggle is in `rebootKeys`)

## How to verify it took effect after reboot

SSH into the device and run:

```python
import sys
sys.path.insert(0, '/data/openpilot/opendbc_repo')
from cereal import car
with open('/data/params/d/CarParamsPersistent', 'rb') as f:
    cp_bytes = f.read()
with car.CarParams.from_bytes(cp_bytes) as cp:
    print("controller class:", cp.lateralTuning.which())  # should now print: torque
    print("flags:", hex(cp.flags))                         # should be 0x2004 (BOSCH=4 | EPS_MODIFIED=8192)
    if cp.lateralTuning.which() == "torque":
        print("friction:", cp.lateralTuning.torque.friction)
        print("latAccelFactor:", cp.lateralTuning.torque.latAccelFactor)
```

Expected after reboot with toggle on:
- `controller class: torque`
- `flags: 0x2004` (or higher if other Honda flag bits are also set; key is the `0x2000` EPS_MODIFIED bit)
- `friction: 0.2546...`
- `latAccelFactor: 1.6917...`

## Tune iteration workflow (for ping-pong tuning)

After verifying torque controller engaged:

1. Drive normally to log baseline behavior
2. Galaxy → SteerFriction: try **0.30** (up from 0.25 default)
3. Drive same route, compare wheel feel
4. If still ping-ponging at low amplitude (~2 Hz), try SteerLatAccel = **1.85** (up from 1.69) — this lets feedforward do more work, P does less, less excitation of mechanical resonance
5. If still bad: try friction up to 0.35
6. SteerKP slider in galaxy is currently inert in Dom (no controller reads it) — don't waste time tuning it

To analyze a drive's ping-pong quantitatively, pull the rlog and run the Welch PSD / cmd→actual transfer-function analysis from the upstream debug folder.

## What this branch does NOT change

- No tuning algorithm changes
- No new controller code
- No changes to existing PID controller behavior for cars without the override toggle on
- All existing TGG,A020 / TGG,A120 auto-detection still works exactly as before
- Other Honda variants (Accord, CR-V, Clarity) unaffected — toggle only acts on `HONDA_CIVIC_BOSCH`

## Files changed (5 files, +11/-2)

```
common/params_keys.h                        | +1
opendbc_repo/opendbc/car/interfaces.py      | +6
starpilot/common/starpilot_variables.py     | +1
starpilot/ui/qt/offroad/lateral_settings.cc | +2/-1
starpilot/ui/qt/offroad/lateral_settings.h  | +1/-1
```

## Safety notes

- Toggle is OFF by default — no behavior change without explicit user opt-in
- Reboot required (in `rebootKeys`) — prevents accidental mid-drive controller switch
- Restricted to `HONDA_CIVIC_BOSCH` candidate; toggle is no-op on any other car
- All downstream tuning leverages Dom's existing pre-validated `is_civic_bosch_modified` code paths — same code that runs for TGG-modded cars in the wild
- Tune values inherited from `params.toml` are the upstream-published Civic Bosch values, not custom-derived

## Origin

Distilled from a 2026-05-09 ping-pong debugging session on a Honda Civic Bosch with TBA-C120 binary mod. Diagnostic identified two oscillations:

- 0.39 Hz (planner-loop limit cycle)
- ~2 Hz (mechanical/EPS resonance, cmd→actual gain 6.95×)

Friction-led tune (per a Honda Clarity tinkerer friend's empirical guidance) was the indicated direction. Detection gap was identified: TBA-C120 binary mods don't update the EPS fw version string with the comma signature, so `eps_modified` auto-detection misses them. This branch adds the manual override.

Full diagnostic + analysis at: <upstream debug folder>
