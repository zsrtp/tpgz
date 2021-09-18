#include "utils/cursor.h"
#include "controller.h"

namespace Utilities {
void move_cursor(Cursor& cursor, int max_cursor_y_value, int max_cursor_x_value, bool lock_x,
                 bool lock_y, bool unrestricted, bool menu_with_list_lines) {
    if (!can_move_cursor && !unrestricted) {
        return;
    }

    if (button_is_pressed(Controller::DPAD_UP) && !lock_y) {
        // reset so other lines aren't affected
        cursor.x = 0;
        cursor.y > 0 ? cursor.y-- : cursor.y = max_cursor_y_value - 1;
    }

    if (button_is_pressed(Controller::DPAD_DOWN) && !lock_y) {
        // reset so other lines aren't affected
        cursor.x = 0;
        cursor.y < max_cursor_y_value - 1 ? cursor.y++ : cursor.y = 0;
    }

    if (button_is_pressed(Controller::DPAD_RIGHT)) {
        // if y and x aren't locked, we must be on a single column menu
        if (!lock_y && !lock_x && !menu_with_list_lines) {
            cursor.y += 10;
            if (cursor.y > max_cursor_y_value - 1) {
                cursor.y = max_cursor_y_value - 1;
            }
        } else if (!lock_x) {
            cursor.x < max_cursor_x_value - 1 ? cursor.x++ : cursor.x = 0;
        }
    }

    if (button_is_pressed(Controller::DPAD_LEFT)) {
        // if y and x aren't locked, we must be on a single column menu
        if (!lock_x && !lock_y && !menu_with_list_lines) {
            cursor.y -= 10;
            if (cursor.y < 0) {
                cursor.y = 0;
            }
        } else if (!lock_x) {
            cursor.x > 0 ? cursor.x-- : cursor.x = max_cursor_x_value - 1;
        }
    }
}
}  // namespace Utilities
