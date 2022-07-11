#pragma once

#include "menu.h"

#define SPRITES_AMNT 7
enum SpritesIndex {
    MENU_INDEX,
    VIEWER_INDEX,
    DEBUG_INFO_INDEX,
    TIMER_SPR_INDEX,
    LOAD_TIMER_SPR_INDEX,
    IGT_TIMER_SPR_INDEX,
    FIFO_SPR_INDEX
};

extern Vec2 g_spriteOffsets[SPRITES_AMNT];

class PosSettingsMenu : public Menu {
public:
    static void initDefaults();
    PosSettingsMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};