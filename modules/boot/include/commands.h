#pragma once
#include <stdint.h>
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"
#include "utils/containers/deque.h"

#ifdef GCN_PLATFORM
#define COMMANDS_AMNT 10
#define STORE_POSITION_BUTTONS (CButton::DPAD_UP | CButton::R)
#define LOAD_POSITION_BUTTONS (CButton::DPAD_DOWN | CButton::R)
#define MOON_JUMP_BUTTONS (CButton::R | CButton::A)
#define RELOAD_AREA_BUTTONS (CButton::L | CButton::R | CButton::A | CButton::START)
#define TIMER_TOGGLE_BUTTONS (CButton::Z | CButton::A)
#define TIMER_RESET_BUTTONS (CButton::Z | CButton::B)
#define FREE_CAM_BUTTONS (CButton::Z | CButton::B | CButton::A)
#define MOVE_LINK_BUTTONS (CButton::L | CButton::R | CButton::Y)
#define FRAME_PAUSE_BUTTONS (CButton::R | CButton::DPAD_UP)
#define FRAME_ADVANCE_BUTTONS (CButton::R | CButton::DPAD_RIGHT)
#endif

#ifdef WII_PLATFORM
#define COMMANDS_AMNT 11
#define BACK_IN_TIME_BUTTONS (CButton::Z | CButton::C | CButton::A | CButton::TWO)
#define STORE_POSITION_BUTTONS (CButton::Z | CButton::C | CButton::ONE)
#define LOAD_POSITION_BUTTONS (CButton::Z | CButton::C | CButton::TWO)
#define MOON_JUMP_BUTTONS (CButton::Z | CButton::C | CButton::A)
#define RELOAD_AREA_BUTTONS (CButton::Z | CButton::C | CButton::B | CButton::TWO)
#define TIMER_TOGGLE_BUTTONS (CButton::Z | CButton::C | CButton::A | CButton::B)
#define TIMER_RESET_BUTTONS (CButton::Z | CButton::C | CButton::B | CButton::ONE)
#define FREE_CAM_BUTTONS (CButton::Z | CButton::C | CButton::B | CButton::MINUS)
#define MOVE_LINK_BUTTONS (CButton::Z | CButton::C | CButton::B | CButton::PLUS)
#define FRAME_PAUSE_BUTTONS (CButton::Z | CButton::C | CButton::PLUS | CButton::MINUS)
#define FRAME_ADVANCE_BUTTONS (CButton::TWO)
#endif

extern bool reload_area_flag;

extern bool g_commandStates[COMMANDS_AMNT];

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
    CMD_FRAME_PAUSE,
};

struct Command {
    Commands id;
    bool& active;
    uint16_t buttons;
    void (*command)();
};

extern tpgz::containers::deque<Command*> g_commands;

bool GZCmd_checkTrig(int combo);

void GZCmd_storePosition();
void GZCmd_loadPosition();
void GZCmd_moonJump();
void GZCmd_reloadArea();
void GZCmd_toggleTimer();
void GZCmd_resetTimer();
#ifdef WII_PLATFORM
void GZCmd_bitPractice();
#endif
void GZCmd_toggleFreeCam();
void GZCmd_toggleMoveLink();
void GZCmd_pauseFrame();

void GZCmd_addCmd(Command* cmd);
Command* GZCmd_removeCmd(Commands cmdId);
Command* GZCmd_getCmd(int id);

void GZCmd_processInputs();
void GZCmd_enable(int idx);
void GZCmd_disable(int idx);