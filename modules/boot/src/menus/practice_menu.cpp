#include "menus/practice_menu.h"
#include "gz_flags.h"

PracticeMenu::PracticeMenu()
    : Menu(), lines{
                  {"any%", ANY_INDEX, "Any% practice saves", false},
                  {"100%", HUNDO_INDEX, "100% practice saves", false},
                  {"all dungeons", AD_INDEX, "All Dungeons practice saves", false},
              } {}

char last_category[5];
int last_save_index;
int last_special_size;
special* last_special_ptr;

void PracticeMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case ANY_INDEX:
            GZ_setMenu(GZ_ANY_SAVES_MENU);
            return;
        case HUNDO_INDEX:
            GZ_setMenu(GZ_HUNDO_SAVES_MENU);
            return;
        case AD_INDEX:
            GZ_setMenu(GZ_AD_SAVES_MENU);
            return;
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
