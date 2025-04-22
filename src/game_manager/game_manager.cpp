#include "game_manager.hpp"

#include <godot_cpp/classes/packed_scene.hpp>
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
    if(get_node<Player>("../Player")) {
        player = get_node<Player>("../Player");
    }

    if(get_node<Node2D>("../Area")) {
        area_container = get_node<Node2D>("../Area");
    }
    if(player != nullptr && area_container != nullptr) {
        load_area(starting_area);
    }
}

void GameManager::load_area(const int32_t p_area_number) {
    area_name = "area_";
    area_name += std::to_string(p_area_number).c_str();
    area_path = "res://assets/scenes/areas/area_";
    String path = area_path + std::to_string(p_area_number).c_str() + ".tscn";
    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load(path);
    if(scene == nullptr) { return; }
    if(area_container->get_child_count() > 0) {
        for(int32_t i{}; i < area_container->get_child_count(); i++) {
            area_container->get_child(i)->queue_free();
       }
    }

    if(scene->can_instantiate()) {
        Node *instance = scene->instantiate();
        area_name = instance->get_name();
        area_container->call_deferred("add_child", instance);
    }
    call_deferred("_on_tree_exited");
}
void GameManager::load_area_from_path(const String p_scene_path) {
    area_path = p_scene_path;
    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load(p_scene_path);
    if(scene == nullptr) { return; }
    if(area_container->get_child_count() > 0) {
        for(int32_t i{}; i < area_container->get_child_count(); i++) {
            area_container->get_child(i)->queue_free();
       }
    }

    if(scene->can_instantiate()) {
        Node *instance = scene->instantiate();
        area_name = instance->get_name();
        area_container->call_deferred("add_child", instance);
    }
    call_deferred("_on_tree_exited");
}

void GameManager::next_area(const String p_scene_path) {
    //Ref<Script> game_manager_script = ResourceLoader::get_singleton()->load("res://assets/scripts/game_manager.gd", "Script");
    //String path = game_manager_script->call("set_next_area");
    if(p_scene_path == "") {
        load_area(++current_area);
    } else {
        load_area_from_path(p_scene_path);
    }
}

void GameManager::add_energy_cell() {
    ++energy_cells_collected;
    if(energy_cells_collected == 4) {
        if(get_node<AreaExit>("../Area/" + area_name + "/AreaExit")) {
            get_node<AreaExit>("../Area/" + area_name + "/AreaExit")->open();
        }
    }
}

void GameManager::_on_tree_exited() {
    if(get_node<Node2D>("../Area/" + area_name + "/PlayerStartPosition")) {
        reset_energy_cells();
        Vector2 position = get_node<Node2D>("../Area/" + area_name + "/PlayerStartPosition")->get_position();
        player->teleport_to_position(position);
    } else if(get_node<Node2D>(area_path + "/PlayerStartPosition")) {
        reset_energy_cells();
        player->teleport_to_position(get_node<Node2D>(area_path + "/PlayerStartPosition")->get_position());
    }
}
