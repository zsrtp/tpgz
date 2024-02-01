#ifndef PAD_H
#define PAD_H

#include "../types.h"

typedef enum PADMask {
    PAD_CHAN3_BIT = (1 << 28),
    PAD_CHAN2_BIT = (1 << 29),
    PAD_CHAN1_BIT = (1 << 30),
    PAD_CHAN0_BIT = (1 << 31),
} PADMask;

typedef struct PADStatus {
    u16 button;
    s8 stick_x;
    s8 stick_y;
    s8 substick_x;
    s8 substick_y;
    u8 trigger_left;
    u8 trigger_right;
    u8 analog_a;
    u8 analog_b;
    s8 error;
} PADStatus;

#endif /* PAD_H */
