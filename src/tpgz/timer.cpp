#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "font.h"
#include "timer.h"

namespace Timer {
    static int timer_frame = 0;
    static int current_frame = 0;
    static int previous_frame = 0;
    static char timer[5];

    void render(Font& font) {
        if (timer_visible) {
            current_frame = TP::get_frame_count();
            timer_frame += current_frame - previous_frame;
            previous_frame = current_frame;
            current_frame = TP::get_frame_count();

            if (timer_started) {
                timer_frame += current_frame - previous_frame;
                tp_osReport("%d",timer_frame);
                previous_frame = current_frame;
            }

            if (reset_timer) {
                timer_frame = 0;
                reset_timer = false;
                timer_started = false;
            }
            sprintf(timer, "%d", timer_frame);
            font.renderChars(timer, 300.0f, 300.0f, 0XFFFFFFFF);
        }
    }  // namespace Timer
}