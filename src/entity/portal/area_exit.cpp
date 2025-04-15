#include "area_exit.hpp"

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/editor_file_system_directory.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/script.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "../player.hpp"
//#include "../../game_manager/game_manager.hpp"

using namespace godot;

void AreaExit::_ready() {
    connect("body_entered", Callable(this, "_on_body_entered"));
}

void AreaExit::_on_body_entered(CharacterBody2D *body) {
    if(get_node<Player>("../Player") && overlaps_body(get_node<Player>("../Player"))) {
        if(body == get_node<Player>("../Player")) {
            Ref<Script> game_manager_script = ResourceLoader::get_singleton()->load("res://assets/scripts/game_manager.gd", "Script");
            String path = game_manager_script->call("set_next_level");
            SceneTree *scene_tree = get_tree();
            scene_tree->change_scene_to_file(path);
         }
    }
}
