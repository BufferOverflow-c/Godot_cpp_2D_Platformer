#include "player.hpp"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

#include <godot_cpp/core/math.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

Player::Player() = default;

Player::~Player() = default;

void Player::_ready() {
    InputMap::get_singleton()->load_from_project_settings();
}

void Player::_physics_process(const double delta) {
    movement(delta);
}

void Player::movement(const double delta) {
    if(is_on_floor()) {
        velocity.y = 0.0;
    }

    if(!is_on_floor()) {
        velocity += gravity_modifier * get_gravity() * delta;
    }

    if(Input::get_singleton()->is_action_just_pressed("move_up") && is_on_floor()) {
        velocity.y = jump_velocity * jump_modifier;
    }

    float direction = Input::get_singleton()->get_axis("move_left", "move_right");

    if(direction == 1) {
        get_node<Sprite2D>("Sprite2D")->set_flip_h(false);
    } else if(direction == -1) {
        get_node<Sprite2D>("Sprite2D")->set_flip_h(true);
    }

    if(direction != 0.0) {
        get_node<AnimationPlayer>("AnimationPlayer")->play("move");
        velocity.x = direction * speed * speed_modifier;
    } else {
        get_node<AnimationPlayer>("AnimationPlayer")->play("idle");
        velocity.x = 0;
    }

    if(velocity.y < 0.0) {
        get_node<AnimationPlayer>("AnimationPlayer")->play("jump");
    } else if(velocity.y > 0.0) {
        get_node<AnimationPlayer>("AnimationPlayer")->play("fall");
    }

    if(Input::get_singleton()->is_action_pressed("move_down")) {
 	    set_collision_mask_value(10, false);
    } else {
 	    set_collision_mask_value(10, true);
    }

    set_velocity(velocity);
    move_and_slide();
}
