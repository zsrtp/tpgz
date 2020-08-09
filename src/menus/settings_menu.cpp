#include "gcn_c/include/card.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "controller.h"
#include "menu.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <stdio.h>
#include "log.h"
#define LINES 5
#define MAX_RELOAD_OPTIONS 2
#define MAX_LOG_LEVEL_OPTIONS 3

static Cursor cursor = {0, 0};
bool g_drop_shadows = true;
bool init_once = false;
bool settings_visible;
static uint8_t reload_behavior_index = 0;
static uint8_t log_level_index = 0;
int g_area_reload_behavior;

Line lines[LINES] = {
    {"log level:", LOG_LEVEL_INDEX, "Changes log level for debugging", false, nullptr, MAX_LOG_LEVEL_OPTIONS},
    {"drop shadows", DROP_SHADOWS_INDEX, "Adds shadows to all font letters", true, &g_drop_shadows},
    {"save card", SAVE_CARD_INDEX, "Save settings to memory card"},
    {"load card", LOAD_CARD_INDEX, "Load settings from memory card"},
    {"", AREA_RELOAD_BEHAVIOR_INDEX, "load area = Reload last area; load file = Reload last file", false, nullptr, MAX_RELOAD_OPTIONS}};

// Log log;
void SettingsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        settings_visible = false;
        mm_visible = true;
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
                // case SAVE_CARD_INDEX: {
                //     static SaveLayout save_layout;
                //     static MemCard::Card card;
                //     card.file_name = "tpgz01";
                //     card.sector_size = SECTOR_SIZE;
                //     sprintf(card.file_name_buffer, card.file_name);

                //     memcpy(save_layout.CheatItems, CheatItems, sizeof(CheatItems));
                //     memcpy(save_layout.ToolItems, ToolItems, sizeof(ToolItems));

                //     card.card_result = CARDProbeEx(0, nullptr, &card.sector_size);
                //     if (card.card_result == Ready) {
                //         card.card_result = CARDCreate(0, card.file_name_buffer, card.sector_size, &card.card_info);
                //         if (card.card_result == Ready || card.card_result == Exist) {
                //             card.card_result = CARDOpen(0, card.file_name_buffer, &card.card_info);
                //             if (card.card_result == Ready) {
                //                 card.card_result = CARDWrite(&card.card_info, &save_layout, 0, 0);
                //                 if (card.card_result == Ready) {
                //                     // log.PrintLog("saved card!", DEBUG);
                //                     tp_osReport("saved card!");
                //                 } else {
                //                     // log.PrintLog("failed to save!", DEBUG);
                //                     tp_osReport("failed to save");
                //                 }
                //                 card.card_result = CARDClose(&card.card_info);
                //             }
                //         }
                //     }
                //     break;
                // };
                // case LOAD_CARD_INDEX: {
                //     static SaveLayout save_layout;
                //     static MemCard::Card card;
                //     card.file_name = "tpgz01";
                //     sprintf(card.file_name_buffer, card.file_name);
                //     Utilities::load_mem_card(card,save_layout);
                //     break;
                // }
        }
    }

    ListMember reload_options[MAX_RELOAD_OPTIONS] = {
        "load area",
        "load file"};

    ListMember log_level_options[MAX_LOG_LEVEL_OPTIONS] = {
        "none",
        "info",
        "debug"};

    // handle list rendering
    switch (cursor.y) {
        case AREA_RELOAD_BEHAVIOR_INDEX: {
            cursor.x = reload_behavior_index;
            Utilities::move_cursor(cursor, LINES, MAX_RELOAD_OPTIONS);
            if (cursor.y == AREA_RELOAD_BEHAVIOR_INDEX) {
                reload_behavior_index = cursor.x;
            }
            g_area_reload_behavior = reload_behavior_index;
            break;
        }
        case LOG_LEVEL_INDEX: {
            cursor.x = log_level_index;
            Utilities::move_cursor(cursor, LINES, MAX_LOG_LEVEL_OPTIONS);
            if (cursor.y == LOG_LEVEL_INDEX) {
                log_level_index = cursor.x;
            }
            g_log_level = log_level_index;
            break;
        }
        default: {
            Utilities::move_cursor(cursor, LINES, 2);
            break;
        }
    }
    sprintf(lines[AREA_RELOAD_BEHAVIOR_INDEX].line, "area reload behavior: <%s>", reload_options[reload_behavior_index].member);
    sprintf(lines[LOG_LEVEL_INDEX].line, "log level: <%s>", log_level_options[log_level_index].member);

    Utilities::render_lines(font, lines, cursor.y, LINES, 130.0f);
};