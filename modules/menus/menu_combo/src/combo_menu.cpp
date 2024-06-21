#include "menus/menu_combo/include/combo_menu.h"
#include <cstdio>
#include "commands.h"
#include "global_data.h"
#include "timer.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/utils.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#ifdef GCN_PLATFORM
#define RESET_COMBO_TEXT "X"
#define RESET_COMBO_BUTTONS GZPad::X
#endif
#ifdef WII_PLATFORM
#define RESET_COMBO_TEXT "Minus"
#define RESET_COMBO_BUTTONS GZPad::MINUS
#endif

KEEP_FUNC ComboMenu::ComboMenu(Cursor& cursor, ComboData& data)
    : Menu(cursor),
      lines{
          {"frame pause: ", CMB_FRAME_PAUSE, "[Reset: " RESET_COMBO_TEXT "] Combo to Pause the game"},
          {"frame advance: ", CMB_FRAME_ADVANCE, "[Reset: " RESET_COMBO_TEXT "] Combo to Advance the game by 1 frame"},
          {"timer toggle: ", CMB_TIMER_TOGGLE, "[Reset: " RESET_COMBO_TEXT "] Combo to Toggle the timer"},
          {"timer reset: ", CMB_TIMER_RESET, "[Reset: " RESET_COMBO_TEXT "] Combo to Reset the timer"},
          {"store position: ", CMB_STORE_POSITION, "[Reset: " RESET_COMBO_TEXT "] Combo to Store the player's position"},
          {"load position: ", CMB_LOAD_POSITION, "[Reset: " RESET_COMBO_TEXT "] Combo to Load the player's position"},
          {"reload area: ", CMB_RELOAD_AREA, "[Reset: " RESET_COMBO_TEXT "] Combo to Reload the area"},
          {"free cam: ", CMB_FREE_CAM, "[Reset: " RESET_COMBO_TEXT "] Combo to Toggle Free Cam"},
          {"move link: ", CMB_MOVE_LINK, "[Reset: " RESET_COMBO_TEXT "] Combo to Toggle Move Link"},
#ifdef WII_PLATFORM
          {"bit: ", CMB_BIT, "[Reset: " RESET_COMBO_TEXT "] Combo to load the BiT save file"},
#endif
          {"gorge void: ", CMB_GORGE_VOID, "[Reset: " RESET_COMBO_TEXT "] Combo to load the Gorge Void save file"},
          {"moon jump: ", CMB_MOON_JUMP, "[Reset: " RESET_COMBO_TEXT "] Combo to Moon Jump"},
      } {}

ComboMenu::~ComboMenu() {}

GZSettingID l_mapping[] = {
    STNG_CMD_FRAME_PAUSE,
    STNG_CMD_FRAME_ADVANCE,
    STNG_CMD_TIMER_TOGGLE,
    STNG_CMD_TIMER_RESET,
    STNG_CMD_STORE_POSITION,
    STNG_CMD_LOAD_POSITION,
    STNG_CMD_RELOAD_AREA,
    STNG_CMD_FREE_CAM,
    STNG_CMD_MOVE_LINK,
#ifdef WII_PLATFORM
    STNG_CMD_BIT,
#endif
    STNG_CMD_GORGE_VOID,
    STNG_CMD_MOON_JUMP,
};

void ComboMenu::execute() {
    if (m_inputMode) {
        if (!m_selectBtnActive) {
            m_prevButtons = m_buttons;
            m_buttons = GZ_getButtonStatusSaved();
        }
        uint16_t released = ~m_buttons & m_prevButtons;

        if ((released != 0 && !m_selectBtnActive) || m_keepInputModeCounter == 0) {
            if (released != 0 && !m_selectBtnActive) {
                GZStng_addSetting(l_mapping[cursor.y], new uint16_t(m_prevButtons), sizeof(uint16_t));
            }
            m_inputMode = false;
            m_keepInputModeCounter = 0;
            m_buttons = 0;
            m_prevButtons = 0;
            m_selectBtnActive = false;
            for (int i = 0; i < CMB_COUNT; i++) {
                lines[i].disabled = false;
            }
        }
    }
}

void ComboMenu::renderLine(int i, uint16_t cmb) {
    char* comboStr = new char[GZCmd_getComboLen(cmb) + 1];
    GZCmd_comboToStr(cmb, comboStr);
    snprintf(lines[i].value, sizeof(lines[i].value), "[%s]", comboStr);
    delete[] comboStr;
}

void ComboMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON) && !m_inputMode) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(RESET_COMBO_BUTTONS) && !m_inputMode) {
        GZStng_removeSetting(l_mapping[cursor.y]);
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON) && !m_inputMode) {
        m_inputMode = true;
        m_selectBtnActive = true;
        m_keepInputModeCounter = COMBO_MODE_INACTIVITY_TIMEOUT;
        for (int i = 0; i < CMB_COUNT; i++) {
            if (i != cursor.y) {
                lines[i].disabled = true;
            }
        }
    }

    if (m_selectBtnActive && !GZ_getButtonPressed(SELECTION_BUTTON)) {
        m_selectBtnActive = false;
    }

    for (int i = 0; i < CMB_COUNT; i++) {
        uint16_t cmb = GZStng_getSettingData(l_mapping[i], (uint16_t)0);
        renderLine(i, cmb);
    }

    if (m_inputMode) {
        if (!m_selectBtnActive) {
            renderLine(cursor.y, m_buttons);
        }
    } else {
        cursor.move(0, MENU_LINE_NUM);
    }

    if (m_keepInputModeCounter > 0) {
        --m_keepInputModeCounter;
    }

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
