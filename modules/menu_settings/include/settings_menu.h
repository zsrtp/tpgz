#pragma once

#include "menu.h"
#include "settings.h"

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

class SettingsMenu : public Menu {
public:
    SettingsMenu(Cursor&);
    virtual ~SettingsMenu();
    virtual void draw();

    Cursor& m_cursor;

private:
    Line lines[9];
};