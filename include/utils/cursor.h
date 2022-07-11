#pragma once

#include <stdint.h>
#include "controller.h"

#ifdef GCN_PLATFORM
#define SCROLL_P10_BTN GZPad::Y
#define SCROLL_M10_BTN GZPad::X
#endif

#ifdef WII_PLATFORM
#define SCROLL_P10_BTN Controller::TWO
#define SCROLL_M10_BTN Controller::ONE
#endif

struct Cursor {
    enum Mode {
        MODE_SINGLE_COLUMN,
        MODE_LIST,
        MODE_UNRESTRICTED,
    };

    Cursor() {
        reset();
    }

    void move(int max_x, int max_y);

    template <typename T>
    static void moveList(T& index) {
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            index--;
        } else if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            index++;
        } else if (GZ_getButtonRepeat(SCROLL_M10_BTN)) {
            index -= 10;
        } else if (GZ_getButtonRepeat(SCROLL_P10_BTN)) {
            index += 10;
        }
    }

    void reset() {
        mode = MODE_SINGLE_COLUMN;
        x = 0;
        y = 0;
        lock_x = false;
        lock_y = false;
    }

    void lock(bool x, bool y) {
        lock_x = x;
        lock_y = y;
    }

    void setMode(uint8_t m) { mode = m; }

    int x = 0;
    int y = 0;
    uint8_t mode = 0;
    bool lock_x = false;
    bool lock_y = false;
};

extern bool g_cursorEnabled;

void GZ_setCursorColor();