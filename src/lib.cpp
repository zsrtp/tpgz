#include "controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"

static bool visible = false;

void render() {
    if (Controller::B.is_pressed()) {
        visible = false;
        tp_osReport("Goodbye!");
        return;
    }
    tp_osReport("Hello!");
}

extern "C" void game_loop() {
    bool rt_down = Controller::R.is_down();
    bool lt_down = Controller::L.is_down();
    bool d_down = Controller::DPAD_DOWN.is_down();

    if (visible) {
        render();
    } else if (rt_down && d_down && lt_down && !visible) {
        visible = true;
    } else {
        //something
    }
}