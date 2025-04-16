#pragma once

#include <godot_cpp/classes/node.hpp>

#include <godot_cpp/classes/resource_loader.hpp>

namespace godot {

class GameManager : public Node {
    GDCLASS(GameManager, Node)

public:
    GameManager();
    ~GameManager();

	static GameManager *get_singleton();
    void next_level();

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("next_level"), &GameManager::next_level);
    }

private:
    static GameManager *singleton;
    int32_t current_level{1};
    String area_path{"res://assets/scenes/areas/area_"};
};
}
