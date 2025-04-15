#pragma once

#include <godot_cpp/classes/area2d.hpp>

#include <godot_cpp/classes/character_body2d.hpp>

namespace godot {

class AreaExit : public Area2D {
    GDCLASS(AreaExit, Area2D)

public:
    void _ready() override;

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("_on_body_entered", "body"), &AreaExit::_on_body_entered);
    }

    void _on_body_entered(CharacterBody2D *body);

private:
};

}
