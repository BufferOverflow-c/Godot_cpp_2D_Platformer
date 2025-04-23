#pragma once

#include <godot_cpp/classes/node.hpp>

#include <godot_cpp/classes/node2d.hpp>

#include "../entity/player.hpp"

namespace godot {

class Gameplay : public Node {
    GDCLASS(Gameplay, Node)

public:
    Gameplay();
    ~Gameplay();

    void _ready() override;

    String get_area_path() const { return area_path; }
    void set_area_path(const String &p_area_path) { area_path = p_area_path; }

    String get_area_name() const { return area_name; }
    void set_area_name(const String p_area_name) { area_name = p_area_name; }

    int32_t get_starting_area() const { return starting_area; }
    void set_starting_area(const int32_t p_starting_area) { starting_area = p_starting_area; }

    void start_game();
    void load_area(const int32_t p_area_number);
    void load_area_from_path(const String p_scene_path);
    void next_area(const String p_scene_path);
    void unload_area();
    void _on_tree_exited();

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("get_area_path"), &Gameplay::get_area_path);
        ClassDB::bind_method(D_METHOD("set_area_path", "p_area_path"), &Gameplay::set_area_path);

        ClassDB::bind_method(D_METHOD("get_area_name"), &Gameplay::get_area_name);
        ClassDB::bind_method(D_METHOD("set_area_name", "p_area_name"), &Gameplay::set_area_name);

        ClassDB::bind_method(D_METHOD("get_starting_area"), &Gameplay::get_starting_area);
        ClassDB::bind_method(D_METHOD("set_starting_area", "p_starting_area"), &Gameplay::set_starting_area);

        ClassDB::bind_method(D_METHOD("start_game"), &Gameplay::start_game);
        ClassDB::bind_method(D_METHOD("load_area", "p_area_number"), &Gameplay::load_area);
        ClassDB::bind_method(D_METHOD("load_area_from_path", "p_scene_path"), &Gameplay::load_area_from_path);
        ClassDB::bind_method(D_METHOD("next_area", "p_scene_path"), &Gameplay::next_area);
        ClassDB::bind_method(D_METHOD("unload_area"), &Gameplay::unload_area);
        ClassDB::bind_method(D_METHOD("_on_tree_exited"), &Gameplay::_on_tree_exited);

        ADD_PROPERTY(PropertyInfo(Variant::STRING, "area_path"), "set_area_path", "get_area_path");
        ADD_PROPERTY(PropertyInfo(Variant::STRING, "area_name"), "set_area_name", "get_area_name");
        ADD_PROPERTY(PropertyInfo(Variant::INT, "starting_area"), "set_starting_area", "get_starting_area");
    }

private:
    Player *player{nullptr};
    Node2D *area_container{nullptr};
    int32_t starting_area{1};
    int32_t current_area{1};
    String area_path{};
    String area_name{};
};
}
