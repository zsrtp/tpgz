#pragma once
#include "font.h"
#ifdef WII_PLATFORM
#define MAX_GZ_FLAGS 16
#endif
#ifdef GCN_PLATFORM
#define MAX_GZ_FLAGS 15
#endif

struct GZFlag {
    bool* activation_flag;
    int required_phase;
    void (*flag_active_function)();
    void (*flag_deactive_function)();
};

enum LoopPhase { GAME_LOOP, POST_GAME_LOOP };

namespace GZFlags {
void apply_active_flags(int loop_phase);
}