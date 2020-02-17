#include "controller.h"

void move_cursor(int len, int cursor) {
    //let state = unsafe { super::get_state() };
    //let lines = state.menu.lines_mut();

    if (button_is_down(Controller::DPAD_DOWN) && cursor > 0) {
        cursor -= 1;
        // while lines[*cursor].len() < 3 {
        //     *cursor -= 1;
        // }
    } else if (button_is_down(Controller::DPAD_DOWN) && cursor + 1 < len) {
        cursor += 1;
        // while lines[*cursor].len() < 3 {
        //     *cursor += 1;
        // }
    }
}