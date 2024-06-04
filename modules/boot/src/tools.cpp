#include "tools.h"

int g_tunic_color;

Tool g_tools[TOOLS_COUNT] = {
    {RELOAD_AREA_INDEX, false},   {FRAME_ADVANCE_INDEX, false}, {FAST_BONK_INDEX, false},
    {FAST_MOVEMENT_INDEX, false}, {GORGE_INDEX, false},
#ifdef WII_PLATFORM
    {BIT_INDEX, false},
#endif
    {COROTD_INDEX, false},        {UMD_INDEX, false},           {INPUT_VIEWER_INDEX, false},
    {LINK_DEBUG_INDEX, false},    {HEAP_DEBUG_INDEX, false},    {SAND_INDEX, false},
    {ROLL_INDEX, false},          {MASH_CHECKER_INDEX, false},  {TELEPORT_INDEX, false},
    {TURBO_MODE_INDEX, false},    {TIMER_INDEX, false},         {LOAD_TIMER_INDEX, false},
    {IGT_TIMER_INDEX, false},     {FREE_CAM_INDEX, false},      {MOVE_LINK_INDEX, false},
    {TRANSFORM_INDICATOR_INDEX, false},
};
