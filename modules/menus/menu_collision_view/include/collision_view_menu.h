#pragma once

#include "menu.h"

class CollisionViewMenu : public Menu {
public:
    CollisionViewMenu(Cursor&);
    virtual ~CollisionViewMenu();
    virtual void draw();

private:
    Line lines[8];
};
