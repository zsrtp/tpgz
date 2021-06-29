#include "menus/settings_menu.h"
#include "controller.h"
#include "libtp_c/include/msl_c/string.h"
#include "utils/card.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#include "fifo_queue.h"

#define LINES 9
#define MAX_RELOAD_OPTIONS 2
#define MAX_CURSOR_COLOR_OPTIONS 6
#define MAX_FONT_OPTIONS 7

static Cursor cursor = {0, 0};
bool g_drop_shadows = true;
bool init_once = false;
int g_area_reload_behavior;
int g_cursor_color;
bool g_cursor_color_flag;
bool g_swap_equips_flag;
int g_font = 0;

ListMember reload_options[MAX_RELOAD_OPTIONS] = {"load area", "load file"};

ListMember cursor_color_options[MAX_CURSOR_COLOR_OPTIONS] = {"green",  "blue",   "red",
                                                             "orange", "yellow", "purple"};

ListMember font_options[MAX_FONT_OPTIONS] = {"consola",       "calamity-bold", "lib-sans",
                                             "lib-sans-bold", "lib-serif",     "lib-serif-bold",
                                             "press-start-2p"};

Line lines[LINES] = {
    {"area reload behavior:", AREA_RELOAD_BEHAVIOR_INDEX,
     "load area = Reload last area; load file = Reload last file", false, nullptr,
     MAX_RELOAD_OPTIONS},
    {"cursor color:", CURSOR_COLOR_INDEX, "Change cursor color", false, nullptr,
     MAX_CURSOR_COLOR_OPTIONS},
    {"font:", FONT_INDEX, "Change font", false, nullptr, MAX_FONT_OPTIONS},
    {"drop shadows", DROP_SHADOWS_INDEX, "Adds shadows to all font letters", true, &g_drop_shadows},
    {"swap equips", SWAP_EQUIPS_INDEX, "Swap equips when loading practice files", true,
     &g_swap_equips_flag},
    {"save card", SAVE_CARD_INDEX, "Save settings to memory card"},
    {"load card", LOAD_CARD_INDEX, "Load settings from memory card"},
    {"delete card", DELETE_CARD_INDEX, "Delete settings from memory card"},
    {"menu positions", POS_SETTINGS_MENU_INDEX,
     "Change menu object positions (A to toggle selection, DPad to move)", false}};

void SettingsMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        init_once = false;
        MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    // Utilities::move_cursor(cursor, LINES, 2);

    if (current_input == SELECTION_BUTTON && a_held == false) {
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
            static Storage storage;
            storage.file_name = "tpgz01";
            storage.sector_size = SECTOR_SIZE;
            tp_sprintf(storage.file_name_buffer, storage.file_name);
#ifndef WII_PLATFORM
            storage.result = CARDProbeEx(0, nullptr, &storage.sector_size);
            if (storage.result == Ready) {
                Utilities::store_mem_card(storage);
            }
#endif  // WII_PLATFORM
            Utilities::store_mem_card(storage);
            break;
        };
        case LOAD_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "tpgz01";
            storage.sector_size = SECTOR_SIZE;
            tp_sprintf(storage.file_name_buffer, storage.file_name);
#ifndef WII_PLATFORM
            storage.result = CARDProbeEx(0, NULL, &storage.sector_size);
            if (storage.result == Ready) {
                Utilities::load_mem_card(storage);
            }
#endif  // WII_PLATFORM
            Utilities::load_mem_card(storage);
            break;
        };
        case DELETE_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "tpgz01";
            storage.sector_size = SECTOR_SIZE;
            tp_sprintf(storage.file_name_buffer, storage.file_name);
#ifndef WII_PLATFORM
            storage.result = CARDProbeEx(0, nullptr, &storage.sector_size);
            if (storage.result == Ready) {
                Utilities::delete_mem_card(storage);
            }
#endif  // WII_PLATFORM
            Utilities::delete_mem_card(storage);
            break;
        };
        case SWAP_EQUIPS_INDEX: {
            g_swap_equips_flag = !g_swap_equips_flag;
            break;
        };
        }
    }

    // handle list rendering
    switch (cursor.y) {
    case AREA_RELOAD_BEHAVIOR_INDEX: {
        cursor.x = g_area_reload_behavior;
        Utilities::move_cursor(cursor, LINES, MAX_RELOAD_OPTIONS, false, false, false, true);
        if (cursor.y == AREA_RELOAD_BEHAVIOR_INDEX) {
            g_area_reload_behavior = cursor.x;
        }
        break;
    }

    case CURSOR_COLOR_INDEX: {
        cursor.x = g_cursor_color;
        Utilities::move_cursor(cursor, LINES, MAX_CURSOR_COLOR_OPTIONS, false, false, false, true);
        if (cursor.y == CURSOR_COLOR_INDEX) {
            g_cursor_color = cursor.x;
        }
        break;
    }

    case FONT_INDEX: {
        cursor.x = g_font;
        int old_font = g_font;
        Utilities::move_cursor(cursor, LINES, MAX_FONT_OPTIONS, false, false, false, true);
        if (cursor.y == FONT_INDEX) {
            g_font = cursor.x;
        }
        if (old_font != g_font) {
            if (g_font >= 0 && g_font < MAX_FONT_OPTIONS) {
                char buf[80];
                tp_sprintf(buf, "tpgz/fonts/%s.fnt", font_options[g_font].member);
                Font::load_font(buf);
            }
        }
        break;
    }

    default: {
        Utilities::move_cursor(cursor, LINES, 2, false, false, false, true);
        break;
    }
    }

    tp_sprintf(lines[AREA_RELOAD_BEHAVIOR_INDEX].value, " <%s>",
               reload_options[g_area_reload_behavior].member);
    tp_sprintf(lines[CURSOR_COLOR_INDEX].value, " <%s>",
               cursor_color_options[g_cursor_color].member);
    tp_sprintf(lines[FONT_INDEX].value, " <%s>", font_options[g_font].member);

    Utilities::render_lines(lines, cursor.y, LINES);
}

void SettingsMenu::initFont() {
    if (g_font >= 0 && g_font < MAX_FONT_OPTIONS) {
        char buf[80];
        tp_sprintf(buf, "tpgz/fonts/%s.fnt", font_options[g_font].member);
        Font::load_font(buf);
    }
}