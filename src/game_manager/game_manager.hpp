#pragma once

#include <godot_cpp/classes/node2d.hpp>

#include <godot_cpp/classes/resource_loader.hpp>

namespace godot {

class GameManager : public Node2D {
    GDCLASS(GameManager, Node2D)

public:
    GameManager();
    ~GameManager();

	static GameManager *get_singleton();

    void _ready() override;

    String get_area_path() const { return area_path; }
    void set_area_path(const String &p_area_path) { area_path = p_area_path; }

    int32_t get_energy_cells_collected() const { return energy_cells_collected; }
    void set_energy_cells_collected(const int32_t p_energy_cells_collected) { energy_cells_collected = p_energy_cells_collected; }

    void next_level(const String &p_path = "");
    void set_up_area();
    void add_energy_cell();
    void reset_energy_cells() { energy_cells_collected = 0; }

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("get_area_path"), &GameManager::get_area_path);
        ClassDB::bind_method(D_METHOD("set_area_path", "p_area_path"), &GameManager::set_area_path);

        ClassDB::bind_method(D_METHOD("get_energy_cells_collected"), &GameManager::get_energy_cells_collected);
        ClassDB::bind_method(D_METHOD("set_energy_cells_collected", "p_energy_cells_collected"), &GameManager::set_energy_cells_collected);

        ClassDB::bind_method(D_METHOD("next_level", "p_path"), &GameManager::next_level);
        ClassDB::bind_method(D_METHOD("set_up_area"), &GameManager::set_up_area);
        ClassDB::bind_method(D_METHOD("add_energy_cell"), &GameManager::add_energy_cell);
        ClassDB::bind_method(D_METHOD("reset_energy_cells"), &GameManager::reset_energy_cells);

        ADD_PROPERTY(PropertyInfo(Variant::STRING, "area_path"), "set_area_path", "get_area_path");
        ADD_PROPERTY(PropertyInfo(Variant::INT, "cells_collected"), "set_energy_cells_collected", "get_energy_cells_collected");
    }

private:
    static GameManager *singleton;
    int32_t energy_cells_collected{};
    int32_t current_level{1};
    String area_path{};
};
}
