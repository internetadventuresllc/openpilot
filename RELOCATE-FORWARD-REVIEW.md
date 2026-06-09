# Civic Bosch 0x1DF -> 0x4F0 Relocate-and-Forward — Reviewer Design Doc

**Branch:** `civic-bosch-0x4f0-relocate-forward`
**Base:** `radar-fine-0x280-ingest`
**Status:** INERT. Nothing in this branch has been flashed, sent on CAN, or driven. The `.rwd`
is a study artifact. The OP code has not been deployed to a device. This doc exists so a
human reviewer can evaluate the architecture and the safety regression BEFORE any of that happens.

> **ADVERSARIAL-REVIEW FIXES APPLIED (post-review pass).** The blockers and majors from the adversarial
> review have been fixed on this same branch. Summary at the top so the reviewer sees state at a glance;
> details are folded into the sections below and into **§8 (Fixes applied)**.
>
> - **BLOCKER #2 (FIXED):** `interface._get_params` now ORs `HondaSafetyFlags.BOSCH_RELOCATE` into the
>   Bosch-long `safetyParam` for the relocated radar, so `honda_bosch_relocate_long` is actually true on
>   the panda and the -1000 floor (not -350) is used — a forwarded full-authority AEB is no longer
>   hard-dropped to zero braking.
> - **MAJOR #3 (FIXED):** `interface.init()` no longer `disable_ecu`-mutes the radar for the flashed car
>   (gated on `CP_SP & RADAR_FLASHED`), so it can't kill the radar whose 0x4F0 the forward reads.
> - **MAJOR #4 (FIXED):** `carstate` now freshness-gates the 0x4F0 snapshot (~0.15 s, mirroring
>   `BOSCH_RADAR_STALE_S`) and sets `radar_acc_relocated = None` when stale — no frozen phantom-brake.
> - **MAJOR #5 (FIXED/reconciled):** the relaxed -1000 floor is gated SOLELY on `BOSCH_RELOCATE`; the
>   `ALLOW_DEBUG` hoist of `BOSCH_LONG` no longer widens the relaxed AEB floor to all Honda Bosch cars.
> - **MAJOR (lens1) (FIXED):** the forward override fires only on a real commanded decel
>   (`AEB_BRAKING`/`BRAKE_REQUEST` set AND `ACCEL_COMMAND < 0`), not the PREPARE-only union, and clamps
>   the forwarded accel to the -10.0 m/s² panda floor.
> - **MINORS (a)(b)(c) (APPLIED):** explicit 0x4F0 subscription; relocate-gate subsumption comment;
>   the un-forwarded `MAYBE_DISENGAGE_COMMAND`/`ALERT` (bits 41/54) noted below.
> - **.rwd:** the corrected study artifact `36802-TBA,A160-RELOCATE+MARKER-1DF-to-4F0.rwd.gz` carries the
>   comma `RADAR_FW_RELOCATED` marker (10 DID copies, hyphen→comma) so the OP code actually fingerprints
>   it as relocated. Build is byte-diff clean (22 bytes: 10 relocate + 10 marker + 2 CRC).
>
> **The W1/W2 fail-dark AEB regression (§4) is NOT mitigated by these fixes — it is intrinsic to the
> design and remains the operator's accepted tradeoff.**

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

- **File (corrected, marker-carrying):**
  `C:\claudecode\firmware-analysis-kit\modded-firmware\radar-36802\36802-TBA,A160-RELOCATE+MARKER-1DF-to-4F0.rwd.gz`
  - This is the artifact the OP code can actually fingerprint. The earlier `...-RELOCATE-1DF-to-4F0.rwd.gz`
    relocated 0x1DF→0x4F0 but did **not** flip the fw string to the comma form, so `RADAR_FW_RELOCATED`
    (the *sole* discriminator) would never match it and none of the OP gating would engage. The
    `+MARKER` build fixes that by additionally patching the part-number DID string hyphen→comma.
- **Build report:** `36802-TBA,A160-RELOCATE+MARKER-1DF-to-4F0_build_report.txt` (same dir)
- **What it does:** patches the **five** outbound id sites in the radar's TX/COM descriptor and
  routing tables from `01DF` to `04F0`, **plus ten** marker sites (hyphen→comma, `0x2D`→`0x2C`):
  - `0x128DC6` — TX descriptor table entry[0] (stride-20, base 0x128DC4)
  - `0x12A176` — AUTOSAR/COM descriptor table (base 0x128FE0, stride-20, entry 225)
  - `0x11CB9A` — COM signal table (base 0x11CB80, stride-8 pair)
  - `0x13487C` — CAN routing/signal-binding table (base 0x134804, stride-12, entry[10])
  - `0x13696C` — slot-group/message-group scheduler map (block base 0x136938)
- **Integrity:** whole-image CRC16 @0x14FFFE recomputed `0x9C31 -> 0x1D1B`. Re-encrypted via the
  canonical monoalphabetic LUT + x5a repack.
- **`byte_diff_clean = True`**: round-trip verify confirms **only** the intended patch bytes plus the
  2 CRC bytes changed — **22 total** (10 relocate + 10 marker + 2 CRC), expected 22. No collateral edits.
  The SYSB family-compat header entries (x5a Group 3, still hyphen form) are **preserved verbatim**
  (the bootloader's flash-time family check reads those — patching them would break the flash).
- **fw string discriminator:** the flashed radar now reports `36802-TBA,A160` (comma) vs. the stock
  `36802-TBA-A160` (hyphen) — this is what the `+MARKER` build adds. The comma is the *sole* discriminator
  everywhere in the OP code. The live `0xF181` DID copy can't be pinned without a live capture, so all
  10 part-number-record copies are patched (reviewer-endorsed simplest-correct option).

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

### 3b. The forward override (OP-2) — lens1 FIXED
- `hondacan.create_acc_commands(... , radar_aeb=None)`. With `radar_aeb=None` the function is
  **byte-identical to today**.
- **lens1 fix:** the override now fires only on an **actual commanded decel** — `AEB_BRAKING` or
  `BRAKE_REQUEST` asserted **AND** `ACCEL_COMMAND < 0`. The prior code forced `BRAKE_REQUEST=1` on the
  PREPARE-only union (`AEB_STATUS|AEB_PREPARE|AEB_BRAKING|BRAKE_REQUEST`, no sign check), which would
  inject a spurious brake on a PREPARE-only pre-charge or a non-negative accel. PREPARE-only frames are
  no longer forwarded as braking.
- When it does fire, it clobbers `ACCEL_COMMAND` with the radar's decel **clamped to
  `HONDA_BOSCH_RELOCATE_ACCEL_MIN = -10.0 m/s²`** (== the panda -1000 centiunit relocate floor; OP-side
  defense in depth so a malformed/over-range radar decel can't reach the wire below the panda floor) and
  sets `BRAKE_REQUEST`/`AEB_STATUS`/`AEB_PREPARE`/`AEB_BRAKING` **before** `make_can_msg`, so the
  re-checksummed 0x1DF carries radar-AEB intent. It runs last, so it wins same-cycle vs. the
  op-generated accel (correct safety polarity).
- `carcontroller` caches `self.radar_flashed` once at construction and passes
  `radar_aeb=(CS.radar_acc_relocated if self.radar_flashed else None)`. Because `radar_acc_relocated` is
  now `None` when 0x4F0 is stale (MAJOR #4), a frozen 0x4F0 cleanly degrades to plain OP-ACC here.
- The `AEB_*` keys are valid `ACC_CONTROL` packer keys (BO_ 479 via `_bosch_radar_acc.dbc`,
  present in the generated Civic pt DBC) and default to 0 when omitted — adding them only sets
  bits, no schema change.

### 3c. The panda floor change (OP-5) — MAJOR #5 reconciled
- `HONDA_PARAM_BOSCH_LONG` is **hoisted out of `#ifdef ALLOW_DEBUG`** so `honda_bosch_long` is
  settable on **release** panda builds. Without this, 0x1DF is never whitelisted and all op-long
  TX is dropped on release firmware. This is the **pre-existing op-long enablement mechanism**; the
  hoist makes it reachable on release, which is a real (but in-kind) widening — the reviewer should
  still weigh it. **MAJOR #5 reconciliation:** the hoist no longer widens the *relaxed AEB floor*.
- New `HONDA_BOSCH_RELOCATE_LONG_LIMITS` with `min_accel = -1000` centiunits (**-10 m/s2**),
  selected for the **0x1DF accel/gas check only** when `honda_bosch_relocate_long` is set. This
  admits a verbatim forward of full-authority factory AEB decel instead of clipping it at the
  default `-350` / -3.5 m/s2 (a clip would mean *partial* braking at the emergency moment).
- `honda_bosch_relocate_long` is the **sole gate** for the -1000 floor and requires **both**
  `honda_bosch_long` AND the `BOSCH_RELOCATE` flag. So even if `BOSCH_LONG` is reachable on a release
  panda for some other Bosch car, that car still gets the stock -350 floor; only a car that **also**
  sets `BOSCH_RELOCATE` (the production `interface.py` sets it solely for `RADAR_FW_RELOCATED`) sees -10.
- The radarless `0x1C8` path and Bosch-CANFD keep the original `-350` floor — **unchanged**, independent
  of either flag.
- `test_honda.py` adds `TestHondaBoschRelocateLongSafety` exercising the -10.0 m/s2 0x1DF floor;
  the existing bosch-long and CANFD-long tests keep MIN_ACCEL=-3.5. Verified out-of-band by a
  sanitizer-free cffi probe of `safety.c` (the repo harness links `-fsanitize=undefined` / libubsan,
  which this Windows MinGW toolchain lacks): RELOCATE admits down to -1000 and rejects -1001; plain
  `BOSCH_LONG` rejects -1000 (floor stays -350). See §6.

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

1. **Staleness of `radar_acc_relocated` — FIXED.** `carstate.update` now freshness-gates the snapshot:
   it compares the `ACC_CONTROL_RELOCATED` per-signal `ts_nanos` against the parser clock
   (`_last_update_nanos`, the same field `radar_interface.py` uses for `BOSCH_RADAR_STALE_S`) and sets
   `radar_acc_relocated = None` when the 0x4F0 source has been silent for more than
   `RADAR_RELOCATED_STALE_S = 0.15 s` (≈3 missed 17 Hz frames). A frozen 0x4F0 therefore degrades to
   plain OP-ACC within ~0.15 s instead of replaying a stale phantom-brake. The 0x4F0 message is now
   subscribed **explicitly** (MINOR (a)) so it registers with a real timeout and a populated `ts_nanos`.
2. **Release-build op-long hoist (OP-5) — bounded by MAJOR #5.** Hoisting `HONDA_PARAM_BOSCH_LONG` out
   of `ALLOW_DEBUG` still widens what release panda firmware *permits for op-long* (in-kind with the
   pre-existing mechanism) and is worth a deliberate sign-off. But the **relaxed -10 floor no longer
   leaks** with it: it is gated solely on `BOSCH_RELOCATE` (§3c).
3. **Forward override OP-side clamp — ADDED (lens1).** The override now clamps the forwarded decel to
   `-10.0 m/s²` (the panda floor) on the OP side as defense in depth, and only fires on a real commanded
   decel. The panda check remains the authoritative backstop. (A *rate*-limit is still not added — the
   radar's own AEB ramp + the panda floor are the bounds; flagged for the reviewer if a slew limit is
   wanted.)
4. **`radar_acc_relocated` key access hardened.** The override now reads `ACCEL_COMMAND` via
   `.get('ACCEL_COMMAND', 0.0)` (and the AEB bits via `.get(...)`), so a malformed snapshot can no longer
   `KeyError`. OP-3 still always defines the signal; this just removes the hard coupling.
5. **Secure-boot may refuse the modified radar image** (section 2). Until that is resolved on a
   spare radar, the entire OP side is exercising a code path no real car can yet produce. **Unchanged.**
6. **`pcmCruise=False` forced** for the flashed car — confirm this matches the intended cruise
   button / set-speed UX for op-long on this platform. **Unchanged (UX question, not a fix).**
7. **MINOR (c) — `MAYBE_DISENGAGE_COMMAND` / `ALERT` (bits 41/54) are NOT forwarded.** The forward
   override carries `ACCEL_COMMAND` + the AEB status bits only. The radar's maybe-disengage / alert bits
   on 0x4F0 are not relayed to 0x1DF. Out of scope for the AEB-decel forward, but noted so the reviewer
   knows those signals are dropped (no driver-facing alert is synthesized from them on this branch).

---

## 6. Validation performed on this branch (no device, no bus)

- `python -m py_compile` on all changed Python files (interface.py, carstate.py, hondacan.py) and the
  two new test modules — **PASS**.
- `gcc -fsyntax-only` on `opendbc/safety/tests/libsafety/safety.c` (the real safety TU) **with and
  without `-DALLOW_DEBUG`** — **PASS both** (confirms the ALLOW_DEBUG hoist + relocate flag leave no
  dangling refs).
- **New INERT unit tests run and PASS (Python 3.13, `openpilot.common.params` stubbed since the full
  openpilot package isn't importable in this env):**
  - `tests/test_relocate_init.py` (7 tests): the production `_get_params` sets `BOSCH_RELOCATE` +
    forces op-long for `RADAR_FW_RELOCATED` (and NOT for stock / 0x280 radars); `init()` skips the
    radar mute when flashed, still mutes for stock op-long, never mutes with op-long off; `deinit()`
    re-enables with `CP_SP=None`. **This is the BLOCKER #2 "production path sets the flag" proof** the
    reviewer asked for — the panda `TestHondaBoschRelocateLongSafety` sets the flag directly (unit test
    of the panda layer in isolation), while this interface test proves the real `CarParams` carries it.
  - `tests/test_relocate_forward.py` (6 tests): lens1 — `None`=passthrough, PREPARE-only no brake,
    status-set-but-nonnegative-accel no brake, real braking forwarded, over-range decel clamped to
    -10.0, `BRAKE_REQUEST`-only-with-decel forwarded.
- **Panda -1000 floor verified out-of-band:** the repo's `libsafety_py` test harness links
  `-fsanitize=undefined` (needs libubsan, absent in this Windows MinGW toolchain), so `pytest
  test_honda.py::TestHondaBoschRelocateLongSafety` fails to *link* (environmental, not logic). A
  sanitizer-free cffi probe compiled `safety.c` with `-DALLOW_DEBUG` and exercised the 0x1DF accel
  check directly: `BOSCH_LONG|BOSCH_RELOCATE` admits down to -1000 / rejects -1001; plain `BOSCH_LONG`
  rejects -1000 (floor stays -350). This is exactly the assertion `TestHondaBoschRelocateLongSafety`
  makes; it will pass in a CI env that has libubsan / the scons build.
- fw-discriminator check: `RADAR_FW_RELOCATED.replace(b',', b'-') == RADAR_FW_0X280_INGEST` — True
  (comma is the sole difference). Flag values: `RADAR_FLASHED=16`, `BOSCH_RELOCATE=32`.
- **Not run:** the full panda safety unit-test suite under pytest (libubsan/scons unavailable here),
  the DBC generator, and any on-device / replay test.

---

## 7. Bottom line for the reviewer

The architecture is coherent and the per-atom changes are tightly scoped and gated on the flashed
fw string, so stock cars are unaffected. The adversarial-review blockers/majors are now fixed
(BLOCKER #2, MAJOR #3/#4/#5, lens1) and the corrected `.rwd` carries the comma marker, so the OP
gating actually engages on the real artifact. The **staleness phantom-brake is closed** (freshness
gate, §5.1). The one thing that still needs a human decision before this goes anywhere near a car is
**the W1/W2 fail-dark AEB regression (section 4)** — accepted by the operator but a genuine downgrade
of the most critical safety function, and intrinsic to the design (NOT fixable in software on this
branch). Everything here remains INERT until that tradeoff is signed off and the secure-boot gate is
cleared on a spare radar.

---

## 8. Fixes applied (adversarial-review pass)

| Fix | Severity | File(s) | What changed |
|---|---|---|---|
| #2 | BLOCKER | `honda/interface.py` (+`tests/test_relocate_init.py`) | `_get_params` ORs `HondaSafetyFlags.BOSCH_RELOCATE` into the Bosch-long `safetyParam` for the relocated radar, so `honda_bosch_relocate_long` is true on the panda and the -1000 floor is used (forwarded AEB no longer hard-dropped to 0). |
| #3 | MAJOR | `honda/interface.py` (+test) | `init()` skips `disable_ecu` (radar mute) when `CP_SP & RADAR_FLASHED`; `deinit()` passes `CP_SP=None` through the corrected signature so re-enable still runs. |
| #4 | MAJOR | `honda/carstate.py` | Freshness gate (`RADAR_RELOCATED_STALE_S = 0.15 s`, `ts_nanos` vs parser clock) → `radar_acc_relocated = None` when 0x4F0 is stale. + MINOR (a) explicit 0x4F0 subscription @17 Hz. |
| #5 | MAJOR | `safety/modes/honda.h` | Relaxed -1000 floor gated SOLELY on `BOSCH_RELOCATE` (= `BOSCH_LONG && BOSCH_RELOCATE`); the `ALLOW_DEBUG` `BOSCH_LONG` hoist no longer widens the relaxed floor to all Bosch. 0x1C8 stays -350. |
| lens1 | MAJOR | `honda/hondacan.py` (+`tests/test_relocate_forward.py`) | Override fires only on `AEB_BRAKING`/`BRAKE_REQUEST` **and** `ACCEL_COMMAND < 0` (not PREPARE-only); forwarded accel clamped to `HONDA_BOSCH_RELOCATE_ACCEL_MIN = -10.0`; `.get()` key access. |
| (b) | MINOR | `honda/interface.py` | Comment at the relocate-gate: the comma fw intentionally subsumes the 0x280-ingest radar-live assertion (superset, not a separate radar). |
| (c) | MINOR | this doc (§5.7) | Noted that `MAYBE_DISENGAGE_COMMAND`/`ALERT` (bits 41/54) are not forwarded. |
| .rwd | — | `firmware-analysis-kit` (separate repo) | Rebuilt as `36802-TBA,A160-RELOCATE+MARKER-1DF-to-4F0.rwd.gz` carrying the comma `RADAR_FW_RELOCATED` marker (10 DID copies). Byte-diff clean: 22 bytes (10 relocate + 10 marker + 2 CRC). CRC16 `0x9C31→0x1D1B`. Study artifact, NOT flashed. |

All fixes are on the same branch `civic-bosch-0x4f0-relocate-forward`, committed per-fix. Still INERT:
no flash, no CAN/UDS TX, no device deploy.
