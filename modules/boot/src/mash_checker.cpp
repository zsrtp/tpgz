#include <cstdio>
#include "mash_checker.h"
#include "tools.h"
#include "settings.h"
#include "controller.h"
#include "fifo_queue.h"
#include "pos_settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"
#include "rels/include/defines.h"

u32 getSpeedTextColor(u8 i_bps) {
    if (i_bps >= 11) {
        return 0x00CC00FF;
    } else if (i_bps >= 9) {
        return 0xCCCC00FF;
    } else if (i_bps > 0) {
        return 0xCC0000FF;
    }

    return 0xFFFFFFFF;
}

KEEP_FUNC void GZ_displayButtonMashInfo() {
    static OSTime start_time;
    static bool init_start_time = false;

    static u8 abtn_presses = 0;
    static u8 last_abtn_presses = 0;
    static u8 a_bps = 0;

    static u8 bbtn_presses = 0;
    static u8 last_bbtn_presses = 0;
    static u8 b_bps = 0;

    if (!g_tools[MASH_CHECKER_INDEX].active) {
        init_start_time = false;
        return;
    }

    if (!init_start_time) {
        start_time = OSGetTime();

        abtn_presses = 0;
        last_abtn_presses = 0;
        a_bps = 0;

        bbtn_presses = 0;
        last_bbtn_presses = 0;
        b_bps = 0;

        init_start_time = true;
    }

    OSTime current_time = OSGetTime();
    OSTime time_diff = current_time - start_time;
    OSCalendarTime ctime;
    OSTicksToCalendarTime(time_diff, &ctime);

    if (ctime.seconds == 1) {
        a_bps = abtn_presses - last_abtn_presses;
        b_bps = bbtn_presses - last_bbtn_presses;

        last_abtn_presses = abtn_presses;
        last_bbtn_presses = bbtn_presses;

        start_time = current_time;
    }

    GZ_getButtonPressCount(abtn_presses, CButton::A, GZPad::A);
    GZ_getButtonPressCount(bbtn_presses, CButton::B, GZPad::B);

    char abtn_text[8] = {0};
    snprintf(abtn_text, sizeof(abtn_text), "A: %d", a_bps);
    Font::GZ_drawStr(abtn_text, g_spriteOffsets[MASH_INFO_INDEX].x,
                     g_spriteOffsets[MASH_INFO_INDEX].y, getSpeedTextColor(a_bps), g_dropShadows);

    char bbtn_text[8] = {0};
    snprintf(bbtn_text, sizeof(bbtn_text), "B: %d", b_bps);
    Font::GZ_drawStr(bbtn_text, g_spriteOffsets[MASH_INFO_INDEX].x,
                     g_spriteOffsets[MASH_INFO_INDEX].y + 20.0f, getSpeedTextColor(b_bps),
                     g_dropShadows);
}