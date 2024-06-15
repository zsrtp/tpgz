#pragma once
#include "cheats.h"
#include "commands.h"
#include "font.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/dolphin/mtx/vec.h"
#include "timer.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define MAX_MENU_RENDER_FLAGS 30

#ifdef GCN_PLATFORM
#define SELECTION_BUTTON (GZPad::A)
#define BACK_BUTTON (GZPad::B)
#endif
#ifdef WII_PLATFORM
#define SELECTION_BUTTON (GZPad::A)
#define BACK_BUTTON (GZPad::B)
#endif

// If you add a new menu to this list, you must also add the REL name to the g_menuPaths array in menu.cpp.
enum MenuIndex {
    MN_NONE_INDEX = -1,
    MN_MAIN_MENU_INDEX = 0,
    // Main menu's sub menus
    MN_CHEAT_INDEX,
    MN_FLAGS_INDEX,
    MN_INVENTORY_INDEX,
    MN_MEMORY_INDEX,
    MN_PRACTICE_INDEX,
    MN_SCENE_INDEX,
    MN_SETTINGS_INDEX,
    MN_TOOLS_INDEX,
    MN_WARPING_INDEX,
    // Flags menu's sub menus
    MN_GENERAL_FLAGS_INDEX,
    MN_DUNGEON_FLAGS_INDEX,
    MN_PORTAL_FLAGS_INDEX,
    MN_FLAG_RECORDS_INDEX,
    MN_FLAG_LOG_INDEX,
    // Inventory menu's sub menus
    MN_ITEM_WHELL_INDEX,
    MN_PAUSE_INDEX,
    MN_AMOUNTS_INDEX,
    // Memory menu's sub menus
    MN_WATCHES_INDEX,
    MN_MEMORY_EDITOR_INDEX,
    MN_MEM_FILES_INDEX,
    // Practice menu's sub menus
    MN_ANY_SAVES_INDEX,
    MN_ANY_BITE_SAVES_INDEX,
    MN_HUNDO_SAVES_INDEX,
    MN_AD_SAVES_INDEX,
    MN_NOSQ_SAVES_INDEX,
    MN_GLITCHLESS_SAVES_INDEX,
    // Scene menu's sub menus
    MN_ACTOR_SPAWNER_INDEX,
    MN_ACTOR_LIST_INDEX,
    MN_COLLISION_VIEW_INDEX,
    // MN_PROJECTION_VIEW_INDEX,
    MN_TRIGGER_VIEW_INDEX,
    // Setting menu's sub menus
    MN_POS_SETTINGS_INDEX,
    MN_CREDITS_INDEX,

    // This entry is used only to get a count of the number of valid entries.
    MN_COUNT
};

extern const char* g_menuPaths[MN_COUNT];

#define LIST_COUNT(list) (sizeof(list) / sizeof((list)[0]))
#define MENU_LINE_NUM LIST_COUNT(lines)

class Menu {
public:
    Menu(Cursor& cursor);

    virtual void draw() = 0;

protected:
    Cursor& cursor;
};