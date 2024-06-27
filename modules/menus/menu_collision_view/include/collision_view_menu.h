#pragma once

#include "menus/menu.h"

class CollisionViewMenu : public Menu {
public:
    CollisionViewMenu(Cursor&);
    virtual ~CollisionViewMenu();
    virtual void draw();

private:
    Line lines[10];
};
