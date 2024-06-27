#pragma once

#include "menus/menu.h"

class CreditsMenu : public Menu {
public:
    CreditsMenu(Cursor& cursor);
    virtual ~CreditsMenu();
    virtual void draw();
};