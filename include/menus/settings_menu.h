#pragma once

#include "menu.h"

#define CURSOR_RGBA g_cursorColor

enum SettingsIndex {
    AREA_RELOAD_BEHAVIOR_INDEX,
    CURSOR_COLOR_INDEX,
    FONT_INDEX,
    DROP_SHADOWS_INDEX,
    SWAP_EQUIPS_INDEX,
    SAVE_CARD_INDEX,
    LOAD_CARD_INDEX,
    DELETE_CARD_INDEX,
    POS_SETTINGS_MENU_INDEX
};
extern bool g_dropShadows;
extern int g_reloadType;
extern int g_cursorColorType;
extern bool g_cursor_color_flag;
extern bool g_swap_equips_flag;
extern int g_cursorColor;
extern int g_fontType;
#define LOAD_AREA 0
#define LOAD_FILE 1

enum cursor_colors {
    CURSOR_GREEN,
    CURSOR_BLUE,
    CURSOR_RED,
    CURSOR_ORANGE,
    CURSOR_YELLOW,
    CURSOR_PURPLE
};

class SettingsMenu : public Menu {
public:
    static void initFont();
    SettingsMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};