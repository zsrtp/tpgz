#pragma once
#include <stdint.h>

struct AreaReload {
    uint8_t temp_flags[0x20];
    uint16_t tears;
};

extern AreaReload g_area_reload;
AreaReload g_area_reload;

namespace Utilities {
void load_save(uint32_t id, char* category);
void load_save_file(const char* fileName);
void set_camera_angle_position();
void set_angle_position();
void trigger_load();
}  // namespace Utilities