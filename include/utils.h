#pragma once

#include "controller.h"
#include "font.h"
#include "menu.h"
#include "cheats.h"
#include "save_injector.h"

extern bool loading_initiated;
extern bool trigger_menu_anim;

enum Caller {
        None,
        Gorge,
        SaveInjection,
        AreaReload,
        SaveTempFlags
};

namespace Utilities {
    void move_cursor(int& cursor, int LINES);
    void menu_anim(Font& font, int idx);
    void render_lines(Font& font, Line lines[], int cursor, int LINES);
    void render_lines_with_items(Font& font, Line lines[], int cursor, int LINES, Cheats::Cheat Items[]);
    void trigger_load();
}  // namespace Utilities