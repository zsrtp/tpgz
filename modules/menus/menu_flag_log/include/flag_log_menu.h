#pragma once
#include "menus/menu.h"

class FlagLogMenu : public Menu {
public:
    FlagLogMenu(Cursor&);
    virtual ~FlagLogMenu();
    virtual void draw();

private:
    Line lines[1];
};
