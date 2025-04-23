#include "game_manager.hpp"

#include "../entity/portal/area_exit.hpp"
#include "../gameplay/gameplay.hpp"

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
    Gameplay *gameplay{};
    gameplay->next_area(p_scene_path);
    reset_energy_cells();
}

void GameManager::add_energy_cell() {
    String area_path{};
    for(int32_t i{}; i < get_node<Node2D>("../Area")->get_child_count(); i++) {
        area_path = get_node<Node2D>("../Area")->get_child(i)->get_path();
    }

    ++energy_cells_collected;
    if(energy_cells_collected == 4) {
        get_node<AreaExit>(area_path + "/AreaExit")->open();
    }
}
