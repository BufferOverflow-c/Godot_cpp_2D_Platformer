#include "gameplay.hpp"

#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "../game_manager/game_manager.hpp"

// STD
#include <string>

using namespace godot;

Gameplay::Gameplay() = default;

Gameplay::~Gameplay() = default;

void Gameplay::_ready() {
    player = get_node<Player>("Player");
    area_container = get_node<Node2D>("Area");
    //area_path = "";
    //area_name = "";
    start_game();
}

void Gameplay::start_game() {
    load_area(starting_area);
}

void Gameplay::next_area(const String p_scene_path) {
    if(p_scene_path == "") {
        load_area(++current_area);
    } else {
        load_area_from_path(p_scene_path);
    }
}

void Gameplay::load_area(const int32_t p_area_number) {
    area_name = "area_";
    area_name += std::to_string(p_area_number).c_str();
    area_path = "res://assets/scenes/areas/area_";
    String path = area_path + std::to_string(p_area_number).c_str() + ".tscn";
    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load(path);
    if(scene == nullptr) { return; }

    unload_area();

    if(scene->can_instantiate()) {
        Node *instance = scene->instantiate();
        area_name = instance->get_name();
        area_container->call_deferred("add_child", instance);
    }
    call_deferred("_on_tree_exited");
}
void Gameplay::load_area_from_path(const String p_scene_path) {
    area_path = p_scene_path;
    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load(p_scene_path);
    if(scene == nullptr) { return; }

    unload_area();

    if(scene->can_instantiate()) {
        Node *instance = scene->instantiate();
        area_name = instance->get_name();
        area_container->call_deferred("add_child", instance);
    }
    call_deferred("_on_tree_exited");
}

void Gameplay::unload_area() {
    for(int32_t i{}; i < area_container->get_child_count(); i++) {
        area_container->get_child(i)->queue_free();
    }
}

void Gameplay::_on_tree_exited() {
    String area_container_name = area_container->get_name();
    if(get_node<Node2D>(area_container_name + "/" + area_name + "/PlayerStartPosition")) {
        //GameManager::get_singleton()->reset_energy_cells();
        Vector2 position = get_node<Node2D>(area_container_name + "/" + area_name + "/PlayerStartPosition")->get_position();
        player->teleport_to_position(position);
    } else {
        //GameManager::get_singleton()->reset_energy_cells();
        player->teleport_to_position(get_node<Node2D>(area_path + "/PlayerStartPosition")->get_position());
    }
}
