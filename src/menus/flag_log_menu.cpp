#include "menus/flags_menu.h"
#include "flaglog.h"
#include "gz_flags.h"

#define LINE_NUM 1

Cursor FlagLogMenu::cursor;
bool g_flagLogEnabled = false;

Line lines[LINE_NUM] = {{"log activated", 0, "toggle flag logger on/off", true, &g_flagLogEnabled}};

void FlagLogMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(GZ_FLAGS_MENU);
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case 0:
            g_flagLogEnabled = !g_flagLogEnabled;
            return;
        }
    }

    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}