#include "menu.h"

extern "C" {
// This array must correspond to the order of the MenuIndex enum.
const char* g_menuPaths[MN_COUNT] = {
    "/tpgz/rels/menu_main.rel",
    "/tpgz/rels/menu_cheats.rel",
    "/tpgz/rels/menu_inventory.rel",
    "/tpgz/rels/menu_practice.rel",
    "/tpgz/rels/menu_settings.rel",
    "/tpgz/rels/menu_tools.rel",
    "/tpgz/rels/menu_warp.rel",
    "/tpgz/rels/menu_wheel.rel",
};
}
