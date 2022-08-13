#pragma once

#include "menu.h"

#ifdef WII_PLATFORM
#define TOOL_AMNT 21
#endif
#ifdef GCN_PLATFORM
#define TOOL_AMNT 20
#endif

enum ToolsIndex {
    RELOAD_AREA_INDEX,
    FRAME_ADVANCE_INDEX,
    FAST_BONK_INDEX,
    FAST_MOVEMENT_INDEX,
    GORGE_INDEX,
#ifdef WII_PLATFORM
    BIT_INDEX,
#endif
    COROTD_INDEX,
    UMD_INDEX,
    INPUT_VIEWER_INDEX,
    LINK_DEBUG_INDEX,
    HEAP_DEBUG_INDEX,
    SAND_INDEX,
    ROLL_INDEX,
    TELEPORT_INDEX,
    TURBO_MODE_INDEX,
    TIMER_INDEX,
    LOAD_TIMER_INDEX,
    IGT_TIMER_INDEX,
    FREE_CAM_INDEX,
    MOVE_LINK_INDEX,
    TUNIC_COLOR_INDEX
};

struct Tool {
    enum ToolsIndex id;
    bool active;
};

void GZ_applyCheats();

extern Tool g_tools[TOOL_AMNT];

extern int g_tunic_color;
extern bool g_tunic_color_flag;

enum tunic_color { GREEN, BLUE, RED, ORANGE, YELLOW, WHITE, CYCLE, TUNIC_COLOR_COUNT };

struct TunicColor {
    char name[7];
    bool active;
};

#define TUNIC_COLOR_AMNT 7
extern TunicColor TunicColors[TUNIC_COLOR_AMNT];

class ToolsMenu : public Menu {
public:
    ToolsMenu();
    virtual void draw();
    static void setTunicColor();

    Cursor cursor;
private:
    uint8_t l_tunicCol_idx;

    Line lines[TOOL_AMNT];
};