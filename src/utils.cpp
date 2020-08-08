#include "utils.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "gcn_c/include/card.h"
#include "controller.h"
#include "save_injector.h"
#include "commands.h"
#include "gorge.h"
#include "log.h"
#include "fs.h"
#include "menu.h"
#include "font.h"

bool loading_initiated = false;
int apply_after_counter = 0;
uint8_t red;
uint8_t green;
uint8_t blue;

namespace Utilities {
    static Log log;

    void show_link_debug_info(Font &font) {
#define LINK_DEBUG_X_OFFSET 450.0f
#define LINK_DEBUG_Y_OFFSET 200.0f

        if (tp_zelAudio.link_debug_ptr) {
            char link_angle[20];
            //char vspeed[4];
            char link_speed[20];
            char link_x[20];
            char link_y[20];
            char link_z[20];

            sprintf(link_angle, "angle: %d", tp_zelAudio.link_debug_ptr->facing);
            sprintf(link_speed, "speed: %.4f", tp_zelAudio.link_debug_ptr->speed);
            sprintf(link_x, "x-pos: %.4f", tp_zelAudio.link_debug_ptr->position.x);
            sprintf(link_y, "y-pos: %.4f", tp_zelAudio.link_debug_ptr->position.y);
            sprintf(link_z, "z-pos: %.4f", tp_zelAudio.link_debug_ptr->position.z);

            font.gz_renderChars(link_angle, LINK_DEBUG_X_OFFSET, LINK_DEBUG_Y_OFFSET, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars(link_speed, LINK_DEBUG_X_OFFSET, LINK_DEBUG_Y_OFFSET + 20.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars(link_x, LINK_DEBUG_X_OFFSET, LINK_DEBUG_Y_OFFSET + 40.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars(link_y, LINK_DEBUG_X_OFFSET, LINK_DEBUG_Y_OFFSET + 60.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars(link_z, LINK_DEBUG_X_OFFSET, LINK_DEBUG_Y_OFFSET + 80.0f, 0xFFFFFFFF, g_drop_shadows);
        } else {
            font.gz_renderChars("angle: n/a", LINK_DEBUG_X_OFFSET, LINK_DEBUG_Y_OFFSET, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars("speed: n/a", LINK_DEBUG_X_OFFSET, LINK_DEBUG_Y_OFFSET + 20.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars("x-pos: n/a", LINK_DEBUG_X_OFFSET, LINK_DEBUG_Y_OFFSET + 40.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars("y-pos: n/a", LINK_DEBUG_X_OFFSET, LINK_DEBUG_Y_OFFSET + 60.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars("z-pos: n/a", LINK_DEBUG_X_OFFSET, LINK_DEBUG_Y_OFFSET + 80.0f, 0xFFFFFFFF, g_drop_shadows);
        }
    }

    void move_cursor(Cursor &cursor, int max_cursor_x_value) {
        if (!can_move_cursor) {
            return;
        }
        if (button_is_pressed(Controller::DPAD_UP)) {
            if (cursor.x > 0) {
                cursor.x -= 1;
            } else {
                cursor.x = max_cursor_x_value - 1;
            }
        }
        if (button_is_pressed(Controller::DPAD_DOWN)) {
            if (cursor.x < max_cursor_x_value - 1) {
                cursor.x += 1;
            } else {
                cursor.x = 0;
            }
        }
    }

    void move_cursor(Cursor &cursor, int max_cursor_x_value, int max_cursor_y_value) {
        if (!can_move_cursor) {
            return;
        }
        if (button_is_pressed(Controller::DPAD_UP)) {
            if (cursor.x > 0) {
                cursor.x -= 1;
            } else {
                cursor.x = max_cursor_x_value - 1;
            }
        }
        if (button_is_pressed(Controller::DPAD_DOWN)) {
            if (cursor.x < max_cursor_x_value - 1) {
                cursor.x += 1;
            } else {
                cursor.x = 0;
            }
        }
        if (button_is_pressed(Controller::DPAD_RIGHT)) {
            if (cursor.y < max_cursor_y_value - 1) {
                cursor.y += 1;
            } else {
                cursor.y = 0;
            }
        }
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            if (cursor.y > 0) {
                cursor.y -= 1;
            } else {
                cursor.y = max_cursor_y_value - 1;
            }
        }
    }

    void render_lines(Font &font, Line input_lines[], int cursor, int LINES, float menu_toggle_switch_x_offset) {
        font.gz_renderChars("tpgz v0.1a", 25.0f, 25.0f, 0x00CC00FF, g_drop_shadows);
        float offset = 0.0f;
        for (int i = 0; i < LINES; i++) {
            // don't draw past line 15/cursor
            if (LINES > 15 && i > 15 && cursor < i) {
                if (i == LINES - 1 && cursor < LINES) {
                    font.gz_renderChars("______", 25.0f, 380.0f, 0xFFFFFF80, g_drop_shadows);
                }
                continue;
            };

            // initiate scroll
            if (cursor > 15) {
                if (i < (cursor - 15)) {
                    continue;
                } else {
                    offset = (60.0f + (i - (cursor - 15)) * 20.0f);
                }
            }
            // normal line rendering offset
            else {
                offset = (60.0f + (i * 20.0f));
            }

            int cursor_color = 0x00CC00FF;
            int description_color = 0xFFFFFF00;
            int description_alpha = 0xFF;

            // fade line/hide descriptions for lines the cursor isn't on
            if (input_lines[i].idx != cursor) {
                cursor_color = 0xFFFFFFFF;
                description_alpha = 0x00;
            }
            description_color |= description_alpha;

            // logic for lines that are toggleable
            if (input_lines[i].toggleable) {
                if (*input_lines[i].activation_flag) {
                    font.gz_renderChars(" [X]", menu_toggle_switch_x_offset, offset, cursor_color, g_drop_shadows);
                } else {
                    font.gz_renderChars(" [ ]", menu_toggle_switch_x_offset, offset, cursor_color, g_drop_shadows);
                }

                font.gz_renderChars(input_lines[i].line, 25.0f, offset, cursor_color, g_drop_shadows);
            }
            // logic for lines that are lists
            else if (input_lines[i].is_list) {
                // need to simplify this logic
                char final_line[50];
                char list_line[MAX_LIST_MEMBER_LENGTH];
                sprintf(list_line, input_lines[i].list_member[*input_lines[i].list_member_idx].member);
                sprintf(final_line, input_lines[i].line);
                strcat(final_line, " ");
                strcat(final_line, list_line);
                font.gz_renderChars(final_line, 25.0f, offset, cursor_color, g_drop_shadows);
            }
            // logic for normal lines
            else {
                font.gz_renderChars(input_lines[i].line, 25.0f, offset, cursor_color, g_drop_shadows);
            }

            // render line descriptions
            font.gz_renderChars(input_lines[i].description, 25.0f, 440.f, description_color, false);
        };
    }

    void trigger_load() {
        if (tp_fopScnRq.isLoading == 0 && !loading_initiated) {
            log.PrintLog("Initiating warp", INFO);
            if (practice_file.inject_options_before_load) {
                practice_file.inject_options_before_load();
            }
            tp_gameInfo.warp.enabled = true;
        }

        if (tp_fopScnRq.isLoading == 1) {
            if (practice_file.inject_options_during_load) {
                practice_file.inject_options_during_load();
            }
            loading_initiated = true;
        }

        if (loading_initiated == true) {
            if (tp_fopScnRq.isLoading == 0) {
                if (practice_file.inject_options_after_load) {
                    practice_file.inject_options_after_load();
                }
                if (practice_file.inject_options_after_counter == apply_after_counter) {
                    apply_after_counter = 0;
                    practice_file.inject_options_after_counter = 0;
                    loading_initiated = false;
                    inject_save_flag = false;
                } else {
                    apply_after_counter++;
                }
            }
        }
    }

    void change_tunic_color() {
        // patch out part of setWaterDropEffect's code
        memset((void *)0x801244a4, 0x60, 1);
        memset((void *)0x801244a5, 0x00, 3);
        memset((void *)0x801244a8, 0x60, 1);
        memset((void *)0x801244a9, 0x00, 3);
        memset((void *)0x801244ac, 0x60, 1);
        memset((void *)0x801244ad, 0x00, 3);

        if (tp_gameInfo.link_tunic_ptr) {
            switch (g_tunic_color) {
                case GREEN: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x00;
                    break;
                }
                case BLUE: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x20;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x80;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x20;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x80;
                    break;
                }
                case RED: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0x80;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0x80;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x00;
                    break;
                }
                case ORANGE: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0xDC;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x14;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0xDC;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x14;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x00;
                    break;
                }
                case YELLOW: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x00;
                    break;
                }
                case WHITE: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x30;
                    break;
                }
                case CYCLE: {
                    if (red < 0x0040 && (green == 0x0000 && blue == 0x0000)) {
                        red += 0x0002;
                    } else if (green < 0x0040 && (blue == 0x0000 && red == 0x0040)) {
                        green += 0x0002;
                    } else if (blue < 0x0040 && (green == 0x0040 && red == 0x0040)) {
                        blue += 0x0002;
                    } else if (red > 0x0000 && (green == 0x0040 && blue == 0x0040)) {
                        red -= 0x0002;
                    } else if (green > 0x0000 && (blue == 0x0040 && red == 0x0000)) {
                        green -= 0x0002;
                    } else {
                        blue -= 0x0002;
                    }
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = red;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = green;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = blue;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = red;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = green;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = blue;
                    break;
                }
            }
        }
    }

    void disable_bg_music() {
        tp_zelAudio.bg_audio = 0.0f;
        tp_zelAudio.enemy_bg_music_volume = 0.0f;
        tp_zelAudio.hyrule_castle_bg_music_volume = 0.0f;
    }

    void load_mem_card(MemCard::Card &card, SaveLayout &save_layout) {
        card.card_result = CARDOpen(0, card.file_name_buffer, &card.card_info);
        if (card.card_result == Ready) {
            card.card_result = CARDRead(&card.card_info, &save_layout, 512, 0x0000);
            if (card.card_result == Ready) {
                tp_osReport("loaded card!");
                memcpy(CheatItems, save_layout.CheatItems, sizeof(save_layout.CheatItems));
                memcpy(ToolItems, save_layout.ToolItems, sizeof(save_layout.ToolItems));
            } else {
                tp_osReport("failed to load");
            }
            card.card_result = CARDClose(&card.card_info);
        }
    }

    void enable_bg_music() {
        tp_zelAudio.bg_audio = 1.0f;
        tp_zelAudio.enemy_bg_music_volume = 1.0f;
        tp_zelAudio.hyrule_castle_bg_music_volume = 1.0f;
    }

    // void change_font(Font& font, const _Font& font_bytes, const char* font_texture_data ) {
    //     memset(&font._texobj, 0x0, sizeof(GXTexObj));
    //     GX_InitTexObj(&font._texobj, (void*)font_texture_data, font_bytes.width, font_bytes.height, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    //     font.font = &font_bytes;
    // }

    void disable_sfx() {
        tp_zelAudio.enemy_sfx_volume = 0.0f;
        tp_zelAudio.env_sfx_volume = 0.0f;
        tp_zelAudio.item_recoil_sfx_volume = 0.0f;
        tp_zelAudio.item_sfx_volume = 0.0f;
        tp_zelAudio.link_idle_sfx_volume = 0.0f;
        tp_zelAudio.link_voice_volume = 0.0f;
        tp_zelAudio.menu_sfx_volume = 0.0f;
        tp_zelAudio.midna_sfx_volume = 0.0f;
        tp_zelAudio.npc_volume = 0.0f;
        tp_zelAudio.pause_button_volume = 0.0f;
    }
    void enable_sfx() {
        tp_zelAudio.enemy_sfx_volume = 1.0f;
        tp_zelAudio.env_sfx_volume = 1.0f;
        tp_zelAudio.item_recoil_sfx_volume = 1.0f;
        tp_zelAudio.item_sfx_volume = 1.0f;
        tp_zelAudio.link_idle_sfx_volume = 1.0f;
        tp_zelAudio.link_voice_volume = 1.0f;
        tp_zelAudio.menu_sfx_volume = 1.0f;
        tp_zelAudio.midna_sfx_volume = 1.0f;
        tp_zelAudio.npc_volume = 1.0f;
        tp_zelAudio.pause_button_volume = 1.0f;
    }
    void load_gz_card(bool &card_load) {
        uint8_t frame_count = TP::get_frame_count();
        if (card_load && frame_count > 200) {
            static SaveLayout save_layout;
            static MemCard::Card card;
            card.file_name = "tpgz01";
            card.sector_size = SECTOR_SIZE;
            sprintf(card.file_name_buffer, card.file_name);
            card.card_result = CARDProbeEx(0, NULL, &card.sector_size);
            if (card.card_result == Ready) {
                Utilities::load_mem_card(card, save_layout);
                card_load = false;
            } else {
                card_load = false;
            }
        }
    }
}  // namespace Utilities

// temp -
// patch setWaterDropEffect back to it's original code
// memset((void *)0x801244a4, 0xB0, 1);
// memset((void *)0x801244a5, 0x03, 1);
// memset((void *)0x801244a6, 0x32, 1);
// memset((void *)0x801244a7, 0xA0, 1);
// memset((void *)0x801244a8, 0xB0, 1);
// memset((void *)0x801244a9, 0x03, 1);
// memset((void *)0x801244aa, 0x32, 1);
// memset((void *)0x801244ab, 0xA2, 1);
// memset((void *)0x801244ac, 0xB0, 1);
// memset((void *)0x801244ad, 0x03, 1);
// memset((void *)0x801244ae, 0x32, 1);
// memset((void *)0x801244af, 0xA4, 1);
