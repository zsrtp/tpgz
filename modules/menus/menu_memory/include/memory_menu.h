#pragma once
#include "menus/menu.h"

class MemoryMenu : public Menu {
public:
    MemoryMenu(Cursor&);
    virtual ~MemoryMenu();
    virtual void draw();

private:
    Line lines[3];
};
