#pragma once

#include <godot_cpp/classes/area2d.hpp>

#include <godot_cpp/classes/character_body2d.hpp>

namespace godot {

class AreaExit : public Area2D {
    GDCLASS(AreaExit, Area2D)

public:
    void _ready() override;

    bool get_is_open() const { return is_open; }
    void set_is_open(const bool p_is_open) { is_open = p_is_open; }

    void open();

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("get_is_open"), &AreaExit::get_is_open);
        ClassDB::bind_method(D_METHOD("set_is_open", "p_is_open"), &AreaExit::set_is_open);

        ClassDB::bind_method(D_METHOD("_on_body_entered", "body"), &AreaExit::_on_body_entered);
        ClassDB::bind_method(D_METHOD("open"), &AreaExit::open);
        ClassDB::bind_method(D_METHOD("close"), &AreaExit::close);

        ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_open"), "set_is_open", "get_is_open");
    }

    void _on_body_entered(CharacterBody2D *body);
    void close();

private:
    bool is_open{true};
};

}
