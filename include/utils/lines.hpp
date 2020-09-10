#pragma once
#include "font.h"
#include "menu.h"

namespace Utilities {
    void menu_anim(Font& font, int idx);
    void render_lines(Font& font, Line lines[], int cursor, int LINES, float menu_toggle_switch_x_offset = 200.0f);
	void change_cursor_color();
}  // namespace Utilities