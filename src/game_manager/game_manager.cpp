#include "game_manager.hpp"

#include "../entity/portal/area_exit.hpp"
#include "../gameplay/gameplay.hpp"
#include "../ui/hud.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

GameManager *GameManager::singleton = nullptr;

GameManager::GameManager() {
    singleton = this;
}

GameManager::~GameManager() {
    if(singleton == this) {
        singleton = nullptr;
    }
}

GameManager *GameManager::get_singleton() {
	return singleton;
}

void GameManager::_ready() {}

void GameManager::next_area(const String p_scene_path) {
    if(get_node_or_null("../../Gameplay") != nullptr) {
        Gameplay *gameplay{};
        gameplay = get_node<Gameplay>("../../Gameplay");
        gameplay->next_area(p_scene_path);
        reset_energy_cells();
        HUD::get_singleton()->set_energy_cell_number(energy_cells_collected);
        HUD::get_singleton()->update_energy_cell_label();
        HUD::get_singleton()->portal_closed();
    }
}

void GameManager::add_energy_cell() {
    String area_path{};
    for(int32_t i{}; i < get_node<Node2D>("../Area")->get_child_count(); i++) {
        area_path = get_node<Node2D>("../Area")->get_child(i)->get_path();
    }

    ++energy_cells_collected;
    HUD::get_singleton()->set_energy_cell_number(energy_cells_collected);
    HUD::get_singleton()->update_energy_cell_label();
    if(energy_cells_collected == 4) {
        get_node<AreaExit>(area_path + "/AreaExit")->open();
        HUD::get_singleton()->portal_open();
    }
}
