#pragma once

#include "menus/menu.h"
#include "tools.h"

#ifdef GCN_PLATFORM
#define FRAME_ADVANCE_TEXT "R + D-Pad Up"
#define FRAME_PAUSE_TEXT "R"
#define GORGE_VOID_TEXT "L+Z"
#define STORE_POSITION_TEXT "D-PAD up + R"
#define LOAD_POSITION_TEXT "D-PAD down + R"
#define RELOAD_AREA_TEXT "L+R+A+Start"
#define TIMER_TOGGLE_TEXT "Z+A"
#define TIMER_RESET_TEXT "Z+B"
#define FREE_CAM_TEXT "Z+B+A"
#define MOVE_LINK_TEXT "L+R+Y"
#endif

#ifdef WII_PLATFORM
#define FRAME_ADVANCE_TEXT "Z+C+Plus+Minus"
#define FRAME_PAUSE_TEXT "2"
#define GORGE_VOID_TEXT "Z+C+A+1"
#define BACK_IN_TIME_TEXT "Z+C+A+2"
#define STORE_POSITION_TEXT "Z+C+1"
#define LOAD_POSITION_TEXT "Z+C+2"
#define RELOAD_AREA_TEXT "Z+C+B+2"
#define TIMER_TOGGLE_TEXT "Z+C+A+B"
#define TIMER_RESET_TEXT "Z+C+B+1"
#define FREE_CAM_TEXT "Z+C+B+Minus"
#define MOVE_LINK_TEXT "Z+C+B+Plus"
#endif

struct ToolsData {
    uint8_t l_tunicCol_idx;
};

class ToolsMenu : public Menu {
public:
    ToolsMenu(Cursor&, ToolsData&);
    virtual ~ToolsMenu();
    virtual void draw();

private:
    uint8_t& l_tunicCol_idx;

    Line lines[TOOLS_COUNT];
};