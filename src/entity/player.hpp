#pragma once

#include <godot_cpp/classes/character_body2d.hpp>

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {
class Player : public CharacterBody2D {
    GDCLASS(Player, CharacterBody2D)

public:
    Player();
    ~Player();

    void _ready() override;
    void _physics_process(const double delta) override;

    // getters
    double get_speed() const { return speed; }
    double get_jump_velocity() const { return jump_velocity; }
    double get_speed_modifier() const { return speed_modifier; }
    double get_jump_modifier() const { return jump_modifier; }
    double get_gravity_modifier() const { return gravity_modifier; }
    //int32_t get_energy_cells_collected() const { return energy_cells_collected; }

    // setters
    void set_speed(const double p_speed) { speed = p_speed; }
    void set_jump_velocity(const double p_jump_velocity) { jump_velocity = p_jump_velocity; }
    void set_speed_modifier(const double p_speed_modifier) { speed_modifier = p_speed_modifier; }
    void set_jump_modifier(const double p_jump_modifier) { jump_modifier = p_jump_modifier; }
    void set_gravity_modifier(const double p_gravity_modifier) { gravity_modifier = p_gravity_modifier; }
    //void set_energy_cells_collected(const int32_t p_energy_cells_collected) { energy_cells_collected = p_energy_cells_collected; }

protected:
    static void _bind_methods() {
        // getters && setters
        ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
        ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Player::set_speed);

        ClassDB::bind_method(D_METHOD("get_jump_velocity"), &Player::get_jump_velocity);
        ClassDB::bind_method(D_METHOD("set_jump_velocity", "p_jump_velocity"), &Player::set_jump_velocity);

        ClassDB::bind_method(D_METHOD("get_speed_modifier"), &Player::get_speed_modifier);
        ClassDB::bind_method(D_METHOD("set_speed_modifier", "p_speed_modifier"), &Player::set_speed_modifier);

        ClassDB::bind_method(D_METHOD("get_jump_modifier"), &Player::get_jump_modifier);
        ClassDB::bind_method(D_METHOD("set_jump_modifier", "p_jump_modifier"), &Player::set_jump_modifier);

        ClassDB::bind_method(D_METHOD("get_gravity_modifier"), &Player::get_gravity_modifier);
        ClassDB::bind_method(D_METHOD("set_gravity_modifier", "p_gravity_modifier"), &Player::set_gravity_modifier);

        //ClassDB::bind_method(D_METHOD("get_energy_cells_collected"), &Player::get_energy_cells_collected);
        //ClassDB::bind_method(D_METHOD("set_energy_cells_collected", "p_energy_cells_collected"), &Player::set_energy_cells_collected);

        // methods
        ClassDB::bind_method(D_METHOD("movement", "delta"), &Player::movement);

        // attributes
        ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed_modifier"), "set_speed_modifier", "get_speed_modifier");
        ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "jump_modifier"), "set_jump_modifier", "get_jump_modifier");
        ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity_modifier"), "set_gravity_modifier", "get_gravity_modifier");
        //ADD_PROPERTY(PropertyInfo(Variant::INT, "cells_collected"), "set_energy_cells_collected", "get_energy_cells_collected");

        // signals

    }

private:
    void movement(const double delta);

private:
    AnimationPlayer *animation_player{};
    Camera2D *camera{};
    CollisionShape2D *collision_shape2d{};
    Sprite2D *sprite{};

    Vector2 velocity{};
    double speed{10.0};
    double jump_velocity{-10.0};

    double speed_modifier{20.0};
    double jump_modifier{45.0};
    double gravity_modifier{3.0};

    //int32_t energy_cells_collected{};

};
}
