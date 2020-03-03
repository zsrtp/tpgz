#include "libtp_c/include/controller.h"
#include "cheats.h"
#include "controller.h"
#include "menu.h"
#include "commands.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"

#define BUTTON_STATES 12
#define REPEAT_TIME 6
#define REPEAT_DELAY 10

static uint16_t sButtons_down_last_frame = 0;
static uint16_t sButtons_down = 0;
static uint16_t sButtons_pressed = 0;

struct ButtonState {
    uint16_t button;
    uint32_t pressed_frame;
    bool is_down;
};

static ButtonState buttonStates[BUTTON_STATES] = {
    {Controller::Pad::DPAD_LEFT, 0xFFFFFFFF, false},
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

extern "C" uint32_t read_controller() {
    sButtons_down_last_frame = sButtons_down;
    // 0x0100 down last frame
    sButtons_down = tp_mPadStatus.sval;
    // sButtons_down = 0x0200 down this frame
    sButtons_pressed = sButtons_down & (0xFFFF ^ sButtons_down_last_frame);
    // sButtons_pressed = 0x0200 & 0xFEFF
    // sButtons_pressed = 0xFCFF
    

    uint8_t idx = 0;
    for (; idx < BUTTON_STATES; idx++) {
        buttonStates[idx].is_down = (buttonStates[idx].button & sButtons_down) != 0;
        // AND with anything other than itself results in 0, so must be down
        if ((buttonStates[idx].button & sButtons_pressed) != 0) {
            buttonStates[idx].pressed_frame = TP::get_frame_count() + 1;
        }
    }
    
    Cheats::apply_cheats();
    if (mm_visible|| prac_visible || settings_visible || cheats_visible || 
                    tools_visible || inventory_visible || item_wheel_visible || 
                    pause_visible || memory_visible || warping_visible) {
        Controller::set_buttons_down(0x0);
        Controller::set_buttons_pressed(0x0);
        tp_mPadStatus.sval = 0x0;
        tp_mPadButton.sval = 0x0;
    }
    else {
        Commands::process_inputs();
    }
    return 0x80000000;
}

namespace Controller {

    bool button_is_down(int idx) {
        return buttonStates[idx].is_down;
    }

    bool button_is_pressed(int idx) {
        // delta between when you pressed idx button now and before
        auto delta = TP::get_frame_count() - buttonStates[idx].pressed_frame;
        // just clicked is true if you pressed it on this frame
        auto just_clicked = delta == 0;
        // after 10 frames, it's considered held down long enough
        auto held_down_long_enough = delta > REPEAT_DELAY;
        // if held for more than 10f and 
        auto is_repeat_frame = held_down_long_enough && delta % REPEAT_TIME == 0;
        auto down = button_is_down(idx);

        return down && (just_clicked || is_repeat_frame);
    }

    uint32_t get_current_inputs() {
        return tp_mPadStatus.sval;
    }

    bool button_is_held(int idx) {
        auto delta = TP::get_frame_count() - buttonStates[idx].pressed_frame + 1;
        if (delta != 0) {
            return true;
        }
        else {
            return false;
        }
    }
}  // namespace Controller