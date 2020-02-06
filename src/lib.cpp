#include "controller.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"

static bool visible = false;

void render() {
    if (Controller::is_pressed(Controller::Pad::DPAD_DOWN)) {
        visible = false;
        tp_osReport("Goodbye!");
        return;
    }
}

extern "C" void game_loop() {
    bool a_down = button_is_pressed(Controller::A);
    bool z_down = button_is_down(Controller::Z);
    bool r_down = Controller::button_is_down(Controller::R);
    bool l_down = Controller::button_is_down(Controller::L);

    if (visible) {
        render();
    } else if (l_down && r_down && z_down && a_down) {
        visible = true;
    }
}