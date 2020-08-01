#pragma once
#include "font.h"
#define MAX_GZ_FLAGS 10

struct GZFlag {
    bool* activation_flag;
    void (*flag_active_function)();
    void (*flag_deactive_function)();
};

namespace GZFlags {
    void apply_active_flags();
}