#pragma once

extern bool g_gorge_active;
extern bool inject_gorge_flag;

namespace GorgeVoidIndicator {
    void render();
    void run();
    void prep_rupee_roll();
    void warp_to_gorge();
}  // namespace GorgeVoidIndicator