#pragma once
#include "font.h"
#include <string.h>

struct Line {
    char line[50];
    const int idx;
};

extern bool visible;

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
    MainMenu() : Menu("Main Menu", 0, "Main Menu Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    static void render(Font& font);
};

class InventoryMenu : public Menu {
   public:
    InventoryMenu() : Menu("Inventory", 1, "Inventory Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
};

class CheatsMenu : public Menu {
   public:
    CheatsMenu() : Menu("Cheats", 2, "Cheats Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
};

class WarpingMenu : public Menu {
   public:
    WarpingMenu() : Menu("Warping", 3, "Warping Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
};

class MemoryMenu : public Menu {
   public:
    MemoryMenu() : Menu("Memory", 4, "Memory Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
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