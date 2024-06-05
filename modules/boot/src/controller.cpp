#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "cheats.h"
#include "commands.h"
#include "gz_flags.h"
#include "controller.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "menu.h"
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"

#ifdef GCN_PLATFORM
#define BUTTON_STATES 12
#endif
#ifdef WII_PLATFORM
#define BUTTON_STATES 13
#endif
#define REPEAT_TIME 4
#define REPEAT_DELAY 5

#ifdef GCN_PLATFORM
#define buttonStatus (mPadStatus.button)
#define A_BUTTON (CButton::A)
#define ITEM_WHEEL_BUTTON (CButton::DPAD_DOWN)
#define TRIGGER_BUTTONS (CButton::L | CButton::R)
#endif
#ifdef WII_PLATFORM
#define buttonStatus (mPad.mHoldButton)
#define A_BUTTON (CButton::A)
#define ITEM_WHEEL_BUTTON (CButton::MINUS)
#define TRIGGER_BUTTONS (CButton::Z | CButton::C)
#endif

static uint16_t sButtonsLastFrame = 0;
static uint16_t sButtons = 0;
static uint16_t sButtonsPressed = 0;
static uint16_t sCursorEnableDelay = 0;

struct ButtonState {
    uint16_t button;
    uint32_t pressed_frame;
    bool is_down;
};

#ifdef GCN_PLATFORM
static ButtonState buttonStates[BUTTON_STATES] = {
    {CButton::DPAD_LEFT, 0xFFFFFFFF, false}, {CButton::DPAD_RIGHT, 0xFFFFFFFF, false},
    {CButton::DPAD_DOWN, 0xFFFFFFFF, false}, {CButton::DPAD_UP, 0xFFFFFFFF, false},
    {CButton::Z, 0xFFFFFFFF, false},         {CButton::R, 0xFFFFFFFF, false},
    {CButton::L, 0xFFFFFFFF, false},         {CButton::A, 0xFFFFFFFF, false},
    {CButton::B, 0xFFFFFFFF, false},         {CButton::X, 0xFFFFFFFF, false},
    {CButton::Y, 0xFFFFFFFF, false},         {CButton::START, 0xFFFFFFFF, false},
};
#endif
#ifdef WII_PLATFORM
static ButtonState buttonStates[BUTTON_STATES] = {
    {CButton::DPAD_LEFT, 0xFFFFFFFF, false}, {CButton::DPAD_RIGHT, 0xFFFFFFFF, false},
    {CButton::DPAD_DOWN, 0xFFFFFFFF, false}, {CButton::DPAD_UP, 0xFFFFFFFF, false},
    {CButton::PLUS, 0xFFFFFFFF, false},      {CButton::TWO, 0xFFFFFFFF, false},
    {CButton::ONE, 0xFFFFFFFF, false},       {CButton::B, 0xFFFFFFFF, false},
    {CButton::A, 0xFFFFFFFF, false},         {CButton::MINUS, 0xFFFFFFFF, false},
    {CButton::Z, 0xFFFFFFFF, false},         {CButton::C, 0xFFFFFFFF, false},
    {CButton::HOME, 0xFFFFFFFF, false},
};
#endif

KEEP_FUNC void GZ_readController() {
    sButtonsLastFrame = sButtons;
    sButtons = buttonStatus;
    sButtonsPressed = sButtons & (0xFFFF ^ sButtonsLastFrame);

    for (uint8_t idx = 0; idx < BUTTON_STATES; idx++) {
        buttonStates[idx].is_down = (buttonStates[idx].button & sButtons) != 0;
        if ((buttonStates[idx].button & sButtonsPressed) != 0) {
            buttonStates[idx].pressed_frame = cCt_getFrameCount() + 1;
        }
    }

    GZ_applyCheats();
    if (g_menuMgr->isOpen()) {
#ifdef GCN_PLATFORM
        uint16_t current_input = GZ_getButtonStatus();

        // prevent accidentally moving cursor down when opening menu
        if (!g_cursorEnabled) {
            if (current_input & CButton::DPAD_UP) {
                g_cursorEnabled = true;
            } else if (current_input & (CButton::L | CButton::R)) {
                sCursorEnableDelay = 0;
            } else if (sCursorEnableDelay < 1) {
                sCursorEnableDelay = 1;
            }

            if (sCursorEnableDelay >= 4) {
                g_cursorEnabled = true;
            } else if (sCursorEnableDelay > 0) {
                sCursorEnableDelay++;
            }
        }
#else
        g_cursorEnabled = true;
#endif

        setGamepadButtons(0);
        setGamepadTrig(0);

#ifdef WII_PLATFORM
        mPad.mTrigButton = 0;
#endif

#ifdef GCN_PLATFORM
        buttonStatus = 0x0;
        mPadButton.mRepeat = 0x0;
#endif
    } else {
        g_cursorEnabled = false;
        sCursorEnableDelay = 0;
        GZCmd_processInputs();
    }
}

bool GZ_getButtonPressed(int idx) {
    return buttonStates[idx].is_down;
}

bool GZ_getButtonRepeat(int idx, uint16_t repeat_time) {
    // Needs to be signed due to delta sometimes being negative
    // which causes a subtle bug making held_down_long_enough 
    // true when it shouldn't be
    s32 delta = cCt_getFrameCount() - buttonStates[idx].pressed_frame;

    auto just_clicked = delta == 0;
    auto held_down_long_enough = delta > REPEAT_DELAY;
    auto is_repeat_frame = held_down_long_enough && (delta % repeat_time == 0);
    auto down = GZ_getButtonPressed(idx);
    return down && (just_clicked || is_repeat_frame);
}

bool GZ_getButtonRepeat(int idx) {
    return GZ_getButtonRepeat(idx, REPEAT_TIME);
}

uint16_t GZ_getButtonStatus() {
    return buttonStatus;
}

bool GZ_getButtonTrig(int idx) {
    auto delta = cCt_getFrameCount() - buttonStates[idx].pressed_frame;
    auto just_clicked = delta == 0;

    auto down = GZ_getButtonPressed(idx);
    return down && just_clicked;
}

bool GZ_getButtonHold(int idx, int phase) {
    uint32_t delta = cCt_getFrameCount() - buttonStates[idx].pressed_frame;
    
    if (phase != POST_GAME_LOOP)
        delta++;

    return delta != 0 ? true : false;
}

KEEP_FUNC void GZ_getButtonPressCount(u8& i_pressCounter, int i_button, int i_gzButton) {
    if ((GZ_getButtonStatus() & i_button) && (buttonStates[i_gzButton].button & sButtonsPressed)) {
        i_pressCounter++;
    }
}
