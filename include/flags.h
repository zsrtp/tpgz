#pragma once
#define MAX_FLAGS 7

struct MenuFlag {
    bool* activation_flag;
    void (*flag_active_function)();
    void (*flag_deactive_function)() = 0;
};

namespace Flags {
    void apply_active_flags();
}