#pragma once
#include <stdint.h>

namespace Utilities {
    void load_save(uint32_t id, char* category);
    void load_save_file(const char* fileName);
    void set_camera_angle_position();
    void set_angle_position();
    void trigger_load();
}