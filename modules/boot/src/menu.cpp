#include "menu.h"
#include "rels/include/cxx.h"
#include "menus/amounts_menu.h"
#include "menus/any_saves_menu.h"
#include "menus/cheats_menu.h"
#include "menus/flags_menu.h"
#include "menus/hundo_saves_menu.h"
#include "menus/inventory_menu.h"
#include "menus/item_wheel_menu.h"
#include "menus/main_menu.h"
#include "menus/memory_editor_menu.h"
#include "menus/memory_menu.h"
#include "menus/pause_menu.h"
#include "menus/position_settings_menu.h"
#include "menus/practice_menu.h"
#include "menus/scene_menu.h"
#include "menus/settings_menu.h"
#include "menus/flag_records_menu.h"
#include "menus/tools_menu.h"
#include "menus/warping_menu.h"
#include "menus/ad_saves_menu.h"
#include "menus/memfiles_menu.h"
#include "menus/actor_spawn_menu.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "rels/include/defines.h"

typedef void (*menu_render_t)();

KEEP_VAR Menu* l_menuDrawList[MAX_MENU_RENDER_FLAGS];

Menu* l_currentMenu = nullptr;
Menu* l_returnMenu = nullptr;

KEEP_FUNC void GZ_drawMenu() {
    if (l_currentMenu != nullptr) {
        l_currentMenu->draw();
    }
}

void GZ_setMenu(int menu_idx) {
    if (menu_idx > MN_NONE_INDEX) {
        l_currentMenu = l_menuDrawList[menu_idx];
    } else {
        l_currentMenu = nullptr;
    }
}

void GZ_clearMenu() {
    if (l_currentMenu) {
        l_currentMenu = nullptr;
    }
}

bool GZ_checkMenuOpen() {
    return l_currentMenu != nullptr;
}

bool GZ_checkReturnMenu() {
    return l_returnMenu != nullptr;
}

void GZ_returnMenu() {
    l_currentMenu = l_returnMenu;
}

void GZ_setReturnMenu(int menu_idx) {
    if (menu_idx > MN_NONE_INDEX) {
        l_returnMenu = l_menuDrawList[menu_idx];
    } else {
        l_returnMenu = nullptr;
    }
}