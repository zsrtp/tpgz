#include "utils.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "controller.h"
#include "save_injector.h"
#include "commands.h"
#include "gorge.h"
#include "log.h"
#include "fs.h"
#include "menu.h"

bool loading_initiated = false;
int apply_after_counter = 0;
uint8_t red;
uint8_t green;
uint8_t blue;

namespace Utilities {
    static Log log;

    void move_cursor(int &cursor, int LINES) {
        if (button_is_pressed(Controller::DPAD_DOWN)) {
            if (cursor < LINES - 1) {
                cursor++;
            } else if (cursor == LINES - 1) {
                cursor = 2;
            }
        };

        if (button_is_pressed(Controller::DPAD_UP)) {
            if (cursor > 2) {
                cursor--;
            } else if (cursor == 2) {
                cursor = LINES - 1;
            }
        };
    }

    void render_lines(Font &font, Line input_lines[], int cursor, int LINES) {
        font.renderChars("tpgz v0.1a", 13.0f, 15.0f, 0x00CC00FF);
        float offset = 0.0f;
        for (int i = 0; i < LINES; i++) {

            // don't draw past line 15/cursor
            if (LINES > 15 && i > 15 && cursor < i){
                if (i == LINES-1 && cursor < LINES){
                    font.renderChars("______", 15.0f, 380.0f, 0xFFFFFF80);
                }
                continue; 
            };

            // initiate scroll
            if (cursor > 15) {
                if (i == 0 || i == 1) {
                    offset = (60.0f + (i * 20.0f));
                }
                else if ((i > 1) && (i < (cursor - 13))) {
                    continue;
                } else {
                    offset = (60.0f + (i - (cursor - 15)) * 20.0f);
                }
            } 
            // normal line rendering offset
            else {
                offset = (60.0f + (i * 20.0f));
            }

            int cursor_color = 0xFFFFFF00;
            int description_color = 0xFFFFFF00;
            int cursor_alpha = 0xFF;
            int description_alpha = 0xFF;
            int drop_shadows_color = 0x00000080;

            // fade line/hide descriptions for lines the cursor isn't on
            if (input_lines[i].idx != cursor) {
                cursor_alpha = 0x80;
                description_alpha = 0x00;
            }

            cursor_color |= cursor_alpha;
            description_color |= description_alpha;

            // logic for lines that are toggleable
            if (input_lines[i].toggleable) {
                char toggleline[54];
                for (int j = 0; j < 50; j++) {
                    toggleline[j] = input_lines[i].line[j];
                }
                if (*input_lines[i].activation_flag) {
                    strcat(toggleline, " [X]");
                } else {
                    strcat(toggleline, " [ ]");
                }

                font.renderChars(toggleline, 15.0f, offset, cursor_color);
                if (g_drop_shadows) {
                    font.renderChars(toggleline, 15.0f + 2.0f, offset + 2.0f, drop_shadows_color);
                };
            }
            // logic for lines that are lists
            else if (input_lines[i].is_list) {
                char final_line[50];
                char list_line[MAX_LIST_MEMBER_LENGTH];
                sprintf(list_line, input_lines[i].list_member[*input_lines[i].list_member_idx].member);
                sprintf(final_line, input_lines[i].line);
                strcat(final_line, " ");
                strcat(final_line, list_line);
                font.renderChars(final_line, 15.0f, offset, cursor_color);
                if (g_drop_shadows) {
                    font.renderChars(final_line, 15.0f + 2.0f, offset + 2.0f, 0x00000080);
                }
            } 
            // logic for normal lines
            else {
                font.renderChars(input_lines[i].line, 15.0f, offset, cursor_color);
                if (g_drop_shadows) {
                    font.renderChars(input_lines[i].line, 15.0f + 2.0f, offset + 2.0f, drop_shadows_color);
                };
            }

            // render line descriptions
            font.renderChars(input_lines[i].description, 15.0f, 440.f, description_color);
            if (g_drop_shadows && input_lines[i].idx == cursor) {
                font.renderChars(input_lines[i].description, 15.0f + 2.0f, 440.0f + 2.0f, drop_shadows_color);
            };
        };
    }  // namespace Utilities

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

    void enable_bg_music() {
        tp_zelAudio.bg_audio = 1.0f;
        tp_zelAudio.enemy_bg_music_volume = 1.0f;
        tp_zelAudio.hyrule_castle_bg_music_volume = 1.0f;
    }

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
