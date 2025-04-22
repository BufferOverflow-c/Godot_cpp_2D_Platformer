#pragma once

#include <godot_cpp/classes/node2d.hpp>

#include <godot_cpp/classes/resource_loader.hpp>

#include "../entity/player.hpp"

namespace godot {

class GameManager : public Node2D {
    GDCLASS(GameManager, Node2D)

public:
    GameManager();
    ~GameManager();

	static GameManager *get_singleton();

    void _ready() override;

    int32_t get_starting_area() const { return starting_area; }
    void set_starting_area(const int32_t p_starting_area) { starting_area = p_starting_area; }

    String get_area_path() const { return area_path; }
    void set_area_path(const String &p_area_path) { area_path = p_area_path; }

    String get_area_name() const { return area_name; }
    void set_area_name(const String p_area_name) { area_name = p_area_name; }

    int32_t get_energy_cells_collected() const { return energy_cells_collected; }
    void set_energy_cells_collected(const int32_t p_energy_cells_collected) { energy_cells_collected = p_energy_cells_collected; }

    void load_area(const int32_t p_area_number);
    void load_area_from_path(const String p_scene_path);
    void next_area(const String p_scene_path = "");
    void add_energy_cell();
    void reset_energy_cells() { energy_cells_collected = 0; }
    void _on_tree_exited();

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("get_starting_area"), &GameManager::get_starting_area);
        ClassDB::bind_method(D_METHOD("set_starting_area", "p_starting_area"), &GameManager::set_starting_area);

        ClassDB::bind_method(D_METHOD("get_area_path"), &GameManager::get_area_path);
        ClassDB::bind_method(D_METHOD("set_area_path", "p_area_path"), &GameManager::set_area_path);

        ClassDB::bind_method(D_METHOD("get_area_name"), &GameManager::get_area_name);
        ClassDB::bind_method(D_METHOD("set_area_name", "p_area_name"), &GameManager::set_area_name);

        ClassDB::bind_method(D_METHOD("get_energy_cells_collected"), &GameManager::get_energy_cells_collected);
        ClassDB::bind_method(D_METHOD("set_energy_cells_collected", "p_energy_cells_collected"), &GameManager::set_energy_cells_collected);

        ClassDB::bind_method(D_METHOD("load_area", "p_area_number"), &GameManager::load_area);
        ClassDB::bind_method(D_METHOD("load_area_from_path", "p_scene_path"), &GameManager::load_area_from_path);
        ClassDB::bind_method(D_METHOD("next_area", "p_scene_path"), &GameManager::next_area);
        ClassDB::bind_method(D_METHOD("add_energy_cell"), &GameManager::add_energy_cell);
        ClassDB::bind_method(D_METHOD("reset_energy_cells"), &GameManager::reset_energy_cells);
        ClassDB::bind_method(D_METHOD("_on_tree_exited"), &GameManager::_on_tree_exited);

        ADD_PROPERTY(PropertyInfo(Variant::INT, "starting_area"), "set_starting_area", "get_starting_area");
        ADD_PROPERTY(PropertyInfo(Variant::STRING, "area_path"), "set_area_path", "get_area_path");
        ADD_PROPERTY(PropertyInfo(Variant::STRING, "area_name"), "set_area_name", "get_area_name");
        ADD_PROPERTY(PropertyInfo(Variant::INT, "cells_collected"), "set_energy_cells_collected", "get_energy_cells_collected");
    }

private:
    static GameManager *singleton;
    Player *player{};
    Node2D *area_container{};
    String area_path{};
    String area_name{};
    //Node *player{};
    //Node *area_container{};
    int32_t energy_cells_collected{};
    int32_t starting_area{1};
    int32_t current_area{1};
};
}
