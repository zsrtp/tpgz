#pragma once

#include "menus/menu.h"
#include "pos_settings.h"
#define POSITION_SETTINGS_NO_SELECTION ((uint8_t)-1)

struct PosSettingsData {
    bool init_once;
    float l_cursorSpeed;
    uint8_t l_selItem = POSITION_SETTINGS_NO_SELECTION;
};

class PosSettingsMenu : public Menu {
public:
    PosSettingsMenu(Cursor&, PosSettingsData&);
    virtual ~PosSettingsMenu();
    virtual void draw();

private:
    bool& init_once;

    float& l_cursorSpeed;
    uint8_t& l_selItem;

    Line lines[SPRITES_AMNT];
};