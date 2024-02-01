#ifndef C_COUNTER_H
#define C_COUNTER_H

#include "../../dolphin/types.h"
#include "../../addrs.h"

struct cCounter {
    u32 game_counter;
    u32 game_counter2;
    u32 non_menu_counter;
};

extern cCounter g_Counter;

inline u32 cCt_getFrameCount() {
    return g_Counter.game_counter;
}

#endif /* C_COUNTER_H */
