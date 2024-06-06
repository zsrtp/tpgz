#pragma once

#include "menu.h"
#include "cheats.h"

#ifdef GCN_PLATFORM
#define MOON_JUMP_TEXT "R+A"
#endif

#ifdef WII_PLATFORM
#define MOON_JUMP_TEXT "Z+C+A"
#endif

class CheatsMenu : public Menu {
public:
    CheatsMenu(Cursor&);
    virtual ~CheatsMenu();
    virtual void draw();

private:
    Line lines[CHEAT_AMNT];
};