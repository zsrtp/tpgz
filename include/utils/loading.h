#pragma once
#include <stdint.h>
#include "saves.h"

struct AreaReload {
    uint8_t temp_flags[0x20];
    uint16_t tears;
};

extern AreaReload g_area_reload;
AreaReload g_area_reload;

#ifdef GCN_NTSCU
#define sTmpBuf 0x803ecf40
#endif
#ifdef GCN_PAL
#define sTmpBuf 0x803eeee0
#endif
#ifdef GCN_NTSCJ
#define sTmpBuf 0x803e7080
#endif
#ifdef WII_NTSCU_10
#define sTmpBuf 0x8046a3e0
#endif
#ifdef WII_PAL
#define sTmpBuf 0x804522e0
#endif

namespace Utilities {
void load_save(uint32_t id, char* category, special* i_specials = nullptr, int size = 0);
void load_save_file(const char* fileName);
void set_camera_angle_position();
void set_angle_position();
void trigger_load();
}  // namespace Utilities