#pragma once
#include "font.h"
#include "menu.h"
#define MAX_RENDER_LINES 15

namespace Utilities {
    void menu_anim(int idx);
    void render_lines(Line lines[], int cursor, int LINES);
    void change_cursor_color();
}  // namespace Utilities