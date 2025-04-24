#pragma once

#include <godot_cpp/classes/control.hpp>

#include <godot_cpp/classes/label.hpp>

namespace godot {

class HUD : public Control {
    GDCLASS(HUD, Control)

public:
    HUD();
    ~HUD();

    static HUD *get_singleton();

    void _ready() override;

    Label *get_portal_label() const { return portal_label; }
    Label *get_energy_cell_label() const { return energy_cell_label; }
    int32_t get_energy_cell_number() const { return energy_cell_number; }

    void set_portal_label(Label *p_portal_label) { portal_label = p_portal_label; }
    void set_energy_cell_label(Label *p_energy_cell_label) { energy_cell_label = p_energy_cell_label; }
    void set_energy_cell_number(const int32_t p_number) { energy_cell_number = p_number; }

    void portal_open();
    void portal_closed();
    void update_energy_cell_label();

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("get_portal_label"), &HUD::get_portal_label);
        ClassDB::bind_method(D_METHOD("set_portal_label", "p_portal_label"), &HUD::set_portal_label);

        ClassDB::bind_method(D_METHOD("get_energy_cell_label"), &HUD::get_energy_cell_label);
        ClassDB::bind_method(D_METHOD("set_energy_cell_label", "p_energy_cell_label"), &HUD::set_energy_cell_label);

        ClassDB::bind_method(D_METHOD("get_energy_cell_number"), &HUD::get_energy_cell_number);
        ClassDB::bind_method(D_METHOD("set_energy_cell_number", "p_number"), &HUD::set_energy_cell_number);

        ClassDB::bind_method(D_METHOD("portal_open"), &HUD::portal_open);
        ClassDB::bind_method(D_METHOD("portal_closed"), &HUD::portal_closed);
        ClassDB::bind_method(D_METHOD("update_energy_cell_label"), &HUD::update_energy_cell_label);
    }

private:
    static HUD *singleton;
    Label *portal_label{nullptr};
    Label *energy_cell_label{nullptr};
    int32_t energy_cell_number{};
};
}
