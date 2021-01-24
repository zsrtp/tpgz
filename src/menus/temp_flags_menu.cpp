#include "menus/temp_flags_menu.h"
#include "controller.h"
#include "font.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/math.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menus/settings_menu.h"
#include "utils/cursor.h"
#include "utils/draw.h"
#include "utils/lines.h"
#include "utils/texture.h"

#define MAX_FLAGS 0x20
#define WHITE_RGBA 0xFFFFFFFF
#define LINES 8

int min_line = 0;
int max_line = 8;

static Cursor cursor = {0, 0};
bool init_once = false;
uint8_t bit_index = 0;

Texture gzFlagOnTex;
Texture gzFlagOffTex;

void render_flag_records() {
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

    for (uint8_t i = 0; i < MAX_FLAGS; i++) {
        float y_offset;
#define LINE_X_OFFSET 20.0f

        if (cursor.y > max_line) {
            max_line = cursor.y;
            min_line = max_line - LINES;
        }
        if (cursor.y < min_line) {
            min_line = cursor.y;
            max_line = min_line + LINES;
        }

        if (i > max_line || i < min_line) {
            continue;
        }
        y_offset = (80.0f + (i - min_line) * 20.0f);

        char offset[6];

        tp_sprintf(offset, "0x%02X:", i);

        float flag_x_offset = LINE_X_OFFSET + Font::get_chars_width(offset);

        for (uint8_t bit = 0; bit < 8; bit++) {
            if (tp_gameInfo.temp_flags.flags[i] & (1 << bit)) {
                Draw::draw_rect(0xFFFFFFFF,
                                {flag_x_offset + ((7 - bit) * 20.0f), y_offset - 13.0f},
                                {16, 16}, &gzFlagOnTex._texObj);
            } else {
                Draw::draw_rect(0xFFFFFFFF,
                                {flag_x_offset + ((7 - bit) * 20.0f), y_offset - 13.0f},
                                {16, 16}, &gzFlagOffTex._texObj);
            }
        }
        if (cursor.y == i) {
            Draw::draw_rect(0x0080FF77,
                            {(flag_x_offset + ((7 - bit_index) * 20.0f)), y_offset - 13.0f},
                            {16, 16});  // Flag cursor
        }
        if (current_input == Controller::Pad::A && a_held == false) {
            if (cursor.y == i) {
                tp_gameInfo.temp_flags.flags[i] ^= (1 << bit_index);
            }
        }

        Font::gz_renderChars(offset, LINE_X_OFFSET, y_offset,
                             (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
    }
}

void TempFlagsMenu::render() {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        free_texture(&gzFlagOnTex);
        free_texture(&gzFlagOffTex);
        MenuRendering::set_menu(MN_FLAGS_INDEX);
        return;
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

    Utilities::move_cursor(cursor, MAX_FLAGS, 0, false, false, false, true);
    Font::gz_renderChars("DPad to move/change value, A to toggle flag", 25.0f, 440.f, 0xFFFFFFFF,
                         g_drop_shadows);
    render_flag_records();
};