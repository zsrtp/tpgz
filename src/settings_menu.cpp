#include "gcn_c/include/card.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "controller.h"
#include "menu.h"
#include "utils.h"
#include <stdio.h>
#include "log.h"
#define LINES 6

static int cursor = 2;
bool g_reset_temp_flags;
bool g_drop_shadows = true;
bool init_once = false;
bool settings_visible;

Line lines[LINES] = {
    {"settings", 0, "", false},
    {"", 1, "", false},
    {"log level:", LOG_LEVEL_INDEX, "changes log level for debugging", false, nullptr, true, {"NONE", "INFO", "DEBUG"}, &g_log_level},
    {"drop shadows", DROP_SHADOWS_INDEX, "adds shadows to all font letters", true, &g_drop_shadows},
    {"save card", SAVE_CARD, "save settings to memory card"},
    {"load card", LOAD_CARD, "load settings from memory card"}};

void SettingsMenu::render(Font& font) {
    static SaveLayout save_layout;
    static MemCard::Card card;
    card.file_name = "tpgz01";

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
        switch (cursor) {
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
            case SAVE_CARD: {
                memcpy(save_layout.CheatItems, CheatItems, sizeof(CheatItems));
                memcpy(save_layout.ToolItems, ToolItems, sizeof(ToolItems));
                card.sector_size = SECTOR_SIZE;
                sprintf(card.file_name_buffer, card.file_name);

                card.card_result = CARDProbeEx(0, NULL, &card.sector_size);
                if (card.card_result == Ready) {
                    card.card_result = CARDCreate(0, card.file_name_buffer, card.sector_size, &card.card_info);
                    if (card.card_result == Ready || card.card_result == Exist) {
                        card.card_result = CARDOpen(0, card.file_name_buffer, &card.card_info);
                        if (card.card_result == Ready) {
                            card.card_result = CARDWrite(&card.card_info, &save_layout, 0, 0);
                            if (card.card_result == Ready) {
                                tp_osReport("saved card!");
                            } else {
                                tp_osReport("failed to save");
                            }
                            card.card_result = CARDClose(&card.card_info);
                        }
                    }
                }
                break;
            };
            case LOAD_CARD: {
                tp_osReport("0x%02X", &save_layout);
                sprintf(card.file_name_buffer, card.file_name);
                card.card_result = CARDOpen(0, card.file_name_buffer, &card.card_info);
                if (card.card_result == Ready) {
                    card.card_result = CARDRead(&card.card_info, &save_layout, 512, 0x0000);
                    if (card.card_result == Ready) {
                        tp_osReport("loaded card!");
                        memcpy(CheatItems,save_layout.CheatItems,sizeof(save_layout.CheatItems));
                        memcpy(ToolItems,save_layout.ToolItems,sizeof(save_layout.ToolItems));
                    } else {
                        tp_osReport("failed to load");
                    }
                    card.card_result = CARDClose(&card.card_info);
                }
                break;
            }
        }
    }
    Utilities::render_lines(font, lines, cursor, LINES);
};