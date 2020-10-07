#include "gcn_c/include/card.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "controller.h"
#include "menus/settings_menu.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "utils/card.hpp"
#include <stdio.h>
#include "fifo_queue.h"

#define LINES 6
#define MAX_RELOAD_OPTIONS 2
#define MAX_CURSOR_COLOR_OPTIONS 6

static Cursor cursor = {0, 0};
bool g_drop_shadows = true;
bool init_once = false;
int g_area_reload_behavior;
int g_cursor_color;
bool g_cursor_color_flag;

Line lines[LINES] = {
    {"", AREA_RELOAD_BEHAVIOR_INDEX, "load area = Reload last area; load file = Reload last file", false, nullptr, MAX_RELOAD_OPTIONS},
    {"cursor color:", CURSOR_COLOR_INDEX, "Change cursor color", false, nullptr, MAX_CURSOR_COLOR_OPTIONS},
    {"drop shadows", DROP_SHADOWS_INDEX, "Adds shadows to all font letters", true, &g_drop_shadows},
    {"save card", SAVE_CARD_INDEX, "Save settings to memory card"},
    {"load card", LOAD_CARD_INDEX, "Load settings from memory card"},
    {"menu positions", POS_SETTINGS_MENU_INDEX, "Change menu object positions (A to toggle selection, DPad to move)", false}};

void SettingsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
		MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    //Utilities::move_cursor(cursor, LINES, 2);

    if (current_input == 256 && a_held == false) {
        switch (cursor.y) {
            case DROP_SHADOWS_INDEX: {
                g_drop_shadows = !g_drop_shadows;
                break;
            };
            case POS_SETTINGS_MENU_INDEX: {
		        MenuRendering::set_menu(MN_POS_SETTINGS_INDEX);
                return;
            };
            case SAVE_CARD_INDEX: {
                static Card card;
                card.file_name = "tpgz01";
                card.sector_size = SECTOR_SIZE;
                sprintf(card.file_name_buffer, card.file_name);
                card.card_result = CARDProbeEx(0, nullptr, &card.sector_size);
                if (card.card_result == Ready) {
                    Utilities::store_mem_card(card);
                }
                break;
            };
            case LOAD_CARD_INDEX: {
                static Card card;
                card.file_name = "tpgz01";
                card.sector_size = SECTOR_SIZE;
                sprintf(card.file_name_buffer, card.file_name);
                card.card_result = CARDProbeEx(0, NULL, &card.sector_size);
                Utilities::load_mem_card(card);
                break;
            }
        }
    }

    ListMember reload_options[MAX_RELOAD_OPTIONS] = {
        "load area",
        "load file"};

    ListMember cursor_color_options[MAX_CURSOR_COLOR_OPTIONS] = {
        "green",
        "blue",
        "red",
        "orange",
        "yellow",
        "purple"};

    // handle list rendering
    switch (cursor.y) {
        case AREA_RELOAD_BEHAVIOR_INDEX: {
            cursor.x = g_area_reload_behavior;
            Utilities::move_cursor(cursor, LINES, MAX_RELOAD_OPTIONS);
            if (cursor.y == AREA_RELOAD_BEHAVIOR_INDEX) {
                g_area_reload_behavior = cursor.x;
            }
            break;
        }

        case CURSOR_COLOR_INDEX: {
            cursor.x = g_cursor_color;
            Utilities::move_cursor(cursor, LINES, MAX_CURSOR_COLOR_OPTIONS);
            if (cursor.y == CURSOR_COLOR_INDEX) {
                g_cursor_color = cursor.x;
            }
            break;
        }
        default: {
            Utilities::move_cursor(cursor, LINES, 2);
            break;
        }
    }
    sprintf(lines[AREA_RELOAD_BEHAVIOR_INDEX].line, "area reload behavior: <%s>", reload_options[g_area_reload_behavior].member);
    sprintf(lines[CURSOR_COLOR_INDEX].line, "cursor color:         <%s>", cursor_color_options[g_cursor_color].member);

    Utilities::render_lines(font, lines, cursor.y, LINES, 210.0f);
};