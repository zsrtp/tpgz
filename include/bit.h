#pragma once
#ifdef WII_PLATFORM

extern bool g_bit_active;
extern bool inject_bit_flag;

namespace BiTIndicator {
    void render();
    void run();
    void set_camera_angle_position();
}  // namespace BiTIndicator
#endif