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
#define NORGOR_INDEX 2
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
#define RELOAD_TEMP_FLAGS_INDEX 3
#define DROP_SHADOWS_INDEX 4
extern bool settings_visible;
extern bool g_reload_temp_flags;
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
    void transition_into(){};
    static void render(Font& font);
};

class InventoryMenu : public Menu {
   public:
    InventoryMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& Font);
};

class PauseMenu : public Menu {
   public:
    PauseMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& Font);
};

class ItemWheelMenu : public Menu {
   public:
    ItemWheelMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& Font);
};

class CheatsMenu : public Menu {
   public:
    CheatsMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};

class WarpingMenu : public Menu {
   public:
    WarpingMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font)
};

class MemoryMenu : public Menu {
   public:
    MemoryMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};

class PracticeMenu : public Menu {
   public:
    PracticeMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};

class SettingsMenu : public Menu {
   public:
    SettingsMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};

class ToolsMenu : public Menu {
   public:
    ToolsMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};