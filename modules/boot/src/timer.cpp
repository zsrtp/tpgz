#include "timer.h"
#include "font.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/position_settings_menu.h"
#include "menus/settings_menu.h"
#include "menus/tools_menu.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "rels/include/defines.h"

#if defined(GCN_PAL) || defined(WII_PAL)
#define FRAME_RATE 25
#else
#define FRAME_RATE 29.97
#endif

KEEP_FUNC void Timer::drawTimer() {
    if (!g_tools[TIMER_INDEX].active) {
        return;
    }
    static int sTimer = 0;
    static float sTimerSec = 0.0f;

    if (g_timerEnabled) {
        sTimer++;
        sTimerSec = sTimer / FRAME_RATE;
    }

    if (g_resetTimer) {
        sTimer = 0;
        sTimerSec = 0.0f;
        g_resetTimer = false;
        g_timerEnabled = false;
    }

    char timerF[5] = {0};
    char timerS[8] = {0};
    tp_sprintf(timerF, "%d", sTimer);
    tp_sprintf(timerS, "%.2f", sTimerSec);

    Font::GZ_drawStr(timerF, (g_spriteOffsets[TIMER_SPR_INDEX].x),
                     (g_spriteOffsets[TIMER_SPR_INDEX].y), 0xFFFFFFFF, g_dropShadows);
    Font::GZ_drawStr(timerS, (g_spriteOffsets[TIMER_SPR_INDEX].x),
                     15.0f + (g_spriteOffsets[TIMER_SPR_INDEX].y), 0xFFFFFFFF, g_dropShadows);
}

KEEP_FUNC void Timer::drawIGT() {
    if (!g_tools[IGT_TIMER_INDEX].active) {
        return;
    }
    static int sTimer = 0;
    static int sTimerHour = 0;
    static int sTimerMin = 0;
    static float sTimerSec = 0.0f;

    if (g_timerEnabled && !tp_fopScnRq.isLoading) {
        sTimer++;
        sTimerSec = sTimer / FRAME_RATE;

        if (sTimerSec >= 60.0f) {
            sTimer = 0;
            sTimerMin++;

            if (sTimerMin == 60) {
                sTimerMin = 0;
                sTimerHour++;
            }
        }
    }

    if (g_resetTimer) {
        sTimer = 0;
        sTimerHour = 0;
        sTimerMin = 0;
        sTimerSec = 0.0f;
        g_resetTimer = false;
        g_timerEnabled = false;
    }

    char buf[16] = {0};
    tp_sprintf(buf, "%02d:%02d:%05.2f", sTimerHour, sTimerMin, sTimerSec);
    Font::GZ_drawStr(buf, g_spriteOffsets[IGT_TIMER_SPR_INDEX].x,
                     g_spriteOffsets[IGT_TIMER_SPR_INDEX].y, 0xFFFFFFFF, g_dropShadows);
}

KEEP_FUNC void Timer::drawLoadTimer() {
    if (!g_tools[LOAD_TIMER_INDEX].active) {
        return;
    }
    static int sTimer = 0;
    static float sTimerSec = 0.0f;

    if (tp_fopScnRq.isLoading) {
        sTimer++;
        sTimerSec = sTimer / FRAME_RATE;
    }

    if (g_resetTimer) {
        sTimer = 0;
        sTimerSec = 0.0f;
        g_resetTimer = false;
    }

    char buf[8] = {0};
    tp_sprintf(buf, "%.2f", sTimerSec);
    Font::GZ_drawStr(buf, g_spriteOffsets[LOAD_TIMER_SPR_INDEX].x,
                     g_spriteOffsets[LOAD_TIMER_SPR_INDEX].y, 0xFFFFFFFF, g_dropShadows);
}