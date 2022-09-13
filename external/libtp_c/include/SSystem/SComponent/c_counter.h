#ifndef C_COUNTER_H
#define C_COUNTER_H

#include <stdint.h>
#include "../../addrs.h"

struct cCounter {
    uint32_t game_counter;
    uint32_t game_counter2;
    uint32_t non_menu_counter;
};

extern cCounter g_Counter;

inline uint32_t cCt_getFrameCount() {
    return g_Counter.game_counter;
}

#endif /* C_COUNTER_H */
