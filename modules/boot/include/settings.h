#pragma once

#include <stdint.h>
#include "utils/lines.h"

#define CURSOR_RGBA g_cursorColor
#define FONT_OPTIONS_COUNT (sizeof(g_font_opt) / sizeof(g_font_opt[0]))

#define LOAD_AREA 0
#define LOAD_FILE 1

extern bool g_dropShadows;
extern bool g_swap_equips_flag;
extern uint32_t g_reloadType;
extern uint32_t g_fontType;
extern uint32_t g_cursorColorType;
extern ListMember g_font_opt[7];

enum cursor_colors {
    CURSOR_GREEN,
    CURSOR_BLUE,
    CURSOR_RED,
    CURSOR_ORANGE,
    CURSOR_YELLOW,
    CURSOR_PURPLE
};

void GZ_initFont();
