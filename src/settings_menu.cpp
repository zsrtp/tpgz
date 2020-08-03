#include "gcn_c/include/card.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "controller.h"
#include "menu.h"
#include "utils.h"
#include <stdio.h>
#include "log.h"
#define LINES 5

static Cursor cursor = {0,0};
bool g_drop_shadows = true;
bool init_once = false;
bool settings_visible;
int g_area_reload_behavior;

Line lines[LINES] = {
    {"log level:", LOG_LEVEL_INDEX, "Changes log level for debugging", false, nullptr, true, {"NONE", "INFO", "DEBUG"}, &g_log_level},
    {"drop shadows", DROP_SHADOWS_INDEX, "Adds shadows to all font letters", true, &g_drop_shadows},
    {"save card", SAVE_CARD_INDEX, "Save settings to memory card"},
    {"load card", LOAD_CARD_INDEX, "Load settings from memory card"},
    {"area reload behavior:",AREA_RELOAD_BEHAVIOR_INDEX,"load area = Reload last area; load file = Reload last file", false, nullptr, true, {"load area","load file"}, &g_area_reload_behavior}};

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

    Utilities::move_cursor(cursor, LINES);

    if (current_input == 256 && a_held == false) {
        switch (cursor.x) {
            case LOG_LEVEL_INDEX: {
                if (g_log_level < 2) {
                    g_log_level++;
                    break;
                } else {
                    g_log_level = 0;
                    break;
                }
            }
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
            case AREA_RELOAD_BEHAVIOR_INDEX: {
                if (g_area_reload_behavior == LOAD_AREA) {
                    g_area_reload_behavior = LOAD_FILE;
                    break;
                } else {
                    g_area_reload_behavior = LOAD_AREA;
                    break;
                }
            }
        }
    }

    Utilities::render_lines(font, lines, cursor.x, LINES, 130.0f);
};