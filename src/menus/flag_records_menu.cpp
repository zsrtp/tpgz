#include "menus/flag_records_menu.h"
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

#define MAX_DISPLAY_LINES 8
#define WHITE_RGBA 0xFFFFFFFF
#define MAX_RECORD_OPTIONS 4
#define FLAG_RECORD_INDEX 0

static Cursor cursor = {0, 0};
bool init_once = false;
int max_flags;
uint8_t bit_index = 0;
uint8_t record_index = 0;

Texture gzFlagOnTex;
Texture gzFlagOffTex;

#ifdef GCN_PLATFORM
#define SCRL_FORW_BUTTON (Controller::X)
#define SCRL_BACK_BUTTON (Controller::Y)
#define SCRL_FORW_TEXT "X"
#define SCRL_BACK_TEXT "Y"
#endif
#ifdef WII_PLATFORM
#define SCRL_FORW_BUTTON (Controller::TWO)
#define SCRL_BACK_BUTTON (Controller::ONE)
#define SCRL_FORW_TEXT "2"
#define SCRL_BACK_TEXT "1"
#endif

void render_flag_records(uint8_t record[]) {
    if (cursor.y > 0) {
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
    }

    for (uint8_t i = 0; i < MAX_DISPLAY_LINES; i++) {
        float y_offset;
#define LINE_X_OFFSET 20.0f

        y_offset = (80.0f + i * 20.0f);

        char offset[6];
        int idx_num;

        if (cursor.y > MAX_DISPLAY_LINES) {
            idx_num = i + (cursor.y - MAX_DISPLAY_LINES);
        } else {
            idx_num = i;
        }
        tp_sprintf(offset, "0x%02X:", idx_num);

        float flag_x_offset = LINE_X_OFFSET + Font::get_chars_width(offset);

        for (uint8_t bit = 0; bit < 8; bit++) {
            if (record[idx_num] & (1 << bit)) {
                Draw::draw_rect(0xFFFFFFFF, {flag_x_offset + ((7 - bit) * 20.0f), y_offset - 13.0f},
                                {16, 16}, &gzFlagOnTex._texObj);
            } else {
                Draw::draw_rect(0xFFFFFFFF, {flag_x_offset + ((7 - bit) * 20.0f), y_offset - 13.0f},
                                {16, 16}, &gzFlagOffTex._texObj);
            }
        }

        if (cursor.y == (idx_num + 1)) {
            Draw::draw_rect(0x0080FF77,
                            {(flag_x_offset + ((7 - bit_index) * 20.0f)), y_offset - 13.0f},
                            {16, 16});  // Flag cursor
        }
        if (current_input == Controller::Pad::A && a_held == false) {
            if (cursor.y == (idx_num + 1)) {
                record[idx_num] ^= (1 << bit_index);
            }
        }

        Font::gz_renderChars(offset, LINE_X_OFFSET, y_offset,
                             (cursor.y == (idx_num + 1) ? CURSOR_RGBA : WHITE_RGBA),
                             g_drop_shadows);
    }
}

void FlagRecordsMenu::render() {
    if (button_is_pressed(Controller::B)) {
        init_once = false;
        free_texture(&gzFlagOnTex);
        free_texture(&gzFlagOffTex);
        MenuRendering::set_menu(MN_FLAGS_INDEX);
        return;
    }

    if (button_is_pressed(Controller::Z)) {
        cursor.y = 0;
    }

    if (button_is_pressed(SCRL_BACK_BUTTON)) {
        cursor.y -= 0x10;
        if (cursor.y < 0) {
            cursor.y = 0;
        }
    } else if (button_is_pressed(SCRL_FORW_BUTTON)) {
        cursor.y += 0x10;
        if (cursor.y > max_flags + 1) {
            cursor.y = max_flags;
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

    ListMember flag_record_options[MAX_RECORD_OPTIONS] = {"area temp", "event", "minigame",
                                                          "dungeon"};
    if (cursor.y == FLAG_RECORD_INDEX) {
        cursor.x = record_index;
        Utilities::move_cursor(cursor, max_flags + 1, MAX_RECORD_OPTIONS, false, false, false,
                               true);
        if (cursor.y == FLAG_RECORD_INDEX) {
            record_index = cursor.x;
        }
    } else {
        Utilities::move_cursor(cursor, max_flags + 1, 0, false, false, false, true);
    }
    char record_type[9];
    tp_sprintf(record_type, " <%s>", flag_record_options[record_index].member);
    Font::gz_renderChars(record_type, 12.0f, 60.0f, (cursor.y == 0 ? CURSOR_RGBA : WHITE_RGBA),
                         g_drop_shadows);

    Font::gz_renderChars("DPad/" SCRL_BACK_TEXT "/" SCRL_FORW_TEXT
                         " to move cursor, A to toggle flag, Z to top",
                         25.0f, 440.f, 0xFFFFFFFF, g_drop_shadows);

    switch (record_index) {
    case 0: {
        max_flags = 0x20;
        render_flag_records(tp_gameInfo.temp_flags.flags);
        break;
    }
    case 1: {
        max_flags = 0x100;
        render_flag_records(tp_gameInfo.event_flags.flags);
        break;
    }
    case 2: {
        max_flags = 0x18;
        render_flag_records(tp_gameInfo.minigame_flags);
        break;
    }
    case 3: {
        max_flags = 0x18;
        render_flag_records((uint8_t*)tp_gameInfo.dungeon_temp_flags.switch_bitfield);
        break;
    }
    }
};