#include "libtp_c/include/controller.h"
#include "cheats.h"
#include "commands.h"
#include "controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menu.h"

#ifdef GCN_PLATFORM
#define BUTTON_STATES 12
#endif
#ifdef WII_PLATFORM
#define BUTTON_STATES 13
#endif
#define REPEAT_TIME 4
#define REPEAT_DELAY 5

#ifdef GCN_PLATFORM
#define buttons_down (tp_mPadStatus.sval)
#define A_BUTTON (Controller::Pad::A)
#define ITEM_WHEEL_BUTTON (Controller::Pad::DPAD_DOWN)
#define TRIGGER_BUTTONS (Controller::Pad::L | Controller::Pad::R)
#endif
#ifdef WII_PLATFORM
#define buttons_down (tp_mPad.buttons)
#define A_BUTTON (Controller::Mote::A)
#define ITEM_WHEEL_BUTTON (Controller::Mote::MINUS)
#define TRIGGER_BUTTONS (Controller::Mote::Z | Controller::Mote::C)
#endif

static uint16_t sButtons_down_last_frame = 0;
static uint16_t sButtons_down = 0;
static uint16_t sButtons_pressed = 0;
bool a_held = true;
bool a_held_last_frame = true;
uint16_t current_input = 0x0000;

bool can_move_cursor = false;
static uint16_t sNum_frames_cursor_buffer = 0;

struct ButtonState {
    uint16_t button;
    uint32_t pressed_frame;
    bool is_down;
};

#ifdef GCN_PLATFORM
static ButtonState buttonStates[BUTTON_STATES] = {{Controller::Pad::DPAD_LEFT, 0xFFFFFFFF, false},
                                                  {Controller::Pad::DPAD_RIGHT, 0xFFFFFFFF, false},
                                                  {Controller::Pad::DPAD_DOWN, 0xFFFFFFFF, false},
                                                  {Controller::Pad::DPAD_UP, 0xFFFFFFFF, false},
                                                  {Controller::Pad::Z, 0xFFFFFFFF, false},
                                                  {Controller::Pad::R, 0xFFFFFFFF, false},
                                                  {Controller::Pad::L, 0xFFFFFFFF, false},
                                                  {Controller::Pad::A, 0xFFFFFFFF, false},
                                                  {Controller::Pad::B, 0xFFFFFFFF, false},
                                                  {Controller::Pad::X, 0xFFFFFFFF, false},
                                                  {Controller::Pad::Y, 0xFFFFFFFF, false},
                                                  {Controller::Pad::START, 0xFFFFFFFF, false}};
#endif
#ifdef WII_PLATFORM
static ButtonState buttonStates[BUTTON_STATES] = {{Controller::Mote::DPAD_LEFT, 0xFFFFFFFF, false},
                                                  {Controller::Mote::DPAD_RIGHT, 0xFFFFFFFF, false},
                                                  {Controller::Mote::DPAD_DOWN, 0xFFFFFFFF, false},
                                                  {Controller::Mote::DPAD_UP, 0xFFFFFFFF, false},
                                                  {Controller::Mote::PLUS, 0xFFFFFFFF, false},
                                                  {Controller::Mote::TWO, 0xFFFFFFFF, false},
                                                  {Controller::Mote::ONE, 0xFFFFFFFF, false},
                                                  {Controller::Mote::B, 0xFFFFFFFF, false},
                                                  {Controller::Mote::A, 0xFFFFFFFF, false},
                                                  {Controller::Mote::MINUS, 0xFFFFFFFF, false},
                                                  {Controller::Mote::Z, 0xFFFFFFFF, false},
                                                  {Controller::Mote::C, 0xFFFFFFFF, false},
                                                  {Controller::Mote::HOME, 0xFFFFFFFF, false}};
#endif

namespace Controller {

void read_controller() {
    sButtons_down_last_frame = sButtons_down;
    sButtons_down = buttons_down;
    sButtons_pressed = sButtons_down & (0xFFFF ^ sButtons_down_last_frame);

    uint8_t idx = 0;
    for (; idx < BUTTON_STATES; idx++) {
        buttonStates[idx].is_down = (buttonStates[idx].button & sButtons_down) != 0;
        if ((buttonStates[idx].button & sButtons_pressed) != 0) {
            buttonStates[idx].pressed_frame = TP::get_frame_count() + 1;
        }
    }

    Cheats::apply_cheats();
    if (MenuRendering::is_menu_open() == true) {
        current_input = Controller::get_current_inputs();
        a_held = a_held_last_frame && current_input == A_BUTTON;
        a_held_last_frame = current_input == A_BUTTON;

#ifdef GCN_PLATFORM
        // prevent accidentally moving cursor down when opening menu
        if (!can_move_cursor) {
            if (current_input & Controller::Pad::DPAD_UP) {
                can_move_cursor = true;
            } else if (current_input & (Controller::Pad::L | Controller::Pad::R)) {
                sNum_frames_cursor_buffer = 0;
            } else if (sNum_frames_cursor_buffer < 1) {
                sNum_frames_cursor_buffer = 1;
            }

            if (sNum_frames_cursor_buffer >= 4) {
                can_move_cursor = true;
            } else if (sNum_frames_cursor_buffer > 0) {
                sNum_frames_cursor_buffer++;
            }
        }
#else
        can_move_cursor = true;
#endif

        Controller::set_buttons_down(0x0);
        Controller::set_buttons_pressed(0x0);
#ifdef GCN_PLATFORM
        buttons_down = 0x0;
        tp_mPadButton.sval = 0x0;
#endif
    } else {
        can_move_cursor = false;
        sNum_frames_cursor_buffer = 0;
        Commands::process_inputs();
    }
}

bool button_is_down(int idx) {
    return buttonStates[idx].is_down;
}

bool button_is_pressed(int idx, uint16_t repeat_time) {
    auto delta = TP::get_frame_count() - buttonStates[idx].pressed_frame;
    auto just_clicked = delta == 0;
    auto held_down_long_enough = delta > REPEAT_DELAY;
    auto is_repeat_frame = held_down_long_enough && delta % repeat_time == 0;
    auto down = button_is_down(idx);
    return down && (just_clicked || is_repeat_frame);
}

bool button_is_pressed(int idx) {
    return button_is_pressed(idx, REPEAT_TIME);
}

uint16_t get_current_inputs() {
    return buttons_down;
}

bool button_is_held(int idx) {
    auto delta = TP::get_frame_count() - buttonStates[idx].pressed_frame + 1;
    if (delta != 0) {
        return true;
    } else {
        return false;
    }
}

bool button_is_held_post_loop(int idx) {
    auto delta = TP::get_frame_count() - buttonStates[idx].pressed_frame;
    if (delta != 0) {
        return true;
    } else {
        return false;
    }
}

}  // namespace Controller