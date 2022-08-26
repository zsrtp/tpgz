#include "menus/menu_flags/include/flags_menu.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC FlagsMenu::FlagsMenu(Cursor& cursor)
    : Menu(),
      m_cursor(cursor), lines{
                            {"general flags", GENERAL_FLAGS_INDEX, "General flags", false},
                            {"dungeon flags", DUNGEON_FLAGS_INDEX, "Dungeon flags", false},
                            {"portal flags", PORTAL_FLAGS_INDEX, "Warp portal flags", false},
                            {"flag records", FLAG_RECORDS_INDEX, "Edit flag records", false},
                            {"flag log", FLAG_LOG_INDEX, "Toggle the flag log", false},
                        } {}

FlagsMenu::~FlagsMenu() {}

void FlagsMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (m_cursor.y) {
        case GENERAL_FLAGS_INDEX:
            g_menuMgr->push(MN_GENERAL_FLAGS_INDEX);
            return;
        case DUNGEON_FLAGS_INDEX:
            g_menuMgr->push(MN_DUNGEON_FLAGS_INDEX);
            return;
        case PORTAL_FLAGS_INDEX:
            g_menuMgr->push(MN_PORTAL_FLAGS_INDEX);
            return;
        case FLAG_RECORDS_INDEX:
            g_menuMgr->push(MN_FLAG_RECORDS_INDEX);
            return;
        case FLAG_LOG_INDEX:
            g_menuMgr->push(MN_FLAG_LOG_INDEX);
            return;
        }
    }

    m_cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, m_cursor.y, MENU_LINE_NUM);
}
