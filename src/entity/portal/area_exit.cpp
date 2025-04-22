#include "area_exit.hpp"

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

#include "../player.hpp"
#include "../../game_manager/game_manager.hpp"

using namespace godot;

void AreaExit::_ready() {
    close();
    connect("body_entered", Callable(this, "_on_body_entered"));
}

void AreaExit::_on_body_entered(CharacterBody2D *body) {
    if(get_node<Player>("../../../Player") && overlaps_body(get_node<Player>("../../../Player"))) {
        if(is_open && body == get_node<Player>("../../../Player")) {
            GameManager::get_singleton()->next_area(scene);
         }
    }
}

void AreaExit::open() {
    const Rect2 open_region_rect = Rect2(22,0,22,22);
    is_open = true;
    get_node<Sprite2D>("Sprite2D")->set_region_rect(open_region_rect);
}

void AreaExit::close() {
    const Rect2 closed_region_rect = Rect2(0,0,22,22);
    is_open = false;
    get_node<Sprite2D>("Sprite2D")->set_region_rect(closed_region_rect);
}
