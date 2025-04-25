#include "hud.hpp"

#include "../gameplay/gameplay.hpp"

// STD
#include <string>

using namespace godot;

HUD *HUD::singleton = nullptr;

HUD::HUD() { singleton = this; }

HUD::~HUD() {
  if (singleton == this) {
    singleton = nullptr;
  }
}

HUD *HUD::get_singleton() { return singleton; }

void HUD::_ready() {
  start_button = Object::cast_to<Button>(get_node_or_null("StartButtonLayer/StartButton"));
  ERR_FAIL_NULL(start_button);
  start_button->connect("pressed", Callable(this, "_on_start_button_clicked"));
}

void HUD::_on_start_button_clicked() {
  Gameplay *gameplay =
      Object::cast_to<Gameplay>(get_node_or_null("../../../Gameplay"));
  ERR_FAIL_NULL(gameplay);

  gameplay->start_game();
}

void HUD::portal_open() {
  if (get_node_or_null("PortalLabel") != nullptr) {
    portal_label = get_node<Label>("PortalLabel");
    portal_label->set_text("Portal open!");
  }
}

void HUD::portal_closed() {
  if (get_node_or_null("PortalLabel") != nullptr) {
    portal_label = get_node<Label>("PortalLabel");
    portal_label->set_text("Portal closed...");
  }
}
void HUD::update_energy_cell_label() {
  if (get_node_or_null("EnergyCellTexture/EnergyCellLabel") != nullptr) {
    energy_cell_label = get_node<Label>("EnergyCellTexture/EnergyCellLabel");
    String num = std::to_string(energy_cell_number).c_str();
    String updated_label = "x " + num;
    energy_cell_label->set_text(updated_label);
  }
}
