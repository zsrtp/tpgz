#include "menus/memory_editor_menu.h"
#include "controller.h"
#include "font.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menus/settings_menu.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define MAX_DISPLAY_LINES 15
#define WHITE_RGBA 0xFFFFFFFF
#define ADDRESS_RGBA 0xBABABAFF
#define LINE_X_OFFSET 20.0f
#define LINE_BYTE_OFFSET 100.0f

static Cursor cursor = {0, 0};
bool init_once = false;
bool lock_cursor_y = false;
bool lock_cursor_x = false;
bool index_selected = false;
uint8_t index_place = 0;
uint8_t byte_index = 0;
uint32_t address_index = 0x80000000;

uint32_t mem_cursor_color;
uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

// returns the width of the rendered string
float render_selected_number_selector(const char* str, float x, float y, size_t selected_char_index,
                                      size_t max_char, uint32_t color) {
    float pos = 0.0f;
    for (size_t i = 0; i <= max_char; ++i) {
        Font::gz_renderChar(str[i], x + pos, y, selected_char_index == i ? CURSOR_RGBA : color,
                            g_drop_shadows);
        pos += Font::get_char_width(str[i]);
    }
    return pos;
}

void render_memory(Cursor cursor) {
    char index[9];
    tp_sprintf(index, "%08X", address_index);

    if (index_selected) {
        if (button_is_pressed(Controller::DPAD_RIGHT)) {
            if (index_place == 7) {
                index_place = 0;
            } else if (index_place >= 0 && index_place < 8) {
                index_place++;
            }
        }
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            if (index_place == 0) {
                index_place = 7;
            } else if (index_place >= 0 && index_place < 8) {
                index_place--;
            }
        }
        if (button_is_pressed(Controller::DPAD_UP)) {
            switch (index_place) {
            case 0: {
                address_index = 0x81FFFFFF;
                break;
            }
            case 1: {
                address_index += 0x1000000;
                break;
            }
            case 2: {
                address_index += 0x100000;
                break;
            }
            case 3: {
                address_index += 0x10000;
                break;
            }
            case 4: {
                address_index += 0x1000;
                break;
            }
            case 5: {
                address_index += 0x100;
                break;
            }
            case 6: {
                address_index += 0x10;
                break;
            }
            case 7: {
                address_index += 0x1;
                break;
            }
            }
            if (address_index > 0x81FFFFFF) {
                address_index = 0x81FFFFFF;
            }
        }
        if (button_is_pressed(Controller::DPAD_DOWN)) {
            switch (index_place) {
            case 0: {
                address_index -= 0x10000000;
                break;
            }
            case 1: {
                address_index -= 0x1000000;
                break;
            }
            case 2: {
                address_index -= 0x100000;
                break;
            }
            case 3: {
                address_index -= 0x10000;
                break;
            }
            case 4: {
                address_index -= 0x1000;
                break;
            }
            case 5: {
                address_index -= 0x100;
                break;
            }
            case 6: {
                address_index -= 0x10;
                break;
            }
            case 7: {
                address_index -= 0x1;
                break;
            }
            }
            if (address_index < 0x80000000) {
                address_index = 0x80000000;
            }
        }
        render_selected_number_selector(index, LINE_X_OFFSET, 80.0f, index_place, 7, WHITE_RGBA);
    } else {
        Font::gz_renderChars(index, LINE_X_OFFSET, 80.0f,
                             (cursor.y == 0 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
    }

    if (cursor.y > 0 && !lock_cursor_x) {
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            if (byte_index == 0) {
                byte_index = 7;
            } else if (byte_index >= 0 && byte_index < 8) {
                byte_index--;
            }
        }
        if (button_is_pressed(Controller::DPAD_RIGHT)) {
            if (byte_index == 7) {
                byte_index = 0;
            } else if (byte_index >= 0 && byte_index < 8) {
                byte_index++;
            }
        }
    }

    for (uint8_t i = 0; i < MAX_DISPLAY_LINES; i++) {
        float y_offset;
        y_offset = ((100.0f) + (i * 20.0f));

        char address[10];
        char b0[3];
        char b1[3];
        char b2[3];
        char b3[3];
        char b4[3];
        char b5[3];
        char b6[3];
        char b7[3];

        tp_sprintf(address, "%08X ", address_index + (i * 8));
        tp_sprintf(b0, "%02X", *(uint8_t*)(address_index + (i * 8)));
        tp_sprintf(b1, "%02X", *(uint8_t*)((address_index + (i * 8)) + 1));
        tp_sprintf(b2, "%02X", *(uint8_t*)((address_index + (i * 8)) + 2));
        tp_sprintf(b3, "%02X", *(uint8_t*)((address_index + (i * 8)) + 3));
        tp_sprintf(b4, "%02X", *(uint8_t*)((address_index + (i * 8)) + 4));
        tp_sprintf(b5, "%02X", *(uint8_t*)((address_index + (i * 8)) + 5));
        tp_sprintf(b6, "%02X", *(uint8_t*)((address_index + (i * 8)) + 6));
        tp_sprintf(b7, "%02X", *(uint8_t*)((address_index + (i * 8)) + 7));

        float address_offset = Font::get_chars_width(address) + LINE_X_OFFSET;
        float two_numbers_offset = Font::get_chars_width(" 00");
        if (cursor.y == (i + 1) && lock_cursor_x && lock_cursor_y) {
            if (button_is_pressed(Controller::DPAD_UP)) {
                *(uint8_t*)((address_index + (i * 8)) + byte_index) += 0x1;
            }
            if (button_is_pressed(Controller::DPAD_DOWN)) {
                *(uint8_t*)((address_index + (i * 8)) + byte_index) -= 0x1;
            }
            if (button_is_pressed(Controller::DPAD_RIGHT)) {
                *(uint8_t*)((address_index + (i * 8)) + byte_index) += 0x10;
            }
            if (button_is_pressed(Controller::DPAD_LEFT)) {
                *(uint8_t*)((address_index + (i * 8)) + byte_index) -= 0x10;
            }
        }

        //  cycle cursor color when value selected
        if (lock_cursor_x && lock_cursor_y) {
            if (red < 0x00A0 && (green == 0x0000 && blue == 0x0000)) {
                red += 0x0001;
            } else if (green < 0x00A0 && (blue == 0x0000 && red == 0x00A0)) {
                green += 0x0001;
            } else if (blue < 0x00A0 && (green == 0x00A0 && red == 0x00A0)) {
                blue += 0x0001;
            } else if (red > 0x0000 && (green == 0x00A0 && blue == 0x00A0)) {
                red -= 0x0001;
            } else if (green > 0x0000 && (blue == 0x00A0 && red == 0x0000)) {
                green -= 0x0001;
            } else {
                blue -= 0x0001;
            }
            mem_cursor_color = (red << 24) | (green << 16) | (blue << 8) | 0xFF;
        } else {
            mem_cursor_color = CURSOR_RGBA;
        }

        Font::gz_renderChars(address, LINE_X_OFFSET, y_offset,
                             (cursor.y == (i + 1) ? CURSOR_RGBA : ADDRESS_RGBA), g_drop_shadows);
        Font::gz_renderChars(
            b0, address_offset, y_offset,
            (byte_index == 0 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
            g_drop_shadows);
        Font::gz_renderChars(
            b1, address_offset + two_numbers_offset * 1, y_offset,
            (byte_index == 1 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
            g_drop_shadows);
        Font::gz_renderChars(
            b2, address_offset + two_numbers_offset * 2, y_offset,
            (byte_index == 2 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
            g_drop_shadows);
        Font::gz_renderChars(
            b3, address_offset + two_numbers_offset * 3, y_offset,
            (byte_index == 3 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
            g_drop_shadows);
        Font::gz_renderChars(
            b4, address_offset + two_numbers_offset * 4, y_offset,
            (byte_index == 4 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
            g_drop_shadows);
        Font::gz_renderChars(
            b5, address_offset + two_numbers_offset * 5, y_offset,
            (byte_index == 5 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
            g_drop_shadows);
        Font::gz_renderChars(
            b6, address_offset + two_numbers_offset * 6, y_offset,
            (byte_index == 6 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
            g_drop_shadows);
        Font::gz_renderChars(
            b7, address_offset + two_numbers_offset * 7, y_offset,
            (byte_index == 7 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
            g_drop_shadows);
    }
}

void MemoryEditorMenu::render() {
    if (button_is_pressed(Controller::B)) {
        if (index_selected) {
            lock_cursor_y = false;
            index_selected = false;
        } else if (lock_cursor_x || lock_cursor_y) {
            lock_cursor_x = false;
            lock_cursor_y = false;
        } else {
            init_once = false;
            MenuRendering::set_menu(MN_MEMORY_INDEX);
            return;
        }
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == Controller::Pad::A && a_held == false) {
        switch (cursor.y) {
        case 0: {
            lock_cursor_y = true;
            index_selected = true;
        }
        }

        if (cursor.y > 0) {
            lock_cursor_x = true;
            lock_cursor_y = true;
        }
    }

    Utilities::move_cursor(cursor, 1 + MAX_DISPLAY_LINES, 8, lock_cursor_x, lock_cursor_y, false,
                           true);
    Font::gz_renderChars("DPad to move/modify value, A/B to (de)select value", 25.0f, 440.f,
                         0xFFFFFFFF, g_drop_shadows);
    render_memory(cursor);
};