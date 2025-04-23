#pragma once

#include <godot_cpp/classes/node2d.hpp>

namespace godot {

class GameManager : public Node2D {
    GDCLASS(GameManager, Node2D)

public:
    GameManager();
    ~GameManager();

	static GameManager *get_singleton();

    void _ready() override;

    int32_t get_energy_cells_collected() const { return energy_cells_collected; }
    void set_energy_cells_collected(const int32_t p_energy_cells_collected) { energy_cells_collected = p_energy_cells_collected; }

    void next_area(const String p_scene_path);
    void add_energy_cell();
    void reset_energy_cells() { energy_cells_collected = 0; }

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("get_energy_cells_collected"), &GameManager::get_energy_cells_collected);
        ClassDB::bind_method(D_METHOD("set_energy_cells_collected", "p_energy_cells_collected"), &GameManager::set_energy_cells_collected);

        ClassDB::bind_method(D_METHOD("next_scene", "p_scene_path"), &GameManager::next_area);
        ClassDB::bind_method(D_METHOD("add_energy_cell"), &GameManager::add_energy_cell);
        ClassDB::bind_method(D_METHOD("reset_energy_cells"), &GameManager::reset_energy_cells);

        ADD_PROPERTY(PropertyInfo(Variant::INT, "cells_collected"), "set_energy_cells_collected", "get_energy_cells_collected");
    }

private:
    static GameManager *singleton;
    int32_t energy_cells_collected{};
};
}
