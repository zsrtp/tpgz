#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "system.h"
#include "libtp_c/include/d/meter/d_meter_HIO.h"

namespace System {
bool camera_run_once;
bool hud_run_once;

void lock_camera() {
    camera_run_once = true;
    dComIfGp_getEventManager().mCameraPlay = 1;
}

void unlock_camera() {
    if (camera_run_once) {
        dComIfGp_getEventManager().mCameraPlay = 0;
        camera_run_once = false;
    }
}

void hide_hud() {
    g_drawHIO.mHUDAlpha = 0.0f;
    hud_run_once = true;
}

void show_hud() {
    if (hud_run_once) {
        g_drawHIO.mHUDAlpha = 1.0f;
        hud_run_once = false;
    }
}
}  // namespace System