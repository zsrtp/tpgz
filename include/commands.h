#pragma once
#include <stdint.h>

#define COMMANDS_AMNT 10
#define GORGE_VOID_BUTTONS (Pad::L | Pad::Z)
#define STORE_POSITION_BUTTONS (Pad::DPAD_UP | Pad::R)
#define LOAD_POSITION_BUTTONS (Pad::DPAD_DOWN | Pad::R)
#define MOON_JUMP_BUTTONS (Pad::R | Pad::A)
#define RELOAD_AREA_BUTTONS (Pad::L | Pad::R | Pad::A | Pad::START)
#define TIMER_TOGGLE_BUTTONS (Pad::Z | Pad::A)
#define TIMER_RESET_BUTTONS (Pad::Z | Pad::B)
#define FREE_CAM_BUTTONS (Pad::Z | Pad::B | Pad::A)
#define MOVE_LINK_BUTTONS (Pad::L | Pad::R | Pad::Y )
#define FRAME_ADVANCE_BUTTONS (Pad::L | Pad::R | Pad::X )

extern bool reload_area_flag;

extern bool commands_states[COMMANDS_AMNT];

namespace Commands {
    enum Commands {
        CMD_STORE_POSITION,
        CMD_LOAD_POSITION,
        CMD_MOON_JUMP,
        CMD_RELOAD_AREA,
        CMD_TIMER_TOGGLE,
        CMD_TIMER_RESET,
        CMD_GORGE_VOID,
        CMD_FREE_CAM,
        CMD_MOVE_LINK,
        CMD_FRAME_ADVANCE
    };

    void process_inputs();
    void enable_command(int idx);
    void disable_command(int idx);
    void reload_area();
}  // namespace Commands