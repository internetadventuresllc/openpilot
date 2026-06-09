#!/usr/bin/env python3
"""
INERT study-branch test (no device, no CAN). Covers the relocate-forward MAJOR #3 fix:

  CarInterface.init() must NOT disable_ecu (mute the radar) for the flashed/relocated radar, because
  op-long is FORCED True on that car and the forward override reads the radar's relocated 0x4F0 frame.
  Muting the radar there would kill the very source the forward depends on.

A stock op-long Bosch car (no RADAR_FLASHED) must still disable_ecu (unchanged behavior).
The deinit() re-enable path must still run regardless of the flashed gate (CP_SP is None there).
"""
import unittest
from unittest import mock

from opendbc.car import structs
from opendbc.car.honda import interface as honda_interface
from opendbc.car.honda.interface import CarInterface
from opendbc.car.honda.values import CAR, HondaSafetyFlags, RADAR_FW_RELOCATED, RADAR_FW_0X280_INGEST
from opendbc.sunnypilot.car.honda.values_ext import HondaFlagsSP

Ecu = structs.CarParams.Ecu


def _fw(fwVersion: bytes, ecu=Ecu.fwdRadar):
  fw = structs.CarParams.CarFw()
  fw.ecu = ecu
  fw.fwVersion = fwVersion
  return fw


def _empty_fingerprint():
  # HONDA_CIVIC_BOSCH: powertrain on bus 1. _get_params only indexes existing-or-membership tests, so
  # four empty per-bus dicts are sufficient.
  return {0: {}, 1: {}, 2: {}, 3: {}}


def _make_cp(op_long=True):
  CP = structs.CarParams()
  CP.carFingerprint = CAR.HONDA_CIVIC_BOSCH
  CP.openpilotLongitudinalControl = op_long
  # hondaBosch safety config so CanBus(CP).pt resolves (powertrain on bus 1 for non-radarless Bosch)
  cfg = structs.CarParams.SafetyConfig()
  cfg.safetyModel = structs.CarParams.SafetyModel.hondaBosch
  CP.safetyConfigs = [cfg]
  return CP


def _make_cp_sp(flashed=False):
  CP_SP = structs.CarParamsSP()
  if flashed:
    CP_SP.flags |= HondaFlagsSP.RADAR_FLASHED.value
  return CP_SP


class TestHondaRelocateInit(unittest.TestCase):
  def test_flashed_radar_skips_disable_ecu(self):
    """RADAR_FLASHED + op-long -> radar must stay live -> disable_ecu NOT called."""
    CP = _make_cp(op_long=True)
    CP_SP = _make_cp_sp(flashed=True)
    with mock.patch.object(honda_interface, "disable_ecu") as m:
      CarInterface.init(CP, CP_SP, can_recv=lambda *a, **k: [], can_send=lambda *a, **k: None)
    m.assert_not_called()

  def test_stock_op_long_still_disables_ecu(self):
    """No RADAR_FLASHED + op-long -> stock behavior: radar muted -> disable_ecu called once."""
    CP = _make_cp(op_long=True)
    CP_SP = _make_cp_sp(flashed=False)
    with mock.patch.object(honda_interface, "disable_ecu") as m:
      CarInterface.init(CP, CP_SP, can_recv=lambda *a, **k: [], can_send=lambda *a, **k: None)
    m.assert_called_once()

  def test_no_op_long_never_disables_ecu(self):
    """op-long off -> disable_ecu never called (regardless of flashed state)."""
    for flashed in (True, False):
      CP = _make_cp(op_long=False)
      CP_SP = _make_cp_sp(flashed=flashed)
      with mock.patch.object(honda_interface, "disable_ecu") as m:
        CarInterface.init(CP, CP_SP, can_recv=lambda *a, **k: [], can_send=lambda *a, **k: None)
      m.assert_not_called()

  def test_deinit_reenable_runs_with_cp_sp_none(self):
    """deinit() passes CP_SP=None; the re-enable disable_ecu (ENABLE comm-control) must still run for a
    stock op-long car. The CP_SP-None branch must be treated as 'not flashed' so re-enable is not gated."""
    CP = _make_cp(op_long=True)
    with mock.patch.object(honda_interface, "disable_ecu") as m:
      CarInterface.deinit(CP, can_recv=lambda *a, **k: [], can_send=lambda *a, **k: None)
    m.assert_called_once()


class TestHondaRelocateGetParams(unittest.TestCase):
  """BLOCKER #2 production path: _get_params must OR HondaSafetyFlags.BOSCH_RELOCATE into the
  Bosch-long safetyParam ONLY for the RADAR_FW_RELOCATED radar. Without it, panda keeps the -350
  floor and hard-drops a forwarded full-authority AEB. This is the path that lets the panda
  TestHondaBoschRelocateLongSafety reflect the real car (the safety unit test sets the flag directly;
  THIS test proves the production CarParams actually carries it)."""

  def _get_params(self, car_fw):
    return CarInterface.get_params(CAR.HONDA_CIVIC_BOSCH, _empty_fingerprint(), car_fw,
                                   alpha_long=False, is_release=False, docs=False)

  def test_relocated_radar_sets_bosch_relocate_and_forces_op_long(self):
    CP = self._get_params([_fw(RADAR_FW_RELOCATED)])
    param = CP.safetyConfigs[-1].safetyParam
    self.assertTrue(CP.openpilotLongitudinalControl, "relocated radar must force op-long")
    self.assertTrue(param & HondaSafetyFlags.BOSCH_LONG.value, "op-long must set BOSCH_LONG")
    self.assertTrue(param & HondaSafetyFlags.BOSCH_RELOCATE.value,
                    "relocated radar must set BOSCH_RELOCATE (the -1000 floor gate)")

  def test_0x280_ingest_radar_does_not_set_bosch_relocate(self):
    # The 0x280-ingest (hyphen) radar is NOT the relocate path: with alpha_long off it stays stock-long
    # (op-long off), so neither BOSCH_LONG nor BOSCH_RELOCATE is set.
    CP = self._get_params([_fw(RADAR_FW_0X280_INGEST)])
    param = CP.safetyConfigs[-1].safetyParam
    self.assertFalse(param & HondaSafetyFlags.BOSCH_RELOCATE.value,
                     "non-relocated radar must NOT set BOSCH_RELOCATE")

  def test_stock_radar_does_not_set_bosch_relocate(self):
    CP = self._get_params([_fw(b"36802-TBA-A030")])
    param = CP.safetyConfigs[-1].safetyParam
    self.assertFalse(param & HondaSafetyFlags.BOSCH_RELOCATE.value)


if __name__ == "__main__":
  unittest.main()
