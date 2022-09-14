#pragma once
#include "menu.h"

class MemoryMenu : public Menu {
public:
    MemoryMenu(Cursor&);
    virtual ~MemoryMenu();
    virtual void draw();

private:
    Line lines[3];
};
