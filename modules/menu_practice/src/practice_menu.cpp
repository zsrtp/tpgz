#include "menu_practice/include/practice_menu.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC PracticeMenu::PracticeMenu(Cursor& cursor)
    : Menu(), m_cursor(cursor), lines{
                  {"any%", ANY_INDEX, "Any% practice saves", false},
                  {"100%", HUNDO_INDEX, "100% practice saves", false},
                  {"all dungeons", AD_INDEX, "All Dungeons practice saves", false},
              } {}

PracticeMenu::~PracticeMenu() {}

void PracticeMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (m_cursor.y) {
        case ANY_INDEX:
            g_menuMgr->push(MN_ANY_SAVES_INDEX);
            return;
        case HUNDO_INDEX:
            g_menuMgr->push(MN_HUNDO_SAVES_INDEX);
            return;
        case AD_INDEX:
            g_menuMgr->push(MN_AD_SAVES_INDEX);
            return;
        }
    }

    m_cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, m_cursor.y, MENU_LINE_NUM);
}
