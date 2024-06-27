#pragma once

#include "menus/menu.h"
#include "tools.h"

/// 3 seconds of inactivity before going back from combo mode to normal mode
#define COMBO_MODE_INACTIVITY_TIMEOUT (90)

struct ComboData {
    uint8_t l_tunicCol_idx;
};

enum ComboId {
    CMB_FRAME_PAUSE,
    CMB_FRAME_ADVANCE,
    CMB_TIMER_TOGGLE,
    CMB_TIMER_RESET,
    CMB_STORE_POSITION,
    CMB_LOAD_POSITION,
    CMB_RELOAD_AREA,
    CMB_FREE_CAM,
    CMB_MOVE_LINK,
#ifdef WII_PLATFORM
    CMB_BIT,
#endif
    CMB_GORGE_VOID,
    CMB_MOON_JUMP,

    CMB_COUNT,
};

class ComboMenu : public Menu {
public:
    ComboMenu(Cursor&, ComboData&);
    virtual ~ComboMenu();
    virtual void draw();
    void execute();
    void renderLine(int i, uint16_t cmb);

private:
    bool m_inputMode = false;
    bool m_selectBtnActive = false;
    uint16_t m_buttons = 0;
    uint16_t m_prevButtons = 0;
    size_t m_keepInputModeCounter = 0;

    Line lines[CMB_COUNT];
};