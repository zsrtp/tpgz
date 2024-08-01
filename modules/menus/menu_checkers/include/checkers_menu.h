#pragma once

#include "menus/menu.h"

#ifdef GCN_PLATFORM
#define GORGE_VOID_TEXT "L+Z"
#endif

#ifdef WII_PLATFORM
#define GORGE_VOID_TEXT "Z+C+A+1"
#define BACK_IN_TIME_TEXT "Z+C+A+2"
#endif

enum CheckersIndex {
    
#ifdef WII_PLATFORM
    BIT_INDEX,
#endif
    COROTD_INDEX,
    GORGE_INDEX,
    MASH_CHECKER_INDEX,
    ROLL_INDEX,
    UMD_INDEX,

    CHECKERS_COUNT,
};

struct CheckersData {
    Cursor cursor;
};

class CheckersMenu : public Menu {
public:
    CheckersMenu(CheckersData&);
    virtual ~CheckersMenu();
    virtual void draw();

private:
    Line lines[CHECKERS_COUNT];
};