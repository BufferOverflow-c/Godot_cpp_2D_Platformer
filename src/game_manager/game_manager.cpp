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
    //area_container = get_tree()->get_first_node_in_group("area_container");
    //player = get_tree()->get_first_node_in_group("player");
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

    // TODO:: figure out how to call deferred
    if(scene->can_instantiate()) {
        Node *instance = scene->instantiate();
        area_name = instance->get_name();
        area_container->add_child(instance);
        area_container->get_child(0)->set_name(instance->get_name());
    }
    if(get_node<Node2D>("../Area/" + area_name + "/PlayerStartPosition")) {
        reset_energy_cells();
        Vector2 position = get_node<Node2D>("../Area/" + area_name + "/PlayerStartPosition")->get_position();
        UtilityFunctions::print(position);
        player->set_position(position);
    }
}

void GameManager::next_area() {
    //Ref<Script> game_manager_script = ResourceLoader::get_singleton()->load("res://assets/scripts/game_manager.gd", "Script");
    //String path = game_manager_script->call("set_next_area");
    load_area(++current_area);
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
    reset_energy_cells();
}
//Variant call_deferred_thread_group(const StringName &p_method, const Args &...p_args) {
//	std::array<Variant, 1 + sizeof...(Args)> variant_args{ Variant(p_method), Variant(p_args)... };
//	std::array<const Variant *, 1 + sizeof...(Args)> call_args;
//	for (size_t i = 0; i < variant_args.size(); i++) {
//		call_args[i] = &variant_args[i];
//	}
//	return call_deferred_thread_group_internal(call_args.data(), variant_args.size());
//}
//void set_deferred_thread_group(const StringName &p_property, const Variant &p_value);
//void notify_deferred_thread_group(int32_t p_what);
