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

    String get_area_path() const { return area_path; }
    void set_area_path(const String &p_area_path) { area_path = p_area_path; }

    void next_level(const String &p_path = "");

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("get_area_path"), &GameManager::get_area_path);
        ClassDB::bind_method(D_METHOD("set_area_path", "p_area_path"), &GameManager::set_area_path);

        ClassDB::bind_method(D_METHOD("next_level", "p_path"), &GameManager::next_level);

        ADD_PROPERTY(PropertyInfo(Variant::STRING, "area_path"), "set_area_path", "get_area_path");
    }

private:
    static GameManager *singleton;
    int32_t current_level{1};
    String area_path{};
};
}
