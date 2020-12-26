#include "font.h"
#include "menus/temp_flags_menu.h"
#include "menus/settings_menu.h"
#include "controller.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/math.h"
#include "libtp_c/include/system.h"
#include "utils/texture.h"
#include "utils/draw.h"

#define MAX_FLAGS 0x20
#define WHITE_RGBA 0xFFFFFFFF
#define LINES 8

static Cursor cursor = {0, 0};
bool init_once = false;
bool lock_cursor_y = false;
bool lock_cursor_x = false;
uint8_t bit_index = 0;

Texture gzFlagOnTex;
Texture gzFlagOffTex;

AreaNode TempFlags[MAX_FLAGS] = {};

void render_area_flags(Cursor cursor) {
    for (uint8_t i = 0; i < MAX_FLAGS; i++) {
        float y_offset;
#define LINE_X_OFFSET 20.0f

        // don't draw past max lines/cursor
        if (i > LINES && cursor.y < i) {
            Font::gz_renderChars("______", LINE_X_OFFSET, 250.0f, 0xFFFFFF80, g_drop_shadows);
            continue;
        };

        // initiate scroll
        if (cursor.y > LINES) {
            if (i < (cursor.y - LINES)) {
                continue;
            } else {
                y_offset = ((80.0f) + (i - (cursor.y - LINES)) * 20.0f);
            }
        }
        // normal line rendering offset
        else {
            y_offset = ((80.0f) + (i * 20.0f));
        }

        TempFlags[i].offset = i;
        TempFlags[i].bit[0] = (tp_gameInfo.temp_flags.flags[i] & (1 << 0));
        TempFlags[i].bit[1] = (tp_gameInfo.temp_flags.flags[i] & (1 << 1));
        TempFlags[i].bit[2] = (tp_gameInfo.temp_flags.flags[i] & (1 << 2));
        TempFlags[i].bit[3] = (tp_gameInfo.temp_flags.flags[i] & (1 << 3));
        TempFlags[i].bit[4] = (tp_gameInfo.temp_flags.flags[i] & (1 << 4));
        TempFlags[i].bit[5] = (tp_gameInfo.temp_flags.flags[i] & (1 << 5));
        TempFlags[i].bit[6] = (tp_gameInfo.temp_flags.flags[i] & (1 << 6));
        TempFlags[i].bit[7] = (tp_gameInfo.temp_flags.flags[i] & (1 << 7));

        char offset[6];

        tp_sprintf(offset, "0x%02X:", TempFlags[i].offset);

        float temp_flag_offset = LINE_X_OFFSET + Font::get_chars_width(offset);

        for (uint8_t j = 0; j < 8; j++) {
            if (TempFlags[i].bit[j] == true) {
                Draw::draw_rect(0xFFFFFFFF, {temp_flag_offset + ((7 - j) * 20.0f), y_offset - 13.0f}, {16, 16}, &gzFlagOnTex._texObj);
            } else {
                Draw::draw_rect(0xFFFFFFFF, {temp_flag_offset + ((7 - j) * 20.0f), y_offset - 13.0f}, {16, 16}, &gzFlagOffTex._texObj);
            }
        }

        if (TempFlags[i].line_selected) {
            if (button_is_pressed(Controller::DPAD_RIGHT)) {
                if (bit_index == 0) {
                    bit_index = 7;
                } else if (bit_index >= 0 && bit_index < 8) {
                    bit_index--;
                }
            }
            if (button_is_pressed(Controller::DPAD_LEFT)) {
                if (bit_index == 7) {
                    bit_index = 0;
                } else if (bit_index >= 0 && bit_index < 8) {
                    bit_index++;
                }
            }
            if (current_input == Controller::Pad::A && a_held == false) {
                switch (bit_index) {
                    case 7: {
                        tp_gameInfo.temp_flags.flags[i] ^= (1 << 7);
                        break;
                    }
                    case 6: {
                        tp_gameInfo.temp_flags.flags[i] ^= (1 << 6);
                        break;
                    }
                    case 5: {
                        tp_gameInfo.temp_flags.flags[i] ^= (1 << 5);
                        break;
                    }
                    case 4: {
                        tp_gameInfo.temp_flags.flags[i] ^= (1 << 4);
                        break;
                    }
                    case 3: {
                        tp_gameInfo.temp_flags.flags[i] ^= (1 << 3);
                        break;
                    }
                    case 2: {
                        tp_gameInfo.temp_flags.flags[i] ^= (1 << 2);
                        break;
                    }
                    case 1: {
                        tp_gameInfo.temp_flags.flags[i] ^= (1 << 1);
                        break;
                    }
                    case 0: {
                        tp_gameInfo.temp_flags.flags[i] ^= (1 << 0);
                        break;
                    }
                }
            }
            Font::gz_renderChars(offset, LINE_X_OFFSET, y_offset, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            Draw::draw_rect(0x0080FF77, {temp_flag_offset + ((7 - bit_index) * 20.0f), y_offset - 13.0f}, {16, 16});  // Flag cursor
        } else {
            Font::gz_renderChars(offset, LINE_X_OFFSET, y_offset, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
        }
    }
}

bool check_offset_line_selected(AreaNode TempFlags[]) {
    bool return_value = false;
    for (int i = 0; i < MAX_FLAGS; i++) {
        if (TempFlags[i].line_selected) {
            return_value = true;
        }
    }

    return return_value;
}

void TempFlagsMenu::render() {
    if (button_is_pressed(Controller::B)) {
        if (check_offset_line_selected(TempFlags)) {
            for (int i = 0; i < MAX_FLAGS; i++) {
                TempFlags[i].line_selected = false;
            }
            TempFlags[cursor.y].line_selected = false;
            lock_cursor_y = false;
        } else {
            init_once = false;
            free_texture(&gzFlagOnTex);
            free_texture(&gzFlagOffTex);
            MenuRendering::set_menu(MN_FLAGS_INDEX);
            return;
        }
    }

    if (gzFlagOnTex.loadCode == TexCode::TEX_UNLOADED) {
        load_texture("tpgz/tex/flagOn.tex", &gzFlagOnTex);
    }
    if (gzFlagOffTex.loadCode == TexCode::TEX_UNLOADED) {
        load_texture("tpgz/tex/flagOff.tex", &gzFlagOffTex);
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (!TempFlags[cursor.y].line_selected && current_input == Controller::Pad::A && a_held == false) {
        TempFlags[cursor.y].line_selected = true;
        current_input = 0;
        lock_cursor_y = true;
    }

    Utilities::move_cursor(cursor, MAX_FLAGS, 1, lock_cursor_x, lock_cursor_y);
    Font::gz_renderChars("DPad to move/change value, A/B to select/cancel line", 25.0f, 440.f, 0xFFFFFFFF, g_drop_shadows);
    render_area_flags(cursor);
};