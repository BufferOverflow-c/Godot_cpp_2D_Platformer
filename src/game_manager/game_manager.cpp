#include "game_manager.hpp"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include "../entity/portal/area_exit.hpp"

// STD
#include <string>

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

void GameManager::_ready() {
    reset_energy_cells();
}

void GameManager::next_level(const String &p_path) {
    //Ref<Script> game_manager_script = ResourceLoader::get_singleton()->load("res://assets/scripts/game_manager.gd", "Script");
    //String path = game_manager_script->call("set_next_level");
    reset_energy_cells();
    if(area_path != "") {
        SceneTree *scene_tree = get_tree();
        scene_tree->change_scene_to_file(area_path);
    } else {
        ++current_level;
        area_path = "res://assets/scenes/areas/area_";
        String path = area_path + std::to_string(current_level).c_str() + ".tscn";
        SceneTree *scene_tree = get_tree();
        scene_tree->change_scene_to_file(path);
    }
}

void GameManager::set_up_area() {
    reset_energy_cells();
}

void GameManager::add_energy_cell() {
    ++energy_cells_collected;
    if(energy_cells_collected == 4) {
        if(get_node<AreaExit>("../AreaExit")) {
            get_node<AreaExit>("../AreaExit")->open();
        }
    }
}
