#include "menu.h"

extern "C" {
// This array must correspond to the order of the MenuIndex enum.
const char* g_menuPaths[MN_COUNT] = {
    "menu_main",
    "menu_cheats",
    "menu_flags",
    "menu_inventory",
    "menu_memory",
    "menu_practice",
    "menu_scene",
    "menu_settings",
    "menu_tools",
    "menu_warp",
    "menu_general_flags",
    "menu_dungeon_flags",
    "menu_portal_flags",
    "menu_flag_records",
    "menu_flag_log",
    "menu_item_wheel",
    "menu_pause",
    "menu_amounts",
    "menu_watches",
    "menu_memory_editor",
    "menu_memfiles",
    "menu_any_saves",
    "menu_hundo_saves",
    "menu_ad_saves",
    "menu_actor_spawn",
    "menu_actor_list",
    "menu_pos_settings",
};
}
