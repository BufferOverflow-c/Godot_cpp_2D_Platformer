#include "register_types.h"

#include "entity/player.hpp"
#include "entity/obstacles/moving_platform.hpp"
#include "entity/pickups/energy_cell.hpp"
#include "entity/portal/area_exit.hpp"

#include "game_manager/game_manager.hpp"
#include "gameplay/gameplay.hpp"
#include "ui/hud.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

static GameManager *GameManager_singleton = nullptr;
static HUD *HUD_singleton = nullptr;

void initialize_example_module(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }
    GDREGISTER_CLASS(Player);
    GDREGISTER_CLASS(MovingPlatform);
    GDREGISTER_CLASS(EnergyCell);
    GDREGISTER_CLASS(AreaExit);
    GDREGISTER_CLASS(Gameplay);

    GDREGISTER_CLASS(GameManager);
    GameManager_singleton = memnew(GameManager);
    Engine::get_singleton()->register_singleton("GameManager", GameManager::get_singleton());

    GDREGISTER_CLASS(HUD);
    HUD_singleton = memnew(HUD);
    Engine::get_singleton()->register_singleton("HUD", HUD::get_singleton());
}

void uninitialize_example_module(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }

    Engine::get_singleton()->unregister_singleton("GameManager");
    memdelete(GameManager_singleton);
    GameManager_singleton = nullptr;
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT
example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
                     const GDExtensionClassLibraryPtr p_library,
                     GDExtensionInitialization *r_initialization) {
  godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library,
                                                 r_initialization);

  init_obj.register_initializer(initialize_example_module);
  init_obj.register_terminator(uninitialize_example_module);
  init_obj.set_minimum_library_initialization_level(
      MODULE_INITIALIZATION_LEVEL_SCENE);

  return init_obj.init();
}
}
