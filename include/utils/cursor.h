#pragma once

#include <stdint.h>
#include "controller.h"

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