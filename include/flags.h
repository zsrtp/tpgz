#pragma once
#include "font.h"
#define MAX_MENU_FLAGS 10

struct MenuFlag {
    bool* activation_flag;
    void (*flag_active_function)();
    void (*flag_deactive_function)();
};

namespace Flags {
    void apply_active_flags();
}