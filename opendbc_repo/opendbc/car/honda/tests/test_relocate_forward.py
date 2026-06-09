#!/usr/bin/env python3
"""
INERT study-branch test (no device, no CAN). Covers the lens1 forward-override fix in
hondacan.create_acc_commands(radar_aeb=...):

  - PREPARE-only (radar arming, not yet decelerating) must NOT force a brake event.
  - A non-negative ACCEL_COMMAND must NOT force a brake event (no decel to forward).
  - A real AEB_BRAKING/BRAKE_REQUEST with negative accel IS forwarded, clamped to the panda floor.
  - radar_aeb=None is byte-identical to the no-override path (the verbatim-today guarantee).

Uses a recording fake packer so no compiled DBC is needed.
"""
import unittest

from opendbc.car.honda import hondacan
from opendbc.car.honda.hondacan import HONDA_BOSCH_RELOCATE_ACCEL_MIN
from opendbc.car.honda.values import CAR


class _FakeCAN:
  pt = 1


class _RecordingPacker:
  """Captures the values dict handed to make_can_msg per message name."""
  def __init__(self):
    self.sent = {}

  def make_can_msg(self, name, bus, values):
    self.sent[name] = dict(values)
    return (0, bytes(8), bus)


def _acc(radar_aeb, active=True, accel=0.5):
  packer = _RecordingPacker()
  hondacan.create_acc_commands(packer, _FakeCAN(), enabled=True, active=active, accel=accel, gas=100,
                               stopping_counter=0, car_fingerprint=CAR.HONDA_CIVIC_BOSCH, gas_force=1.0,
                               radar_aeb=radar_aeb)
  return packer.sent["ACC_CONTROL"]


class TestRelocateForwardOverride(unittest.TestCase):
  def test_none_is_passthrough(self):
    v = _acc(None, accel=0.5)
    self.assertEqual(v["ACCEL_COMMAND"], 0.5)
    self.assertEqual(v["BRAKE_REQUEST"], 0)
    self.assertNotIn("AEB_STATUS", v)  # no AEB keys added when not overriding

  def test_prepare_only_does_not_force_brake(self):
    # AEB_PREPARE set, but not braking and accel >= 0 -> NOT a brake event.
    v = _acc({"AEB_PREPARE": 1, "AEB_BRAKING": 0, "BRAKE_REQUEST": 0, "AEB_STATUS": 1, "ACCEL_COMMAND": 0.0})
    self.assertEqual(v["BRAKE_REQUEST"], 0)
    self.assertNotIn("AEB_BRAKING", v)

  def test_status_set_but_nonnegative_accel_does_not_force_brake(self):
    # AEB_STATUS asserted but commanded accel is non-negative (no decel) -> NOT forwarded as braking.
    v = _acc({"AEB_STATUS": 1, "AEB_BRAKING": 1, "BRAKE_REQUEST": 1, "ACCEL_COMMAND": 0.0})
    self.assertEqual(v["BRAKE_REQUEST"], 0)

  def test_real_braking_is_forwarded(self):
    v = _acc({"AEB_STATUS": 1, "AEB_BRAKING": 1, "BRAKE_REQUEST": 1, "AEB_PREPARE": 0, "ACCEL_COMMAND": -4.0})
    self.assertEqual(v["BRAKE_REQUEST"], 1)
    self.assertEqual(v["ACCEL_COMMAND"], -4.0)
    self.assertEqual(v["AEB_BRAKING"], 1)
    self.assertEqual(v["AEB_STATUS"], 1)

  def test_over_range_decel_is_clamped_to_floor(self):
    # A radar decel beyond the panda floor must be clamped on the OP side (defense in depth).
    v = _acc({"AEB_BRAKING": 1, "BRAKE_REQUEST": 1, "ACCEL_COMMAND": -25.0})
    self.assertEqual(v["BRAKE_REQUEST"], 1)
    self.assertEqual(v["ACCEL_COMMAND"], HONDA_BOSCH_RELOCATE_ACCEL_MIN)  # -10.0

  def test_brake_request_only_with_decel_is_forwarded(self):
    # BRAKE_REQUEST alone (no AEB_BRAKING) with negative accel is still a real brake event.
    v = _acc({"BRAKE_REQUEST": 1, "ACCEL_COMMAND": -2.5})
    self.assertEqual(v["BRAKE_REQUEST"], 1)
    self.assertEqual(v["ACCEL_COMMAND"], -2.5)


if __name__ == "__main__":
  unittest.main()
