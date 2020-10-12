#pragma once
#include <stdint.h>

#define COMMANDS_AMNT 9

extern bool reload_area_flag;

extern bool commands_states[COMMANDS_AMNT];

namespace Commands {
    enum Commands {
        CMD_STORE_POSITION = 0,
        CMD_LOAD_POSITION = 1,
        CMD_MOON_JUMP = 2,
        CMD_RELOAD_AREA = 3,
        CMD_TIMER_TOGGLE = 4,
        CMD_TIMER_RESET = 5,
        CMD_GORGE_VOID = 6,
        CMD_FREE_CAM = 7,
        CMD_MOVE_LINK = 8
    };

    void process_inputs();
    void enable_command(int idx);
    void disable_command(int idx);
    void reload_area();
}  // namespace Commands