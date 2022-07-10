#pragma once
#include "cheats.h"
#include "commands.h"
#include "font.h"
#include "input_viewer.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/dolphin/mtx/vec.h"
#include "timer.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define MAX_MENU_RENDER_FLAGS 27

#ifdef GCN_PLATFORM
#define SELECTION_BUTTON (GZPad::A)
#define BACK_BUTTON (GZPad::B)
#endif
#ifdef WII_PLATFORM
#define SELECTION_BUTTON (Controller::Mote::A)
#define BACK_BUTTON (GZPad::B)
#endif

enum MenuIndex {
    MN_NONE_INDEX = -1,
    MN_MAIN_MENU_INDEX = 0,
    MN_INVENTORY_INDEX,
    MN_ITEM_WHELL_INDEX,
    MN_WARPING_INDEX,
    MN_MEMORY_INDEX,
    MN_WATCHES_INDEX,
    MN_MEMORY_EDITOR_INDEX,
    MN_FLAGS_INDEX,
    MN_GENERAL_FLAGS_INDEX,
    MN_DUNGEON_FLAGS_INDEX,
    MN_PORTAL_FLAGS_INDEX,
    MN_FLAG_RECORDS_INDEX,
    MN_PRACTICE_INDEX,
    MN_CHEAT_INDEX,
    MN_SCENE_INDEX,
    MN_SETTINGS_INDEX,
    MN_TOOLS_INDEX,
    MN_PAUSE_INDEX,
    MN_AMOUNTS_INDEX,
    MN_ANY_SAVES_INDEX,
    MN_HUNDO_SAVES_INDEX,
    MN_POS_SETTINGS_INDEX,
    MN_FLAG_LOG_INDEX,
    MN_AD_SAVES_INDEX,
    MN_MEM_FILES_INDEX,
    MN_ACTOR_SPAWNER_INDEX
};

void GZ_drawMenu();
void GZ_setMenu(int idx);
void GZ_clearMenu();
bool GZ_checkMenuOpen();

class Menu {
public:
    Menu() {}
};