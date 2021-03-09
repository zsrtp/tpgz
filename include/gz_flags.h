#pragma once
#include "font.h"
#ifdef WII_PLATFORM
#define MAX_GZ_FLAGS 15
#endif
#ifdef GCN_PLATFORM
#define MAX_GZ_FLAGS 14
#endif

struct GZFlag {
    bool* activation_flag;
    void (*flag_active_function)();
    void (*flag_deactive_function)();
};

namespace GZFlags {
void apply_active_flags();
}