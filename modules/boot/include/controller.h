#pragma once

#include <stdint.h>
#include "libtp_c/include/controller.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"

#ifdef GCN_PLATFORM
enum GZPad {
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
#endif

#ifdef WII_PLATFORM
enum GZPad {
    DPAD_LEFT = 0,
    DPAD_RIGHT = 1,
    DPAD_DOWN = 2,
    DPAD_UP = 3,
    PLUS = 4,
    TWO = 5,
    ONE = 6,
    B = 7,
    A = 8,
    MINUS = 9,
    Z = 10,
    C = 11,
    HOME = 12,
};
#endif

bool GZ_getButtonRepeat(int idx);
bool GZ_getButtonRepeat(int idx, uint16_t repeat_time);
bool GZ_getButtonPressed(int idx);
bool GZ_getButtonHold(int idx, int phase = 0);
uint16_t GZ_getButtonStatus();
uint16_t GZ_getButtonStatusSaved();
void GZ_readController();
bool GZ_getButtonTrig(int idx);
void GZ_getButtonPressCount(u8& i_pressCounter, int i_button, int i_gzButton);
bool GZ_getPadTrigAny(uint16_t pad);
