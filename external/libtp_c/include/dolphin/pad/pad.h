#ifndef PAD_H
#define PAD_H

#include <stdint.h>

typedef enum PADMask {
    PAD_CHAN3_BIT = (1 << 28),
    PAD_CHAN2_BIT = (1 << 29),
    PAD_CHAN1_BIT = (1 << 30),
    PAD_CHAN0_BIT = (1 << 31),
} PADMask;

typedef struct PADStatus {
    uint16_t button;
    int8_t stick_x;
    int8_t stick_y;
    int8_t substick_x;
    int8_t substick_y;
    uint8_t trigger_left;
    uint8_t trigger_right;
    uint8_t analog_a;
    uint8_t analog_b;
    int8_t error;
} PADStatus;

#endif /* PAD_H */
