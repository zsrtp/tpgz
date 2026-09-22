#pragma once

enum ToolsIndex {
    CHECKERS_INDEX,
    CONTROLLER_INDEX,
    LINK_INDEX,
    SCENE_INDEX,
    TIMERS_INDEX,
    RNG_INDEX,

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
