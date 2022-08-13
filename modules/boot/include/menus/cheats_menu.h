#pragma once

#include "menu.h"
#include "cheats.h"

class CheatsMenu : public Menu {
public:
    CheatsMenu();
    virtual void draw();

    Cursor cursor;
private:
    Line lines[CHEAT_AMNT];
};