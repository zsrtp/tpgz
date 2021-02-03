#pragma once
#include "font.h"
#include "libtp_c/include/gc/OSCache.h"

namespace Utilities {
void show_link_debug_info();
void change_tunic_color();
inline void setup_link_color() {
#ifdef WII_PLATFORM
#ifdef WII_NTSCU_10
#define SWORD_UP_RED_ADDR 0x801176B0
#define SWORD_UP_GREEN_ADDR 0x801176C8
#define SWORD_UP_BLUE_ADDR 0x801176E0
#endif
#ifdef WII_PAL
#define SWORD_UP_RED_ADDR 0x80117d64
#define SWORD_UP_GREEN_ADDR 0x80117d7c
#define SWORD_UP_BLUE_ADDR 0x80117d94
#endif
    *reinterpret_cast<uint32_t*>(SWORD_UP_RED_ADDR) = 0x60000000;  // nop
    gc::os_cache::DCFlushRange((void*)(SWORD_UP_RED_ADDR), sizeof(uint32_t));
    gc::os_cache::ICInvalidateRange((void*)(SWORD_UP_RED_ADDR), sizeof(uint32_t));
    *reinterpret_cast<uint32_t*>(SWORD_UP_GREEN_ADDR) = 0x60000000;  // nop
    gc::os_cache::DCFlushRange((void*)(SWORD_UP_GREEN_ADDR), sizeof(uint32_t));
    gc::os_cache::ICInvalidateRange((void*)(SWORD_UP_GREEN_ADDR), sizeof(uint32_t));
    *reinterpret_cast<uint32_t*>(SWORD_UP_BLUE_ADDR) = 0x60000000;  // nop
    gc::os_cache::DCFlushRange((void*)(SWORD_UP_BLUE_ADDR), sizeof(uint32_t));
    gc::os_cache::ICInvalidateRange((void*)(SWORD_UP_BLUE_ADDR), sizeof(uint32_t));
#endif  // WII_PLATFORM
}
}  // namespace Utilities