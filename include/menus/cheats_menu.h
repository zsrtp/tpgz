#pragma once

#include "menu.h"

class CheatsMenu : public Menu {
public:
    CheatsMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};