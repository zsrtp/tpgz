#pragma once
#include "menus/menu.h"
#include "practice.h"
#include "gz_flags.h"

#ifdef GCN_PLATFORM
#define PRACTICE_MENU_NUM 6
#elif defined WII_PLATFORM
#define PRACTICE_MENU_NUM 4
#endif

class PracticeMenu : public Menu {
public:
    PracticeMenu(Cursor&);
    virtual ~PracticeMenu();
    virtual void draw();

private:
    Line lines[PRACTICE_MENU_NUM];
};