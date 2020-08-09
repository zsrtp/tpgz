#include "font.h"
#include "menu.h"
#include "controller.h"
#include "save_injector.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"

#define LINES 2

static Cursor cursor = {0,0};
bool init_once = false;
bool prac_visible;
PracticeFile practice_file;

Line lines[LINES] = {
	{"any%", ANY_INDEX, "Any% practice saves", false},
	{"100%", HUNDO_INDEX, "100% practice saves", false}};

void PracticeMenu::render(Font& font) {

    if (button_is_pressed(Controller::B)) {
        init_once = false;
        prac_visible = false;
        mm_visible = true;
        return;
    };

	if (!init_once) {current_input = 0;init_once = true;}

	if (current_input == 256 && a_held == false) {
		switch (cursor.y) {
			case ANY_INDEX: {
				prac_visible = false;
				any_saves_visible = true;
				return;
			}
			case HUNDO_INDEX: {
				prac_visible = false;
				hundo_saves_visible = true;
				return;
			}
		}
	}

	Utilities::move_cursor(cursor, LINES);

	Utilities::render_lines(font, lines, cursor.y, LINES);
};
