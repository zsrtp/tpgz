#pragma once
#include <stdint.h>

extern bool reload_area_flag;

namespace Commands {
    enum Commands {
        STORE_POSITION = 0,
        LOAD_POSITION = 1,
        MOON_JUMP = 2,
        RELOAD_AREA = 3,
        TIMER_TOGGLE = 4,
        TIMER_RESET = 5
    };

    void process_inputs();
    void enable_command(int idx);
    void disable_command(int idx);
}  // namespace Commands