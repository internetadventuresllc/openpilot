"""
nrdr experimental settings panel.
"""
from enum import IntEnum

from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.sunnypilot.widgets.list_view import simple_button_item_sp, toggle_item_sp, LineSeparatorSP
from openpilot.system.ui.widgets.scroller_tici import Scroller
from openpilot.system.ui.widgets import Widget
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.nrdr_sub_layouts.learned_parameters import LearnedParametersLayout
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.nrdr_sub_layouts.lateral_tuning import LateralTuningLayout
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.nrdr_sub_layouts.override_tuning import OverrideTuningLayout
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.nrdr_sub_layouts.longitudinal_tuning import LongitudinalTuningLayout
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.nrdr_sub_layouts.party_tricks import PartyTricksLayout


class PanelType(IntEnum):
  NRDR = 0
  LATERAL = 1
  OVERRIDE = 2
  LONGITUDINAL = 3
  PARTY_TRICKS = 4
  LEARNED = 5


class NrdrLayout(Widget):
  def __init__(self):
    super().__init__()

    self._current_panel = PanelType.NRDR
    self._learned_params_layout = LearnedParametersLayout(lambda: self._set_current_panel(PanelType.NRDR))
    self._lateral_layout = LateralTuningLayout(lambda: self._set_current_panel(PanelType.NRDR))
    self._override_layout = OverrideTuningLayout(lambda: self._set_current_panel(PanelType.NRDR))
    self._longitudinal_layout = LongitudinalTuningLayout(lambda: self._set_current_panel(PanelType.NRDR))
    self._party_tricks_layout = PartyTricksLayout(lambda: self._set_current_panel(PanelType.NRDR))

    items = self._initialize_items()
    self._scroller = Scroller(items, line_separator=False, spacing=0)

  def _initialize_items(self):
    self._learned_button = simple_button_item_sp(
      button_text=lambda: tr("Learned Parameters"),
      button_width=800,
      callback=lambda: self._set_current_panel(PanelType.LEARNED),
    )
    self._lateral_button = simple_button_item_sp(
      button_text=lambda: tr("Lateral Tuning"),
      button_width=800,
      callback=lambda: self._set_current_panel(PanelType.LATERAL),
    )
    self._override_button = simple_button_item_sp(
      button_text=lambda: tr("Override Tuning"),
      button_width=800,
      callback=lambda: self._set_current_panel(PanelType.OVERRIDE),
    )
    self._longitudinal_button = simple_button_item_sp(
      button_text=lambda: tr("Longitudinal Tuning"),
      button_width=800,
      callback=lambda: self._set_current_panel(PanelType.LONGITUDINAL),
    )
    self._party_tricks_button = simple_button_item_sp(
      button_text=lambda: tr("Party Tricks"),
      button_width=800,
      callback=lambda: self._set_current_panel(PanelType.PARTY_TRICKS),
    )

    self._radar_tryout = toggle_item_sp(
      param="HondaCivicRadarTryout",
      title=lambda: tr("Try Honda Bosch Radar (experimental)"),
      description=lambda: tr("EXPERIMENTAL — Honda Bosch radar. When ON, openpilot reads the factory Bosch radar's fine-range objects (0x280) and treats this car like a fingerprint-matched radar car (radarUnavailable=False + the custom honda_civic_bosch_radar DBC). If you ALSO enable openpilot experimental/alpha longitudinal, this radar WILL feed openpilot's lead tracking and command braking/acceleration — exactly like a matched car. With openpilot longitudinal OFF (stock ACC) it is perception only. The 0x280 decode is reverse-engineered and cross-car validated (~0.99) but NOT verified on your specific car: before enabling openpilot longitudinal, VALIDATE that lead distance and closing-rate match reality. Honda Civic Bosch only. Leave OFF if unsure."),
      initial_state=False,
    )

    return [
      self._learned_button,
      LineSeparatorSP(40),
      self._lateral_button,
      LineSeparatorSP(40),
      self._override_button,
      LineSeparatorSP(40),
      self._longitudinal_button,
      LineSeparatorSP(40),
      self._party_tricks_button,
      LineSeparatorSP(40),
      self._radar_tryout,
    ]

  def _set_current_panel(self, panel: PanelType):
    self._current_panel = panel

  def _render(self, rect):
    if self._current_panel == PanelType.LEARNED:
      self._learned_params_layout.render(rect)
    elif self._current_panel == PanelType.LATERAL:
      self._lateral_layout.render(rect)
    elif self._current_panel == PanelType.OVERRIDE:
      self._override_layout.render(rect)
    elif self._current_panel == PanelType.LONGITUDINAL:
      self._longitudinal_layout.render(rect)
    elif self._current_panel == PanelType.PARTY_TRICKS:
      self._party_tricks_layout.render(rect)
    else:
      self._scroller.render(rect)

  def show_event(self):
    self._set_current_panel(PanelType.NRDR)
    self._scroller.show_event()
