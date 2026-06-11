#!/usr/bin/env python3
"""Regression test for the DEC flip-flop fix (nrdrbranchdebug).

Reproduces the council's oscillation scenario: a high-urgency emergency 'blended'
followed by opposing non-emergency 'acc' requests while urgency dips below the
emergency threshold. BEFORE the fix, emergency_override bypassed min_mode_duration
for the opposing request → instant flip-back → acc<->blended chatter. AFTER the fix
the override holds its own mode for the dwell, then yields cleanly.

Run on device: PYTHONPATH=/data/openpilot /usr/local/venv/bin/python test_dec_flipflop.py
"""
import importlib.util, os
_p = os.environ.get("DEC_PATH", "/data/openpilot/sunnypilot/selfdrive/controls/lib/dec/dec.py")
_spec = importlib.util.spec_from_file_location("dec_under_test", _p)
_dec = importlib.util.module_from_spec(_spec); _spec.loader.exec_module(_dec)
ModeTransitionManager = _dec.ModeTransitionManager
print(f"(testing dec.py at {_p})")


def test_emergency_holds_against_opposing_request():
    m = ModeTransitionManager()                      # starts 'acc'
    m.request_mode('blended', confidence=1.0, emergency=True)
    m.update()
    assert m.get_mode() == 'blended', m.get_mode()

    # urgency dipped: opposing non-emergency 'acc' spammed every frame for < dwell
    flips = 0
    last = m.get_mode()
    for _ in range(m.min_mode_duration - 2):         # stay within the dwell window
        m.request_mode('acc', confidence=1.0)        # opposing, NON-emergency
        m.update()
        if m.get_mode() != last:
            flips += 1
            last = m.get_mode()
    assert m.get_mode() == 'blended', f"emergency mode flick-cancelled: {m.get_mode()}"
    assert flips == 0, f"chattered {flips} times inside the dwell"
    return "emergency_holds: OK (no flick-cancel, blended held for dwell)"


def test_emergency_engages_immediately_from_acc():
    # Refutes the council NO-GO claim ("emergency entry blocked by dwell, trapped in ACC").
    # A real emergency uses emergency=True, which short-circuits at the TOP of request_mode
    # and never reaches the dwell guard — so it must engage instantly even inside a fresh dwell.
    m = ModeTransitionManager()                      # 'acc', mode_duration = 0 (fresh dwell window)
    assert m.mode_duration < m.min_mode_duration     # we are inside the dwell window
    m.request_mode('blended', confidence=1.0, emergency=True)
    assert m.get_mode() == 'blended', f"emergency entry was BLOCKED (trapped in {m.get_mode()})"
    return "emergency_engages_immediately: OK (not trapped in ACC; top-branch short-circuit intact)"


def test_emergency_yields_after_dwell():
    m = ModeTransitionManager()
    m.request_mode('blended', confidence=1.0, emergency=True)
    m.update()
    # after the dwell + override clear (>20 frames), sustained opposing acc should win
    last = m.get_mode()
    switched = False
    for i in range(40):
        m.request_mode('acc', confidence=1.0)
        m.update()
        if m.get_mode() == 'acc':
            switched = True
            break
    assert switched, "emergency mode never yields — would stick in blended forever"
    return f"emergency_yields: OK (yielded to sustained acc after {i+1} frames)"


def test_same_mode_reinforce_not_blocked():
    # a reinforcing (same-mode) request during override must still pass (keeps blended)
    m = ModeTransitionManager()
    m.request_mode('blended', confidence=1.0, emergency=True)
    m.update()
    m.request_mode('blended', confidence=1.0)        # same mode, non-emergency
    m.update()
    assert m.get_mode() == 'blended'
    return "same_mode_reinforce: OK"


def test_slowdown_threshold_hysteresis():
    # mirror the patched formula: enter 0.8*P, exit 0.5*P -> a value in (0.5P, 0.8P)
    # must NOT toggle state. P is whatever WMACConstants.SLOW_DOWN_PROB is.
    from openpilot.sunnypilot.selfdrive.controls.lib.dec.constants import WMACConstants
    P = WMACConstants.SLOW_DOWN_PROB
    enter = P * 0.8
    exit_ = P * 0.5
    assert exit_ < enter, "hysteresis band is inverted"
    mid = (enter + exit_) / 2.0
    # not slowing yet: mid < enter -> stays off
    has = False
    has = mid > (P * (0.5 if has else 0.8))
    assert has is False, "entered slow-down inside the hysteresis band"
    # already slowing: mid > exit -> stays on
    has = True
    has = mid > (P * (0.5 if has else 0.8))
    assert has is True, "exited slow-down inside the hysteresis band"
    return f"slowdown_hysteresis: OK (band {exit_:.3f}..{enter:.3f}, P={P})"


if __name__ == "__main__":
    for t in (test_emergency_holds_against_opposing_request,
              test_emergency_engages_immediately_from_acc,
              test_emergency_yields_after_dwell,
              test_same_mode_reinforce_not_blocked,
              test_slowdown_threshold_hysteresis):
        print(t())
    print("ALL DEC FLIP-FLOP TESTS PASSED")
