#pragma once
#include <stdint.h>

#ifdef GCN_PLATFORM
#define COMMANDS_AMNT 9
#define GORGE_VOID_BUTTONS (Pad::L | Pad::Z)
#define STORE_POSITION_BUTTONS (Pad::DPAD_UP | Pad::R)
#define LOAD_POSITION_BUTTONS (Pad::DPAD_DOWN | Pad::R)
#define MOON_JUMP_BUTTONS (Pad::R | Pad::A)
#define RELOAD_AREA_BUTTONS (Pad::L | Pad::R | Pad::A | Pad::START)
#define TIMER_TOGGLE_BUTTONS (Pad::Z | Pad::A)
#define TIMER_RESET_BUTTONS (Pad::Z | Pad::B)
#define FREE_CAM_BUTTONS (Pad::Z | Pad::B | Pad::A)
#define MOVE_LINK_BUTTONS (Pad::L | Pad::R | Pad::Y)
#define FRAME_ADVANCE_BUTTONS (Pad::L | Pad::R | Pad::X)
#define GORGE_VOID_TEXT "L+Z"
#define STORE_POSITION_TEXT "D-PAD up + R"
#define LOAD_POSITION_TEXT "D-PAD down + R"
#define MOON_JUMP_TEXT "R+A"
#define RELOAD_AREA_TEXT "L+R+A+Start"
#define TIMER_TOGGLE_TEXT "Z+A"
#define TIMER_RESET_TEXT "Z+B"
#define FREE_CAM_TEXT "Z+B+A"
#define MOVE_LINK_TEXT "L+R+Y"
#define FRAME_ADVANCE_TEXT "L+R+X"
#endif
#ifdef WII_PLATFORM
#define COMMANDS_AMNT 10
#define GORGE_VOID_BUTTONS (Mote::Z | Mote::C | Mote::A | Mote::ONE)
#define BACK_IN_TIME_BUTTONS (Mote::Z | Mote::C | Mote::A | Mote::TWO)
#define STORE_POSITION_BUTTONS (Mote::Z | Mote::C | Mote::ONE)
#define LOAD_POSITION_BUTTONS (Mote::Z | Mote::C | Mote::TWO)
#define MOON_JUMP_BUTTONS (Mote::Z | Mote::C | Mote::A)
#define RELOAD_AREA_BUTTONS (Mote::Z | Mote::C | Mote::B | Mote::TWO)
#define TIMER_TOGGLE_BUTTONS (Mote::Z | Mote::C | Mote::A | Mote::B)
#define TIMER_RESET_BUTTONS (Mote::Z | Mote::C | Mote::B | Mote::ONE)
#define FREE_CAM_BUTTONS (Mote::Z | Mote::C | Mote::B | Mote::MINUS)
#define MOVE_LINK_BUTTONS (Mote::Z | Mote::C | Mote::B | Mote::PLUS)
#define FRAME_ADVANCE_BUTTONS (Mote::Z | Mote::C | Mote::B | Mote::DPAD_RIGHT)
#define GORGE_VOID_TEXT "Z+C+A+1"
#define BACK_IN_TIME_TEXT "Z+C+A+2"
#define STORE_POSITION_TEXT "Z+C+1"
#define LOAD_POSITION_TEXT "Z+C+2"
#define MOON_JUMP_TEXT "Z+C+A"
#define RELOAD_AREA_TEXT "Z+C+B+2"
#define TIMER_TOGGLE_TEXT "Z+C+A+B"
#define TIMER_RESET_TEXT "Z+C+B+1"
#define FREE_CAM_TEXT "Z+C+B+Minus"
#define MOVE_LINK_TEXT "Z+C+B+Plus"
#define FRAME_ADVANCE_TEXT "Z+C+B+D-PAD right"
#endif

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
#ifdef WII_PLATFORM
    CMD_BIT,
#endif
    CMD_FREE_CAM,
    CMD_MOVE_LINK,
    CMD_FRAME_ADVANCE
};

void process_inputs();
void enable_command(int idx);
void disable_command(int idx);
void reload_area();
}  // namespace Commands