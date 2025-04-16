#include "game_manager.hpp"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
//#include <godot_cpp/classes/script.hpp>

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

void GameManager::next_level() {
    //Ref<Script> game_manager_script = ResourceLoader::get_singleton()->load("res://assets/scripts/game_manager.gd", "Script");
    //String path = game_manager_script->call("set_next_level");
    ++current_level;
    String path = area_path + std::to_string(current_level).c_str() + ".tscn";
    SceneTree *scene_tree = get_tree();
    scene_tree->change_scene_to_file(path);
}
