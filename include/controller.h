#pragma once

#include <stdint.h>

namespace Controller {
    class Button {
       private:
        uint8_t idx;

       public:
        Button(uint8_t _idx) {
            idx = _idx;
        }
        bool is_pressed();
        bool is_down();
    };

    static Button DPAD_LEFT = Button(0);
    static Button DPAD_RIGHT = Button(1);
    static Button DPAD_DOWN = Button(2);
    static Button DPAD_UP = Button(3);
    static Button Z = Button(4);
    static Button R = Button(5);
    static Button L = Button(6);
    static Button A = Button(7);
    static Button B = Button(8);
    static Button X = Button(9);
    static Button Y = Button(10);
    static Button START = Button(11);
}