#include "menu.h"
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
#include "menus/temp_flags_menu.h"
#include "menus/tools_menu.h"
#include "menus/warping_menu.h"

typedef void (*menu_render_t)(Font& font);

menu_render_t MenuRenderList[MAX_MENU_RENDER_FLAGS] = {
    MainMenu::render,
    InventoryMenu::render,
    ItemWheelMenu::render,
    WarpingMenu::render,
    MemoryMenu::render,
    WatchesMenu::render,
    MemoryEditorMenu::render,
    FlagsMenu::render,
    GeneralFlagsMenu::render,
    DungeonFlagsMenu::render,
    PortalFlagsMenu::render,
    TempFlagsMenu::render,
    PracticeMenu::render,
    CheatsMenu::render,
    SceneMenu::render,
    SettingsMenu::render,
    ToolsMenu::render,
    PauseMenu::render,
    AmountsMenu::render,
    AnySavesMenu::render,
    HundoSavesMenu::render,
    PosSettingsMenu::render};

menu_render_t currentMenu = nullptr;

namespace MenuRendering {
    void render_active_menus(Font& font) {
        if (currentMenu) {
            currentMenu(font);
        }
    }

    void set_menu(MenuIndex idx) {
        if (idx > MN_NONE_INDEX) {
            currentMenu = MenuRenderList[idx];
        } else {
            currentMenu = nullptr;
        }
    }

    void close_active_menus() {
        if (currentMenu) {
            currentMenu = nullptr;
        }
    }

    bool is_menu_open() {
        return currentMenu != nullptr;
    }
}  // namespace MenuRendering