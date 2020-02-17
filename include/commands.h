#pragma once
#include <stdint.h>

namespace Commands {
    enum Commands {
        STORE_POSITION = 0,
        LOAD_POSITION = 1,
        MOON_JUMP = 2,
        RELOAD_AREA = 3,
    };

    void process_inputs();
    void enable_command(int idx);
    void disable_command(int idx);
}  // namespace Commands