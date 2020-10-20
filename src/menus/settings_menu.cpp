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

#define LINES 7
#define MAX_RELOAD_OPTIONS 2
#define MAX_CURSOR_COLOR_OPTIONS 6
#define MAX_FONT_OPTIONS 6

static Cursor cursor = {0, 0};
bool g_drop_shadows = true;
bool init_once = false;
int g_area_reload_behavior;
int g_cursor_color;
bool g_cursor_color_flag;
int g_font;
bool font_init = false;

Line lines[LINES] = {
    {"", AREA_RELOAD_BEHAVIOR_INDEX, "load area = Reload last area; load file = Reload last file", false, nullptr, MAX_RELOAD_OPTIONS},
    {"cursor color:", CURSOR_COLOR_INDEX, "Change cursor color", false, nullptr, MAX_CURSOR_COLOR_OPTIONS},
    {"font:", FONT_INDEX, "Change font", false, nullptr, MAX_FONT_OPTIONS},
    {"drop shadows", DROP_SHADOWS_INDEX, "Adds shadows to all font letters", true, &g_drop_shadows},
    {"save card", SAVE_CARD_INDEX, "Save settings to memory card"},
    {"load card", LOAD_CARD_INDEX, "Load settings from memory card"},
    {"menu positions", POS_SETTINGS_MENU_INDEX, "Change menu object positions (A to toggle selection, DPad to move)", false}};

void SettingsMenu::render() {
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

    if (current_input == Controller::Pad::A && a_held == false) {
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

    ListMember font_options[MAX_FONT_OPTIONS] = {
        "consola",
        "calamity-bold",
        "lib-sans",
        "lib-sans-bold",
        "lib-serif",
        "lib-serif-bold"
    };

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

        case FONT_INDEX: {
            cursor.x = g_font;
            Utilities::move_cursor(cursor, LINES, MAX_FONT_OPTIONS);
            if (cursor.y == FONT_INDEX) {
                g_font = cursor.x;
            }
            if (button_is_pressed(Controller::DPAD_RIGHT) || button_is_pressed(Controller::DPAD_LEFT)) {
                font_init = false;
            }
            break;
        }

        default: {
            Utilities::move_cursor(cursor, LINES, 2);
            break;
        }
    }

    switch (g_font) {
        case 0: {
            if(!font_init){
                Font::load_font("tpgz/fonts/consola.fnt");
                font_init = true;
            }
            break;
        }
        case 1: {
            if(!font_init){
                Font::load_font("tpgz/fonts/calamity-bold.fnt");
                font_init = true;
            }
            break;
        }
        case 2: {
            if(!font_init){
                Font::load_font("tpgz/fonts/lib-sans.fnt");
                font_init = true;
            }
            break;
        }
        case 3: {
            if(!font_init){
                Font::load_font("tpgz/fonts/lib-sans-bold.fnt");
                font_init = true;
            }
            break;
        }
        case 4: {
            if(!font_init){
                Font::load_font("tpgz/fonts/lib-serif.fnt");
                font_init = true;
            }
            break;
        }
        case 5: {
            if(!font_init){
                Font::load_font("tpgz/fonts/lib-serif-bold.fnt");
                font_init = true;
            }
            break;
        }
    }
    sprintf(lines[AREA_RELOAD_BEHAVIOR_INDEX].line, "area reload behavior: <%s>", reload_options[g_area_reload_behavior].member);
    sprintf(lines[CURSOR_COLOR_INDEX].line, "cursor color:         <%s>", cursor_color_options[g_cursor_color].member);
    sprintf(lines[FONT_INDEX].line, "font:                 <%s>", font_options[g_font].member);

    Utilities::render_lines(lines, cursor.y, LINES, 210.0f);
}

void SettingsMenu::initFont(){
    switch (g_font) {
        case 0: {
            Font::load_font("tpgz/fonts/consola.fnt");
            break;
        }
        case 1: {
            Font::load_font("tpgz/fonts/calamity-bold.fnt");
            break;
        }
        case 2: {
            Font::load_font("tpgz/fonts/lib-sans.fnt");
            break;
        }
        case 3: {
            Font::load_font("tpgz/fonts/lib-sans-bold.fnt");
            break;
        }
        case 4: {
            Font::load_font("tpgz/fonts/lib-serif.fnt");
            break;
        }
        case 5: {
            Font::load_font("tpgz/fonts/lib-serif-bold.fnt");
            break;
        }
    }
}