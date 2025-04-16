#include "area_exit.hpp"

#include <godot_cpp/classes/character_body2d.hpp>

#include "../player.hpp"
#include "../../game_manager/game_manager.hpp"

using namespace godot;

void AreaExit::_ready() {
    connect("body_entered", Callable(this, "_on_body_entered"));
}

void AreaExit::_on_body_entered(CharacterBody2D *body) {
    if(get_node<Player>("../Player") && overlaps_body(get_node<Player>("../Player"))) {
        if(body == get_node<Player>("../Player")) {
            GameManager::get_singleton()->next_level();
         }
    }
}
