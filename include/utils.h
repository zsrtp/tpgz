#pragma once

#include "controller.h"
#include "font.h"
#include "menu.h"
#include "cheats.h"
#include "save_injector.h"

namespace Utilities {
    void move_cursor(int& cursor, int LINES);
    void menu_anim(Font& font, int idx);
    void render_lines(Font& font, Line lines[], int cursor, int LINES);
    void trigger_load();
    void change_tunic_color();
}  // namespace Utilities