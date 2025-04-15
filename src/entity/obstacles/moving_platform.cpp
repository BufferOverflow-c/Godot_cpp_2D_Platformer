#include "moving_platform.hpp"

#include <godot_cpp/classes/path_follow2d.hpp>
#include <godot_cpp/classes/property_tweener.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

void MovingPlatform::_ready() {
    move_tween();
}

void MovingPlatform::move_tween() {
    PathFollow2D *path_follow2d = get_node<PathFollow2D>("PathFollow2D");
    Ref<Tween> tween = get_tree()->create_tween()->set_loops();
    tween->tween_property(path_follow2d, "progress_ratio", 1.0, duration)->set_ease(ease)->set_trans(transition);
    if(!is_looping) {
        tween->tween_property(path_follow2d, "progress_ratio", 0.0, duration)->set_ease(ease)->set_trans(transition);
    } else {
        tween->tween_property(path_follow2d, "progress_ratio", 0.0, 0.0)->set_ease(ease)->set_trans(transition);
    }
}
