#pragma once
#include "font.h"
#include <string.h>

#define INVENTORY_INDEX 0
#define CHEAT_INDEX 1
#define WARPING_INDEX 2
#define MEMORY_INDEX 3
#define PRACTICE_INDEX 4
#define SETTINGS_INDEX 5

#define ROLL_INDEX 0
#define GORGE_INDEX 1

struct Line {
    char line[50];
    const int idx;
    bool enabled;
    char description[100];
};

extern bool mm_visible;
extern bool prac_visible;

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
   private:
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
    void render(){
        // graphics stuff
    };
};

class CheatsMenu : public Menu {
   public:
    CheatsMenu() : Menu("cheats", 2, "Cheats Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
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
    void transition_into(){
        // logic on how to transition into menu
    };
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