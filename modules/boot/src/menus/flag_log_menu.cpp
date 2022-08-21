#include "menus/flags_menu.h"
#include "flaglog.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC FlagLogMenu::FlagLogMenu()
    : Menu(), lines{{"log activated", 0, "toggle flag logger on/off", true, &g_flagLogEnabled}} {}

void FlagLogMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case 0:
            g_flagLogEnabled = !g_flagLogEnabled;
            return;
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}