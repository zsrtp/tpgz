#pragma once
#include <stdint.h>
#include "saves.h"

struct AreaReload {
    uint8_t temp_flags[0x20];
    uint16_t tears;
};

extern AreaReload g_area_reload;
AreaReload g_area_reload;

#if (NTSCU)
#define sTmpBuf 0x803ecf40
#endif
#if (PAL)
#define sTmpBuf 0x803eeee0
#endif
#if (NTSCJ)
#define sTmpBuf 0x803e7080
#endif

namespace Utilities {
void load_save(uint32_t id, char* category, special* i_specials = nullptr, int size = 0);
void load_save_file(const char* fileName);
void set_camera_angle_position();
void set_angle_position();
void trigger_load();
}  // namespace Utilities