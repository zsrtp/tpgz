#pragma once
#include "menu.h"

class FlagLogMenu : public Menu {
public:
    FlagLogMenu();
    virtual void draw();

    Cursor cursor;

private:
    Line lines[1];
};
