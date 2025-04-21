#include "energy_cell.hpp"

#include "../player.hpp"
#include "../portal/area_exit.hpp"
#include "../../game_manager/game_manager.hpp"

using namespace godot;

void EnergyCell::_ready() {
    connect("body_entered", Callable(this, "_on_body_entered"));
}

void EnergyCell::_on_body_entered(CharacterBody2D *body) {
    Player *player = get_node<Player>("../../../../Player");
    if(body == player) {
        if(player && overlaps_body(body)) {
            get_node<GameManager>("../../../../GameManager")->add_energy_cell();
            queue_free();
        }
    }
}
