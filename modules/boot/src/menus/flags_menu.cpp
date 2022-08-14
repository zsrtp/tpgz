#include "menus/flags_menu.h"
#include "gz_flags.h"

bool g_flagLogEnabled;

FlagsMenu::FlagsMenu()
    : Menu(), lines{
                  {"general flags", GENERAL_FLAGS_INDEX, "General flags", false},
                  {"dungeon flags", DUNGEON_FLAGS_INDEX, "Dungeon flags", false},
                  {"portal flags", PORTAL_FLAGS_INDEX, "Warp portal flags", false},
                  {"flag records", FLAG_RECORDS_INDEX, "Edit flag records", false},
                  {"flag log", FLAG_LOG_INDEX, "Toggle the flag log", false},
              } {}

void FlagsMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case GENERAL_FLAGS_INDEX:
            GZ_setMenu(GZ_GEN_FLAGS_MENU);
            return;
        case DUNGEON_FLAGS_INDEX:
            GZ_setMenu(GZ_DUN_FLAGS_MENU);
            return;
        case PORTAL_FLAGS_INDEX:
            GZ_setMenu(GZ_PORTAL_FLAGS_MENU);
            return;
        case FLAG_RECORDS_INDEX:
            GZ_setMenu(GZ_FLAG_RECORD_MENU);
            return;
        case FLAG_LOG_INDEX:
            GZ_setMenu(GZ_FLAG_LOG_MENU);
            return;
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
