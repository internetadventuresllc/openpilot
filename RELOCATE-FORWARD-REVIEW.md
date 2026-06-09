# Civic Bosch 0x1DF -> 0x4F0 Relocate-and-Forward — Reviewer Design Doc

**Branch:** `civic-bosch-0x4f0-relocate-forward`
**Base:** `radar-fine-0x280-ingest`
**Status:** INERT. Nothing in this branch has been flashed, sent on CAN, or driven. The `.rwd`
is a study artifact. The OP code has not been deployed to a device. This doc exists so a
human reviewer can evaluate the architecture and the safety regression BEFORE any of that happens.

---

## 1. The problem this solves

On a stock Civic Bosch, the forward radar (36802-TBA) owns longitudinal: it broadcasts
`ACC_CONTROL` on **0x1DF**, including factory AEB. openpilot longitudinal ("op-long") requires
openpilot to be the one sending 0x1DF — but on stock hardware that means the radar must be muted,
which **disables factory AEB** (the long-standing `WARNING: THIS DISABLES AEB!` in `interface.py`).

The operator wants op-long **and** factory AEB. The relocate-and-forward approach gets most of
the way there:

1. **Reflash the radar** so it emits its `ACC_CONTROL` on a *new* CAN id, **0x4F0**, instead of
   0x1DF. This frees 0x1DF for openpilot and keeps the radar's full decision pipeline (including
   AEB) alive and broadcasting — just on a different address.
2. **openpilot reads 0x4F0**, and when the radar asserts an AEB event there, openpilot **forwards
   that AEB intent into its own 0x1DF** `ACC_CONTROL` frame (re-checksummed, so the powertrain
   accepts it).

Net effect *while openpilot is running*: op-long drives normally, and if the radar fires AEB,
openpilot relays it to the powertrain within the same control cycle.

```
   STOCK:   radar --[0x1DF ACC_CONTROL incl. AEB]--> powertrain      (op-long impossible w/o muting AEB)

   RELOCATE: radar --[0x4F0 ACC_CONTROL incl. AEB]--> openpilot
                                                          |
             openpilot --[0x1DF ACC_CONTROL, op accel OR forwarded radar-AEB]--> powertrain
```

---

## 2. The firmware side — the `.rwd` (study artifact)

- **File:** `C:\claudecode\firmware-analysis-kit\modded-firmware\radar-36802\36802-TBA,A160-RELOCATE-1DF-to-4F0.rwd.gz`
- **Build report:** `..._build_report.txt` (same dir)
- **What it does:** patches the **five** outbound id sites in the radar's TX/COM descriptor and
  routing tables from `01DF` to `04F0`:
  - `0x128DC6` — TX descriptor table entry[0] (stride-20, base 0x128DC4)
  - `0x12A176` — AUTOSAR/COM descriptor table (base 0x128FE0, stride-20, entry 225)
  - `0x11CB9A` — COM signal table (base 0x11CB80, stride-8 pair)
  - `0x13487C` — CAN routing/signal-binding table (base 0x134804, stride-12, entry[10])
  - `0x13696C` — slot-group/message-group scheduler map (block base 0x136938)
- **Integrity:** whole-image CRC16 @0x14FFFE recomputed `0x9C31 -> 0xEC64`. Re-encrypted via the
  canonical monoalphabetic LUT + x5a repack.
- **`byte_diff_clean = True`**: round-trip verify confirms **only** the 10 intended patch bytes
  plus the 2 CRC bytes changed (12 total, expected 12). No collateral edits.
- **fw string discriminator:** the flashed radar reports `36802-TBA,A160` (comma) vs. the stock
  `36802-TBA-A160` (hyphen). The comma is the *sole* discriminator everywhere in the OP code.

### Open firmware risk (not resolved here)
The bootloader's secure-boot chain (ECDSA/X509/SHA256, verify @0x11648) gates **boot-time app
launch**. A content-modified image may be refused at boot — MEDIUM-confidence open gate. This is
why the artifact is study-only and gated on M1 L2-SA proof + a *spare* radar before any flash is
even considered. (Flash write itself is cryptographically unauthenticated; the risk is the radar
refusing to *run* the modified app, not refusing to accept the write.)

---

## 3. The openpilot side — five atoms

All changes are scoped to Honda Civic Bosch with the **flashed** radar fw (comma). Stock-radar,
0x280-only, radarless, CANFD, and unknown/empty-fw paths are untouched.

| Commit | Atom | Files |
|---|---|---|
| `aad32a9` | OP-3 | `dbc/honda_civic_bosch_radar.dbc` — `BO_ 1264 ACC_CONTROL_RELOCATED` |
| `45f6466` | OP-1 | `honda/values.py` (`RADAR_FW_RELOCATED`), `honda/interface.py` (force-op-long gate) |
| `8c150c2` | OP-4 | `values_ext.py` (`RADAR_FLASHED`), `interface.py` (flag-set), `carstate.py` (parser+stash), `fingerprints_ext.py` (fw entry) |
| `aef0a61` | OP-2 | `honda/hondacan.py` (`radar_aeb` override), `honda/carcontroller.py` (call site) |
| `5c69c02` | OP-5 | `honda/values.py` (`BOSCH_RELOCATE`), `safety/modes/honda.h`, `safety/tests/test_honda.py` |

### 3a. The RADAR_FLASHED gate (OP-1 / OP-4)
- `HondaFlagsSP.RADAR_FLASHED = 16` is set in `interface._get_params_sp` when **any fwdRadar fw
  string contains a comma** (mirrors the existing `EPS_MODIFIED` comma-detect). It is the single
  switch that turns the whole feature on.
- When the fwdRadar fw matches `RADAR_FW_RELOCATED` exactly, `interface._get_params` **forces**
  `openpilotLongitudinalControl=True`, `pcmCruise=False`, `radarUnavailable=False` — un-pinning
  op-long from the `alpha_long` toggle that still governs stock and 0x280-only cars.
- `fingerprints_ext.py` registers `b'36802-TBA,A160'` under `HONDA_CIVIC_BOSCH` fwdRadar. fwdRadar
  is ESSENTIAL + FUZZY_EXCLUDE, so **without this entry the flashed car would fail to fingerprint
  at all** — this is load-bearing, not cosmetic.
- `carstate.get_can_parsers` adds a `Bus.radar` CANParser (on `CanBus(CP).camera` — radar frames
  ride the camera bus, rlog src=2) **only** when `RADAR_FLASHED` is set. `carstate.update`
  snapshots `ACC_CONTROL_RELOCATED` into `self.radar_acc_relocated` each frame.

### 3b. The forward override (OP-2)
- `hondacan.create_acc_commands(... , radar_aeb=None)`. With `radar_aeb=None` the function is
  **byte-identical to today**. When `radar_aeb` is set, any AEB bit is high, and the car is not
  radarless, the override clobbers `ACCEL_COMMAND` with the radar's decel and sets
  `BRAKE_REQUEST`/`AEB_STATUS`/`AEB_PREPARE`/`AEB_BRAKING` **before** `make_can_msg`, so the
  re-checksummed 0x1DF carries radar-AEB intent. It runs last, so it wins same-cycle vs. the
  op-generated accel (correct safety polarity).
- `carcontroller` caches `self.radar_flashed` once at construction and passes
  `radar_aeb=(CS.radar_acc_relocated if self.radar_flashed else None)`.
- The `AEB_*` keys are valid `ACC_CONTROL` packer keys (BO_ 479 via `_bosch_radar_acc.dbc`,
  present in the generated Civic pt DBC) and default to 0 when omitted — adding them only sets
  bits, no schema change.

### 3c. The panda floor change (OP-5)
- `HONDA_PARAM_BOSCH_LONG` is **hoisted out of `#ifdef ALLOW_DEBUG`** so `honda_bosch_long` is
  settable on **release** panda builds. Without this, 0x1DF is never whitelisted and all op-long
  TX is dropped on release firmware. *(This is a real widening of release behavior — reviewer
  should weigh it; it is the minimum needed for op-long on a non-debug panda.)*
- New `HONDA_BOSCH_RELOCATE_LONG_LIMITS` with `min_accel = -1000` centiunits (**-10 m/s2**),
  selected for the **0x1DF accel/gas check only** when `honda_bosch_relocate_long` is set. This
  admits a verbatim forward of full-authority factory AEB decel instead of clipping it at the
  default `-350` / -3.5 m/s2 (a clip would mean *partial* braking at the emergency moment).
- The radarless `0x1C8` path and Bosch-CANFD keep the original `-350` floor — **unchanged**.
- `honda_bosch_relocate_long` requires **both** `bosch_long` AND the new `BOSCH_RELOCATE` flag.
- `test_honda.py` adds `TestHondaBoschRelocateLongSafety` exercising the -10.0 m/s2 0x1DF floor;
  the existing bosch-long and CANFD-long tests keep MIN_ACCEL=-3.5.

---

## 4. THE FAIL-SAFE REGRESSION — read this (W1/W2)

**This is the honest cost of the design. It is NOT mitigated by this branch.**

Factory AEB on the relocated radar is broadcast on **0x4F0**. **Nothing on the powertrain consumes
0x4F0.** The powertrain only acts on `ACC_CONTROL` at **0x1DF**. The bridge from 0x4F0 to 0x1DF is
**openpilot software** (the OP-2 forward override). Therefore:

- **During the boot window (~10-30 s after power-on)** while openpilot/the comma device is coming
  up and not yet sending 0x1DF: the radar sees obstacles and asserts AEB on 0x4F0, but **no AEB
  reaches the powertrain.** Factory AEB is effectively absent during boot.
- **During any openpilot crash, disengage, panic, or process death:** controls are not allowed,
  openpilot stops sending 0x1DF, the panda relaxed floor is inactive (it gates on
  `controls_allowed`), and **the 0x4F0 AEB intent goes nowhere.** Factory AEB is absent.
- **Stock behavior was strictly safer here:** on a stock car, factory AEB fires regardless of
  openpilot's state because the radar talks to the powertrain directly on 0x1DF.

In short: **this design trades "factory AEB always available" for "factory AEB available only while
openpilot is up and engaged."** The operator has accepted this tradeoff knowingly (op-long carrying
the driving load is an accessibility need, and keep-AEB-while-up is still better than the stock
op-long path which kills AEB entirely). But a reviewer **must** see it stated plainly: this is a
fail-DARK behavior on the most safety-critical function the radar performs.

---

## 5. Known open items / things a reviewer should push on

1. **Staleness of `radar_acc_relocated` is NOT cleared (highest priority).** `carstate.update`
   refreshes the snapshot only when the radar parser produces a frame; CANParser retains the last
   decoded value, so if 0x4F0 frames stop, the last AEB snapshot **persists**. The OP-2 atom spec
   assigned a staleness-clear to the OP-4 parser (set `radar_acc_relocated = None` when the 0x4F0
   source is stale, mirroring `BOSCH_RADAR_STALE_S = 0.15 s`), **but no such diff was provided in
   the atom**, so it is **not implemented on this branch.** As written, a frozen phantom-brake
   `ACCEL_COMMAND` could persist until the next disengage. This was left as an explicit gap rather
   than silently invented, since inventing safety-critical logic outside the atom spec is the wrong
   move for an INERT review branch. **Recommend: add a freshness check (`vl_all` count or a
   `valid`/timestamp gate) before trusting `radar_acc_relocated`.**
2. **Release-build op-long hoist (OP-5).** Hoisting `HONDA_PARAM_BOSCH_LONG` out of `ALLOW_DEBUG`
   widens what release panda firmware permits. Intentional and required, but a real safety-model
   change worth a deliberate sign-off.
3. **Forward override has no rate-limit / sanity-clamp of its own** beyond the panda -10 floor. It
   trusts whatever decel the radar put on 0x4F0. The panda check is the backstop; consider whether
   an OP-side clamp is also wanted.
4. **`radar_acc_relocated['ACCEL_COMMAND']` is a hard key lookup** in the override (KeyError if
   absent). Safe given OP-3 always defines the signal, but it couples OP-2 to the DBC contract.
5. **Secure-boot may refuse the modified radar image** (section 2). Until that is resolved on a
   spare radar, the entire OP side is exercising a code path no real car can yet produce.
6. **`pcmCruise=False` forced** for the flashed car — confirm this matches the intended cruise
   button / set-speed UX for op-long on this platform.

---

## 6. Validation performed on this branch (no device, no bus)

- `python -m py_compile` on all 8 changed Python files — **PASS**.
- `gcc -fsyntax-only` on `opendbc/safety/tests/libsafety/safety.c` (the real safety TU) **with and
  without `-DALLOW_DEBUG`** — **PASS both** (confirms the ALLOW_DEBUG hoist leaves no dangling refs).
- DBC generator runs clean; `honda_civic_hatchback_ex_2017_can_generated.dbc` rebuilds and contains
  `BO_ 479 ACC_CONTROL` with the AEB signals (generated DBC is gitignored, not committed).
- opendbc `CANParser('honda_civic_bosch_radar', ...)` constructs OK (non-strict loader handles the
  documented RANGE/RANGE_RAW overlap; cantools-strict rejects it, as expected).
- `CANPacker('honda_civic_hatchback_ex_2017_can_generated').make_can_msg('ACC_CONTROL', 1, {...AEB
  keys...})` packs to addr **0x1DF** — confirms AEB_* are valid packer keys.
- fw-discriminator check: `RADAR_FW_RELOCATED.replace(b',', b'-') == RADAR_FW_0X280_INGEST` — True
  (comma is the sole difference). Flag values: `RADAR_FLASHED=16`, `BOSCH_RELOCATE=32`.
- **Not run:** the panda safety unit tests (require an scons libsafety build not available in this
  environment) and any on-device / replay test. The new `TestHondaBoschRelocateLongSafety` is
  committed but unexecuted here.

---

## 7. Bottom line for the reviewer

The architecture is coherent and the per-atom changes are tightly scoped and gated on the flashed
fw string, so stock cars are unaffected. The two things that need a human decision before this goes
anywhere near a car: **(a) the W1/W2 fail-dark AEB regression (section 4)** — accepted by the
operator but a genuine downgrade of the most critical safety function — and **(b) the missing
staleness clear on `radar_acc_relocated` (section 5, item 1)**, which should be fixed before any
live use to avoid a frozen phantom-brake. Everything here is INERT until both are signed off and
the secure-boot gate is cleared on a spare radar.
