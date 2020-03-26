#include "system.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/draw.h"

namespace System {
    bool camera_run_once;
    bool hud_run_once;

    void lock_camera() {
        camera_run_once = true;
        tp_gameInfo.lock_camera = true;
    }

    void unlock_camera() {
        if (camera_run_once) {
            tp_gameInfo.lock_camera = false;
            camera_run_once = false;
        }
    }

    void hide_hud() {
        tp_draw.hud = 0xFFFF;
        hud_run_once = true;
    }

    void show_hud() {
        if (hud_run_once) {
            tp_draw.hud = 0x3F80;
            hud_run_once = false;
        }
    }
}