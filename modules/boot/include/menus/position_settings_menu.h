#pragma once

#include "menu.h"

#define SPRITES_AMNT 8
enum SpritesIndex {
    MENU_INDEX,
    VIEWER_INDEX,
    DEBUG_INFO_INDEX,
    TIMER_SPR_INDEX,
    LOAD_TIMER_SPR_INDEX,
    IGT_TIMER_SPR_INDEX,
    FIFO_SPR_INDEX,
    HEAP_INFO_INDEX
};

#define POSITION_SETTINGS_NO_SELECTION ((uint8_t)-1)

extern Vec2 g_spriteOffsets[SPRITES_AMNT];

class PosSettingsMenu : public Menu {
public:
    static void initDefaults();
    PosSettingsMenu();
    virtual void draw();

    Cursor cursor;
private:
    bool init_once;

    float l_cursorSpeed;
    uint8_t l_selItem;

    Line lines[SPRITES_AMNT];
};