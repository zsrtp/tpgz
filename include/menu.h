#pragma once
#include "font.h"
#include <string.h>

// main menu
#define INVENTORY_INDEX 2
#define CHEAT_INDEX 3
#define WARPING_INDEX 4
#define MEMORY_INDEX 5
#define PRACTICE_INDEX 6
#define SETTINGS_INDEX 7
#define LOG_LEVEL_INDEX 8

// practice
#define ROLL_INDEX 2
#define GORGE_INDEX 3

// cheats
#define INVINCIBLE_INDEX 2
#define INVINCIBLE_ENEMIES_INDEX 3
#define INFINITE_AIR_INDEX 4
#define INFINITE_OIL_INDEX 5
#define INFINITE_BOMBS_INDEX 6
#define INFINITE_RUPEES_INDEX 7
#define INFINITE_ARROWS_INDEX 8
#define MOON_JUMP_INDEX 9
#define TELEPORT_INDEX 10
#define RELOAD_AREA_INDEX 11
#define FAST_MOVEMENT_INDEX 12

struct Line {
    char line[50];
    const int idx;
    char description[100];
};

extern bool mm_visible;
extern bool prac_visible;
extern bool settings_visible;
extern bool cheats_visible;
extern bool trigger_menu_anim;

class Menu {
   protected:
    char MenuName[32];
    int MenuId;
    char MenuDescription[32];

   public:
    Menu() {}
    Menu(const char* _MenuName, int _MenuId, const char* _MenuDescription) {
        strcpy(MenuName, _MenuName);
        strcpy(MenuDescription, _MenuDescription);
        MenuId = _MenuId;
    }
    virtual void transition_into() = 0;
    virtual void render() = 0;
};

class MainMenu : public Menu {
   public:

    MainMenu() : Menu("main menu", 0, "Main Menu Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    static void render(Font& font);
};

class InventoryMenu : public Menu {
   public:

    InventoryMenu() : Menu("inventory", 1, "Inventory Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(Font& Font){
        // graphics stuff
    };
};

class CheatsMenu : public Menu {
   public:

    CheatsMenu() : Menu("cheats", 2, "Cheats Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    static void render(Font& font);
};

class WarpingMenu : public Menu {
   public:

    WarpingMenu() : Menu("warping", 3, "Warping Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
};

class MemoryMenu : public Menu {
   public:

    MemoryMenu() : Menu("memory", 4, "Memory Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(Font& font){
        // graphics stuff
    };
};

class PracticeMenu : public Menu {
   public:

    PracticeMenu() : Menu("practice", 5, "Practice Description") {}
    void transition_into();
    static void render(Font& font);
};

class SettingsMenu : public Menu {
   public:

    SettingsMenu() : Menu("Settings", 5, "Settings Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
};