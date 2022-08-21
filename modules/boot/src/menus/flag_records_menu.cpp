#include "menus/flag_records_menu.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "settings.h"
#include "utils/draw.h"
#include "utils/texture.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/msl_c/string.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define MAX_DISPLAY_LINES 8
#define WHITE_RGBA 0xFFFFFFFF
#define MAX_RECORD_OPTIONS 4
#define FLAG_RECORD_INDEX 0

KEEP_FUNC FlagRecordsMenu::FlagRecordsMenu() : Menu() {}

#ifdef GCN_PLATFORM
#define SCRL_FORW_BUTTON (GZPad::X)
#define SCRL_BACK_BUTTON (GZPad::Y)
#define SCRL_FORW_TEXT "X"
#define SCRL_BACK_TEXT "Y"
#endif
#ifdef WII_PLATFORM
#define SCRL_FORW_BUTTON (GZPad::TWO)
#define SCRL_BACK_BUTTON (GZPad::ONE)
#define SCRL_FORW_TEXT "2"
#define SCRL_BACK_TEXT "1"
#endif

void FlagRecordsMenu::drawFlagRecord(uint8_t* record) {
    if (cursor.y > 0) {
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            if (l_bitIdx == 0) {
                l_bitIdx = 7;
            } else if (l_bitIdx >= 0 && l_bitIdx < 8) {
                l_bitIdx--;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            if (l_bitIdx == 7) {
                l_bitIdx = 0;
            } else if (l_bitIdx >= 0 && l_bitIdx < 8) {
                l_bitIdx++;
            }
        }
    }

    for (uint8_t i = 0; i < MAX_DISPLAY_LINES; i++) {
        const float x_offset = 20.0f;
        float y_offset = (80.0f + i * 20.0f);

        int idx_num;
        if (cursor.y > MAX_DISPLAY_LINES) {
            idx_num = i + (cursor.y - MAX_DISPLAY_LINES);
        } else {
            idx_num = i;
        }

        char offset[6];
        sprintf(offset, "0x%02X:", idx_num);

        float flag_x_offset = x_offset + Font::getStrWidth(offset);
        for (int bit = 0; bit < 8; bit++) {
            if (*(record + idx_num) & (1 << bit)) {
                Draw::drawRect(0xFFFFFFFF, {flag_x_offset + ((7 - bit) * 20.0f), y_offset - 13.0f},
                               {16, 16}, &l_flagOnTex._texObj);
            } else {
                Draw::drawRect(0xFFFFFFFF, {flag_x_offset + ((7 - bit) * 20.0f), y_offset - 13.0f},
                               {16, 16}, &l_flagOffTex._texObj);
            }
        }

        // Draw Flag cursor
        if (cursor.y == (idx_num + 1)) {
            Draw::drawRect(0x0080FF77,
                           {(flag_x_offset + ((7 - l_bitIdx) * 20.0f)), y_offset - 13.0f},
                           {16, 16});
        }

        if (GZ_getButtonTrig(SELECTION_BUTTON)) {
            if (cursor.y == (idx_num + 1)) {
                *(record + idx_num) ^= (1 << l_bitIdx);
            }
        }

        uint32_t color = cursor.y == (idx_num + 1) ? CURSOR_RGBA : WHITE_RGBA;
        GZ_drawText(offset, x_offset, y_offset, color, GZ_checkDropShadows());
    }
}

void FlagRecordsMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (l_flagOnTex.loadCode == TexCode::TEX_UNLOADED) {
        load_texture("tpgz/tex/flagOn.tex", &l_flagOnTex);
    }

    if (l_flagOffTex.loadCode == TexCode::TEX_UNLOADED) {
        load_texture("tpgz/tex/flagOff.tex", &l_flagOffTex);
    }

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        free_texture(&l_flagOnTex);
        free_texture(&l_flagOffTex);
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(GZPad::Z)) {
        cursor.y = 0;
    }

    int max_flags = 0;
    switch (l_recIdx) {
    case 0:
        max_flags = 0x20;
        drawFlagRecord((uint8_t*)&g_dComIfG_gameInfo.info.mMemory.mBit.mTbox);
        break;
    case 1:
        max_flags = 0x100;
        drawFlagRecord((uint8_t*)&g_dComIfG_gameInfo.info.mSavedata.mEvent.mEvent);
        break;
    case 2:
        max_flags = 0x18;
        drawFlagRecord((uint8_t*)&g_dComIfG_gameInfo.info.mSavedata.mMiniGame);
        break;
    case 3:
        max_flags = 0x18;
        drawFlagRecord((uint8_t*)&g_dComIfG_gameInfo.info.mDan.mSwitch);
        break;
    }

    if (GZ_getButtonTrig(SCRL_BACK_BUTTON)) {
        cursor.y -= 0x10;
        if (cursor.y < 0) {
            cursor.y = 0;
        }
    } else if (GZ_getButtonTrig(SCRL_FORW_BUTTON)) {
        cursor.y += 0x10;
        if (cursor.y > max_flags + 1) {
            cursor.y = max_flags;
        }
    }

    if (cursor.y == FLAG_RECORD_INDEX) {
        cursor.x = l_recIdx;
        cursor.move(MAX_RECORD_OPTIONS, max_flags + 1);

        if (cursor.y == FLAG_RECORD_INDEX) {
            l_recIdx = cursor.x;
        }
    } else {
        cursor.move(0, max_flags + 1);
    }

    ListMember rec_opt[MAX_RECORD_OPTIONS] = {"stage", "event", "minigame", "danbit"};
    char record_type[9];
    sprintf(record_type, " <%s>", rec_opt[l_recIdx].member);
    uint32_t color = cursor.y == 0 ? CURSOR_RGBA : WHITE_RGBA;

    GZ_drawText(record_type, 12.0f, 60.f, color, GZ_checkDropShadows());
    GZ_drawText("DPad/" SCRL_BACK_TEXT "/" SCRL_FORW_TEXT
                " to move cursor, A to toggle flag, Z to top",
                25.0f, 440.f, WHITE_RGBA, GZ_checkDropShadows());
}