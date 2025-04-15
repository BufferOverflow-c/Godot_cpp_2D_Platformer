#pragma once

#include <godot_cpp/classes/path2d.hpp>

#include <godot_cpp/classes/tween.hpp>

namespace godot {

class MovingPlatform : public Path2D {
    GDCLASS(MovingPlatform, Path2D)

public:
    void _ready() override;

    // GETTERS
    bool get_is_looping() const { return is_looping; }
    double get_duration() const { return duration; }
    Tween::EaseType get_ease() const { return ease; }
    Tween::TransitionType get_transition() const { return transition; }

    // SETTERS
    void set_is_looping(const bool p_is_looping) { is_looping = p_is_looping; }
    void set_duration(const double p_duration) { duration = p_duration; }
    void set_ease(const Tween::EaseType p_ease) { ease = p_ease; }
    void set_transition(const Tween::TransitionType p_transition) { transition = p_transition; }

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("get_is_looping"), &MovingPlatform::get_is_looping);
        ClassDB::bind_method(D_METHOD("set_is_looping", "p_is_looping"), &MovingPlatform::set_is_looping);

        ClassDB::bind_method(D_METHOD("get_duration"), &MovingPlatform::get_duration);
        ClassDB::bind_method(D_METHOD("set_duration", "p_duration"), &MovingPlatform::set_duration);

        ClassDB::bind_method(D_METHOD("get_ease"), &MovingPlatform::get_ease);
        ClassDB::bind_method(D_METHOD("set_ease", "p_ease"), &MovingPlatform::set_ease);

        ClassDB::bind_method(D_METHOD("get_transition"), &MovingPlatform::get_transition);
        ClassDB::bind_method(D_METHOD("set_transition", "p_transition"), &MovingPlatform::set_transition);

        ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_looping"), "set_is_looping", "get_is_looping");
        ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "duration"), "set_duration", "get_duration");
        ADD_PROPERTY(PropertyInfo(Variant::INT, "ease", PROPERTY_HINT_RANGE, "0, 3, 1"), "set_ease", "get_ease");
        ADD_PROPERTY(PropertyInfo(Variant::INT, "transition", PROPERTY_HINT_RANGE, "0, 11, 1"), "set_transition", "get_transition");
    }

    void move_tween();

private:
    bool is_looping{false};
    double duration{1.0};
    Tween::EaseType ease{Tween::EaseType::EASE_IN_OUT};
    Tween::TransitionType transition{Tween::TransitionType::TRANS_QUAD};
};
}
