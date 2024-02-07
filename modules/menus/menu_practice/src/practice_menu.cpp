#include "menus/menu_practice/include/practice_menu.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC PracticeMenu::PracticeMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"any%", ANY_INDEX, "Any% practice saves", false},
#ifdef GCN_PLATFORM
                        {"any% BiTE", ANY_BITE_INDEX, "Any% (BiTE route) practice saves", false},
#endif
                        {"100%", HUNDO_INDEX, "100% practice saves", false},
                        {"all dungeons", AD_INDEX, "All Dungeons practice saves", false},
#ifdef GCN_PLATFORM
                        {"no save-quit", NOSQ_INDEX, "No Save-Quit practive saves", false},
#endif
                        {"glitchless", GLITCHLESS_INDEX, "Glitchless practice saves", false},
                    } {}

PracticeMenu::~PracticeMenu() {}

void PracticeMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case ANY_INDEX:
            g_menuMgr->push(MN_ANY_SAVES_INDEX);
            return;
#ifdef GCN_PLATFORM
        case ANY_BITE_INDEX:
            g_menuMgr->push(MN_ANY_BITE_SAVES_INDEX);
            return;
#endif
        case HUNDO_INDEX:
            g_menuMgr->push(MN_HUNDO_SAVES_INDEX);
            return;
        case AD_INDEX:
            g_menuMgr->push(MN_AD_SAVES_INDEX);
            return;
#ifdef GCN_PLATFORM
        case NOSQ_INDEX:
            g_menuMgr->push(MN_NOSQ_SAVES_INDEX);
            return;
#endif
        case GLITCHLESS_INDEX:
            g_menuMgr->push(MN_GLITCHLESS_SAVES_INDEX);
            return;
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
