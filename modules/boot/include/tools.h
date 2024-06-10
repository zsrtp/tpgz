#pragma once

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
    MASH_CHECKER_INDEX,
    TELEPORT_INDEX,
    TURBO_MODE_INDEX,
    TIMER_INDEX,
    LOAD_TIMER_INDEX,
    IGT_TIMER_INDEX,
    FREE_CAM_INDEX,
    MOVE_LINK_INDEX,
    TRANSFORM_INDICATOR_INDEX,
    TUNIC_COLOR_INDEX,

    // Entry used as a counter
    TOOLS_COUNT
};

struct Tool {
    enum ToolsIndex id;
    bool active;
};

enum tunic_color { GREEN, BLUE, RED, ORANGE, YELLOW, WHITE, CYCLE, TUNIC_COLOR_COUNT };

struct TunicColor {
    char name[7];
    bool active;
};

#define TUNIC_COLOR_AMNT 7
extern TunicColor TunicColors[TUNIC_COLOR_AMNT];

extern Tool g_tools[TOOLS_COUNT];

extern int g_tunic_color;

void GZ_handleTools();
