#include "timer.h"
#include <cstdio>
#include "font.h"
#include "pos_settings.h"
#include "settings.h"
#include "tools.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "rels/include/defines.h"

KEEP_FUNC void Timer::drawTimer() {
    static bool init_start_time = false;
    static OSTime timer = 0;
    static OSTime start_time = 0;
    static int frame_timer = 0;
    static OSCalendarTime ctime;

    auto* stng_timer = GZStng_getSetting(STNG_TOOLS_TIMER);
    if (!stng_timer || !*(bool*)stng_timer->data) {
        init_start_time = false;
        return;
    }

    if (g_timerEnabled) {
        if (!init_start_time) {
            start_time = OSGetTime();
            init_start_time = true;
        }

        timer = (OSGetTime() - start_time);
        OSTicksToCalendarTime(timer, &ctime);
        frame_timer++;
    }

    if (g_resetTimer) {
        timer = 0;
        start_time = 0;
        frame_timer = 0;
        init_start_time = false;
        g_resetTimer = false;
        g_timerEnabled = false;
    }

    char timerF[5] = {0};
    char timerS[13] = {0};
    snprintf(timerF, sizeof(timerF), "%d", frame_timer);
    snprintf(timerS, sizeof(timerS), "%02d:%02d:%02d.%03d", ctime.hours, ctime.minutes, ctime.seconds, ctime.milliseconds);

    Font::GZ_drawStr(timerF, (g_spriteOffsets[TIMER_SPR_INDEX].x),
                     (g_spriteOffsets[TIMER_SPR_INDEX].y), 0xFFFFFFFF, GZ_checkDropShadows());
    Font::GZ_drawStr(timerS, (g_spriteOffsets[TIMER_SPR_INDEX].x),
                     15.0f + (g_spriteOffsets[TIMER_SPR_INDEX].y), 0xFFFFFFFF, GZ_checkDropShadows());
}

KEEP_FUNC void Timer::drawIGT() {
    static bool init_start_time = false;
    static bool init_load_starttime = false;
    static OSTime timer = 0;
    static OSTime start_time = 0;

    static OSTime load_start_time = 0;
    static OSTime load_total_time = 0;
    static OSTime load_timer = 0;

    static OSCalendarTime ctime;
    static OSCalendarTime load_ctime;

    auto* stng_igt_timer = GZStng_getSetting(STNG_TOOLS_IGT_TIMER);
    if (!stng_igt_timer || !*(bool*)stng_igt_timer->data) {
        init_start_time = false;
        return;
    }

    if (g_timerEnabled) {
        if (!init_start_time) {
            start_time = OSGetTime();
            init_start_time = true;
        }

        if (fopScnRq.isLoading) {
            if (!init_load_starttime) {
                load_start_time = OSGetTime();
                init_load_starttime = true;
            }

            if (init_load_starttime) {
                load_timer = OSGetTime() - load_start_time;
            }

            OSTicksToCalendarTime(load_timer, &load_ctime);
        } else {
            init_load_starttime = false;
            load_total_time += load_timer;
            load_timer = 0;

            timer = (OSGetTime() - start_time) - load_total_time;
            OSTicksToCalendarTime(timer, &ctime);
        }
    }

    if (g_resetTimer) {
        timer = 0;
        start_time = 0;
        ctime.hours = 0;
        ctime.minutes = 0;
        ctime.seconds = 0;
        ctime.milliseconds = 0;
        load_total_time = 0;
        init_start_time = false;
        g_resetTimer = false;
        g_timerEnabled = false;
    }

    char buf[16] = {0};
    snprintf(buf, sizeof(buf), "%02d:%02d:%02d.%03d", ctime.hours, ctime.minutes, ctime.seconds, ctime.milliseconds);
    Font::GZ_drawStr(buf, g_spriteOffsets[IGT_TIMER_SPR_INDEX].x,
                     g_spriteOffsets[IGT_TIMER_SPR_INDEX].y, 0xFFFFFFFF, GZ_checkDropShadows());
}

KEEP_FUNC void Timer::drawLoadTimer() {
    static bool init_load_starttime = false;

    static OSTime load_start_time = 0;
    static OSTime load_total_time = 0;
    static OSTime load_timer = 0;

    static OSCalendarTime load_ctime;

    auto* stng_load_timer = GZStng_getSetting(STNG_TOOLS_LOAD_TIMER);
    if (!stng_load_timer || !*(bool*)stng_load_timer->data) {
        return;
    }

    if (fopScnRq.isLoading) {
        if (!init_load_starttime) {
            load_start_time = OSGetTime();
            init_load_starttime = true;
        }

        if (init_load_starttime) {
            load_timer = OSGetTime() - load_start_time;
        }
    } else {
        init_load_starttime = false;
        load_total_time += load_timer;
        load_timer = 0;

        OSTicksToCalendarTime(load_total_time, &load_ctime);
    }

    if (g_resetTimer) {
        load_ctime.hours = 0;
        load_ctime.minutes = 0;
        load_ctime.seconds = 0;
        load_ctime.milliseconds = 0;
        load_total_time = 0;
        g_resetTimer = false;
        g_timerEnabled = false;
    }

    char buf[16] = {0};
    snprintf(buf, sizeof(buf), "%02d:%02d:%02d.%03d", load_ctime.hours, load_ctime.minutes, load_ctime.seconds, load_ctime.milliseconds);
    Font::GZ_drawStr(buf, g_spriteOffsets[LOAD_TIMER_SPR_INDEX].x,
                     g_spriteOffsets[LOAD_TIMER_SPR_INDEX].y, 0xFFFFFFFF, GZ_checkDropShadows());
}