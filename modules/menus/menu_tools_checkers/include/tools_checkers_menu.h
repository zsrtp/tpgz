#pragma once

#include "menus/menu.h"
#include "tools.h"

#ifdef GCN_PLATFORM
#define GORGE_VOID_TEXT "L+Z"
#define PREVIOUS_GORGE_OPTION GZPad::Y
#define PREVIOUS_GORGE_OPTION_TEXT "Y"
#define NEXT_GORGE_OPTION GZPad::X
#define NEXT_GORGE_OPTION_TEXT "X"
#endif

#ifdef WII_PLATFORM
#define GORGE_VOID_TEXT "Z+C+A+1"
#define BACK_IN_TIME_TEXT "Z+C+A+2"
#define PREVIOUS_GORGE_OPTION GZPad::DPAD_LEFT
#define PREVIOUS_GORGE_OPTION_TEXT "DPad Left"
#define NEXT_GORGE_OPTION GZPad::DPAD_RIGHT
#define NEXT_GORGE_OPTION_TEXT "DPad Right"

#endif

enum CheckersIndex {
    
#ifdef WII_PLATFORM
    BIT_INDEX,
    SLASH_INDEX,
#endif
    COROTD_INDEX,
    EBMB_INDEX,
    ELEVATOR_ESCAPE_INDEX,
    LFC_INDEX,
    MASH_CHECKER_INDEX,
    ROLL_INDEX,
    UMD_INDEX,
    FAST_EEL_REGRAB_INDEX,
    GORGE_INDEX,

    CHECKERS_COUNT,
};

struct CheckersData {
    uint8_t l_gorge_idx;
};

class CheckersMenu : public Menu {
public:
    CheckersMenu(Cursor&);
    virtual ~CheckersMenu();
    virtual void draw();

private:
    Line lines[CHECKERS_COUNT];
};