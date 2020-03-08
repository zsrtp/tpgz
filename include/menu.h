#pragma once
#include "font.h"
#include <string.h>

// main menu
#define INVENTORY_INDEX 2
#define CHEAT_INDEX 3
#define WARPING_INDEX 4
#define MEMORY_INDEX 5
#define PRACTICE_INDEX 6
#define TOOLS_INDEX 7
#define SETTINGS_INDEX 8
extern bool mm_visible;

// inventory
#define ITEM_WHEEL_INDEX 2
#define PAUSE_MENU_INDEX 3
extern bool inventory_visible;

// item wheel
#define stuff 2
extern bool item_wheel_visible;

// pause menu
#define stuff 2
extern bool pause_visible;

// cheats
#define INVINCIBLE_INDEX 0
#define INVINCIBLE_ENEMIES_INDEX 1
#define INFINITE_AIR_INDEX 2
#define INFINITE_OIL_INDEX 3
#define INFINITE_BOMBS_INDEX 4
#define INFINITE_RUPEES_INDEX 5
#define INFINITE_ARROWS_INDEX 6
#define MOON_JUMP_INDEX 7
#define TELEPORT_INDEX 8
#define RELOAD_AREA_INDEX 9
#define FAST_MOVEMENT_INDEX 10
extern bool cheats_visible;

// warping
#define stuff 2
extern bool warping_visible;

// memory
#define stuff 2
extern bool memory_visible;

// practice
#define GOATS_INDEX 2
#define HUGO_INDEX 3
#define MIST_INDEX 4
#define FRST_BIT_INDEX 5
#define GORGE_VOID_INDEX 6
#define PILLAR_CLIP_INDEX 7
#define TOAD_INDEX 8
#define BOSS_BUG_INDEX 9
#define NORGOR_INDEX 10
#define LAKEBED_BK_SKIP_INDEX 11
#define ONEBOMB_INDEX 12
#define MDH_BRIDGE_INDEX 13
#define BULBLIN_CAMP_INDEX 14
#define POE_1_SKIP_INDEX 15
#define DSS_INDEX 16
#define STALLORD_INDEX 17
#define AERALFOS_SKIP_INDEX 18
#define FAN_TOWER_INDEX 19
#define EARLY_PLATFORM_INDEX 20

extern bool prac_visible;
extern bool inject_save_flag;

// tools
#define INPUT_VIEWER_INDEX 2
#define TIMER_INDEX 3
#define ROLL_INDEX 4
#define GORGE_INDEX 5
extern bool tools_visible;

// settings
#define LOG_LEVEL_INDEX 2
#define RESET_TEMP_FLAGS_INDEX 3
#define DROP_SHADOWS_INDEX 4
extern bool settings_visible;
extern bool g_reset_temp_flags;
extern bool g_drop_shadows;

struct Line {
    char line[50];
    const int idx;
    char description[100];
    bool toggleable;
    bool* activation_flag;
};

class Menu {
   protected:
    // char MenuName[32];
    // int MenuId;
    // char MenuDescription[32];

   public:
    Menu() {}
    // Menu(const char* _MenuName, int _MenuId, const char* _MenuDescription) {
    //     strcpy(MenuName, _MenuName);
    //     strcpy(MenuDescription, _MenuDescription);
    //     MenuId = _MenuId;
    // }
    virtual void transition_into() = 0;
    virtual void render() = 0;
};

class MainMenu : public Menu {
   public:
    MainMenu() : Menu() {}
    static void transition_into(){};
    static void render(Font& font);
};

class InventoryMenu : public Menu {
   public:
    InventoryMenu() : Menu() {}
    static void transition_into(){};
    static void render(Font& font);
};

class PauseMenu : public Menu {
   public:
    PauseMenu() : Menu() {}
    static void transition_into(){};
    static void render(Font& font);
};

class ItemWheelMenu : public Menu {
   public:
    ItemWheelMenu() : Menu() {}
    static void transition_into(){};
    static void render(Font& font);
};

class CheatsMenu : public Menu {
   public:
    CheatsMenu() : Menu() {}
    static void transition_into(){};
    static void render(Font& font);
};

class WarpingMenu : public Menu {
   public:
    WarpingMenu() : Menu() {}
    static void transition_into(){};
    static void render(Font& font);
};

class MemoryMenu : public Menu {
   public:
    MemoryMenu() : Menu() {}
    static void transition_into(){};
    static void render(Font& font);
};

class PracticeMenu : public Menu {
   public:
    PracticeMenu() : Menu() {}
    static void transition_into(){};
    static void render(Font& font);
};

class SettingsMenu : public Menu {
   public:
    SettingsMenu() : Menu() {}
    static void transition_into(){};
    static void render(Font& font);
};

class ToolsMenu : public Menu {
   public:
    ToolsMenu() : Menu() {}
    static void transition_into(){};
    static void render(Font& font);
};