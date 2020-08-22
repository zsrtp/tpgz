#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "font.h"
#include "timer.h"

#define FRAME_RATE 29.97

bool timer_visible;

namespace Timer {
    static int timer_frame = 0;
    static int current_frame = 0;
    static int previous_frame = 0;
    static char timer[5];

	static double timer_seconds = 0.0f;
    static char timerS[8];

    void render(Font& font) {
        current_frame = TP::get_frame_count();
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
        sprintf(timer, "%d", timer_frame);
        sprintf(timerS, "%.2f", timer_seconds);
        previous_frame = current_frame;
        font.renderChars(timer, 525.0f, 420.0f, 0XFFFFFFFF);
        font.renderChars(timerS, 525.0f, 435.0f, 0XFFFFFFFF);

    }  // namespace Timer
}  // namespace Timer