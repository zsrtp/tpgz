#pragma once

#include <string.h>

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
    MainMenu() : Menu("Main Menu", 99, "Main Menu Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
};

class InventoryMenu : public Menu {
public:
    InventoryMenu() : Menu("Inventory", 0, "Inventory Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
};

class CheatsMenu : public Menu {
public:
    CheatsMenu() : Menu("Cheats", 1, "Cheats Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
};

class WarpingMenu : public Menu {
public:
    WarpingMenu() : Menu("Warping", 2, "Warping Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
};

class MemoryMenu : public Menu {
public:
    MemoryMenu() : Menu("Memory", 3, "Memory Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
};

class SettingsMenu : public Menu {
public:
    SettingsMenu() : Menu("Settings", 4, "Settings Description") {}
    void transition_into(){
        // logic on how to transition into menu
    };
    void render(){
        // graphics stuff
    };
};