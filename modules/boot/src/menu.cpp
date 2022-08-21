#include "menu.h"

extern "C" {
// This array must correspond to the order of the MenuIndex enum.
const char* g_menuPaths[MN_COUNT] = {
    "/tpgz/rels/menus/menu_main.rel",
    "/tpgz/rels/menus/menu_cheats.rel",
    "/tpgz/rels/menus/menu_flags.rel",
    "/tpgz/rels/menus/menu_inventory.rel",
    "/tpgz/rels/menus/menu_memory.rel",
    "/tpgz/rels/menus/menu_practice.rel",
    "/tpgz/rels/menus/menu_scene.rel",
    "/tpgz/rels/menus/menu_settings.rel",
    "/tpgz/rels/menus/menu_tools.rel",
    "/tpgz/rels/menus/menu_warp.rel",
    "/tpgz/rels/menus/menu_wheel.rel",
    "/tpgz/rels/menus/menu_any_saves.rel",
    "/tpgz/rels/menus/menu_hundo_saves.rel",
};
}
