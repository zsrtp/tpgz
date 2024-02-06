#include "menu.h"
#include "rels/include/defines.h"

// This array must correspond to the order of the MenuIndex enum.
const char* g_menuPaths[MN_COUNT] = {
    "main",         "cheats",         "flags",
    "inventory",    "memory",         "practice",
    "scene",        "settings",       "tools",
    "warp",         "general_flags",  "dungeon_flags",
    "portal_flags", "flag_records",   "flag_log",
    "item_wheel",   "pause",          "amounts",
    "watches",      "memory_editor",  "memfiles",
    "any_saves",    "any_bite_saves", "hundo_saves",
    "ad_saves",     "nosq_saves",     "glitchless_saves",
    "actor_spawn",  "actor_list",     "pos_settings",
};

KEEP_FUNC Menu::Menu(Cursor& cursor) : cursor(cursor) {}