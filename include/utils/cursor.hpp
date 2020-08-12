#pragma once

struct Cursor {
    int y = 0;
    int x = 0;
};
extern bool can_move_cursor;

namespace Utilities {
    void move_cursor(Cursor& cursor, int max_cursor_x_value, int max_cursor_y_value = 0);
}