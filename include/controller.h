#pragma once

#include <stdint.h>

extern bool a_held;
extern uint16_t current_input;

namespace Controller {
    enum Button {
        DPAD_LEFT = 0,
        DPAD_RIGHT = 1,
        DPAD_DOWN = 2,
        DPAD_UP = 3,
        Z = 4,
        R = 5,
        L = 6,
        A = 7,
        B = 8,
        X = 9,
        Y = 10,
        START = 11,
    };
    bool button_is_pressed(int idx);
    bool button_is_pressed(int idx, uint16_t repeat_time);
    bool button_is_down(int idx);
    bool button_is_held(int idx);
    uint16_t get_current_inputs();
    void read_controller();
}  // namespace Controller