#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "font.h"
#include "timer.h"
#include "menus/tools_menu.h"
#include "menus/position_settings_menu.h"
#include "menus/settings_menu.h"

#define FRAME_RATE 29.97

bool timer_visible;

namespace Timer { 
    static int current_frame = 0;
    static int previous_frame = 0;

	//Timer vars
    static int timer_frame = 0;
    static char timer[5];
    static double timer_seconds = 0.0f;
    static char timerS[8];

	//Load timer vars
	static int load_timer_frame = 0;
    static double load_timer_seconds = 0.0f;
    static char load_timerS[8];

	//IGT timer vars
    static int igt_timer_frame = 0;
    static int igt_timer_hours = 0;
    static int igt_timer_minutes = 0;
    static double igt_timer_seconds = 0.0f;
    static char igt_timer[16];

    void render() {
        current_frame = TP::get_frame_count();

        if (ToolItems[Tools::TIMER_INDEX].active) {
            if (timer_started) {
                timer_frame += current_frame - previous_frame;

                timer_seconds = timer_frame / FRAME_RATE;
            }
            if (reset_timer) {
                timer_frame = 0;
                timer_seconds = 0.0f;
                reset_timer = false;
                timer_started = false;
            }
            tp_sprintf(timer, "%d", timer_frame);
            tp_sprintf(timerS, "%.2f", timer_seconds);
            previous_frame = current_frame;
            Font::gz_renderChars(timer, (sprite_offsets[TIMER_SPR_INDEX].x), (sprite_offsets[TIMER_SPR_INDEX].y), 0XFFFFFFFF, g_drop_shadows);
            Font::gz_renderChars(timerS, (sprite_offsets[TIMER_SPR_INDEX].x), 15.0f + (sprite_offsets[TIMER_SPR_INDEX].y), 0XFFFFFFFF, g_drop_shadows);
		}
            
		if (ToolItems[Tools::LOAD_TIMER_INDEX].active) {
            if (tp_fopScnRq.isLoading == 1) {
                load_timer_frame += current_frame - previous_frame;

                load_timer_seconds = load_timer_frame / FRAME_RATE;
            }
            if (reset_timer) {
                load_timer_frame = 0;
                load_timer_seconds = 0.0f;
                reset_timer = false;
            }
            tp_sprintf(load_timerS, "%.2f", load_timer_seconds);
            previous_frame = current_frame;
            Font::gz_renderChars(load_timerS, sprite_offsets[LOAD_TIMER_SPR_INDEX].x, sprite_offsets[LOAD_TIMER_SPR_INDEX].y, 0XFFFFFFFF, g_drop_shadows);
		}

		if (ToolItems[Tools::IGT_TIMER_INDEX].active) {
            if (timer_started && tp_fopScnRq.isLoading == 0) {
                igt_timer_frame += current_frame - previous_frame;

                igt_timer_seconds = igt_timer_frame / FRAME_RATE;

				if (igt_timer_seconds >= 60.0f) {
                    igt_timer_frame = 0;
					igt_timer_minutes++;

					if (igt_timer_minutes == 60) {
						igt_timer_minutes = 0;
						igt_timer_hours++;
					}
				}
            }
            if (reset_timer) {
                igt_timer_frame = 0;
                igt_timer_hours = 0;
                igt_timer_minutes = 0;
                igt_timer_seconds = 0.0f;
                reset_timer = false;
                timer_started = false;
            }
            tp_sprintf(igt_timer, "%02d:%02d:%05.2f", igt_timer_hours, igt_timer_minutes, igt_timer_seconds);
            previous_frame = current_frame;
            Font::gz_renderChars(igt_timer, sprite_offsets[IGT_TIMER_SPR_INDEX].x, sprite_offsets[IGT_TIMER_SPR_INDEX].y, 0XFFFFFFFF, g_drop_shadows);
		}
        

    }  // namespace Timer
}  // namespace Timer