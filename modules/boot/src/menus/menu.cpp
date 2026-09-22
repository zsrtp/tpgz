#include "menus/menu.h"
#include "rels/include/defines.h"

// This array must correspond to the order of the MenuIndex enum.
const char* g_menuPaths[MN_COUNT] = {
    "main",             "cheats",         "flags",
    "inventory",        "memory",         "practice",
    "scene",            "settings",       "tools",
    "warp",             "general_flags",  "dungeon_flags",
    "portal_flags",     "rupee_flags",    "flag_records",
    "flag_log",         "item_wheel",     "pause",
    "amounts",          "equipment",      "golden_bugs",
    "hidden_skills",
    "watches",          "memory_editor",  "memfiles",
    "any_saves",        "any_bite_saves", "hundo_saves",
    "ad_saves",         "nosq_saves",     "glitchless_saves",
    "actor_spawn",      "actor_list",     "collision_view",
    "projection_view",  "trigger_view",   "sound_test",
    "pos_settings",     "credits",        "combo",
    "tools_checkers",   "tools_controller", "tools_link",
    "tools_scene",      "tools_timers",   "tools_rng"
};

KEEP_FUNC Menu::Menu(Cursor& cursor) : cursor(cursor) {}