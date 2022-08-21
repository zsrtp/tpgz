#pragma once
#include "menu.h"

class WatchesMenu : public Menu {
public:
    WatchesMenu();
    virtual void draw();
    void drawMemoryLines();

    Cursor cursor;
};
