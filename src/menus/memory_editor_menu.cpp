#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include <stdio.h>

#define MAX_DISPLAY_LINES 15
#define WHITE_RGBA 0xFFFFFFFF
#define ADDRESS_RGBA 0xBABABAFF
#define LINE_X_OFFSET 20.0f
#define LINE_BYTE_OFFSET 100.0f

static Cursor cursor = {0, 0};
bool memory_editor_visible;
bool init_once = false;
bool lock_cursor_y = false;
bool lock_cursor_x = false;
bool index_selected = false;
uint8_t index_place = 0;
uint32_t address_index = 0x80000000;

MemoryLine memory_lines[MAX_DISPLAY_LINES] = {};

void render_memory(Font& font, Cursor cursor) {
    char index[9];
    sprintf(index, "%08X", address_index);

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
        font.gz_renderChar(index[0], LINE_X_OFFSET, 80.0f, (index_place == 0 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
        font.gz_renderChar(index[1], LINE_X_OFFSET + 10.0f, 80.0f, (index_place == 1 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
        font.gz_renderChar(index[2], LINE_X_OFFSET + 20.0f, 80.0f, (index_place == 2 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
        font.gz_renderChar(index[3], LINE_X_OFFSET + 30.0f, 80.0f, (index_place == 3 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
        font.gz_renderChar(index[4], LINE_X_OFFSET + 40.0f, 80.0f, (index_place == 4 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
        font.gz_renderChar(index[5], LINE_X_OFFSET + 50.0f, 80.0f, (index_place == 5 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
        font.gz_renderChar(index[6], LINE_X_OFFSET + 60.0f, 80.0f, (index_place == 6 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
        font.gz_renderChar(index[7], LINE_X_OFFSET + 70.0f, 80.0f, (index_place == 7 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
    } else {
        font.gz_renderChars(index, LINE_X_OFFSET, 80.0f, (cursor.y == 0 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
    }

    for (uint8_t i = 0; i < MAX_DISPLAY_LINES; i++) {
        float y_offset;
        y_offset = ((100.0f) + (i * 20.0f));

        char address[9];
        char b0[3];
        char b1[3];
        char b2[3];
        char b3[3];
        char b4[3];
        char b5[3];
        char b6[3];
        char b7[3];

        sprintf(address, "%08X", address_index + (i * 8));
        sprintf(b0, "%02X", *(uint8_t*)(address_index + (i * 8)));
        sprintf(b1, "%02X", *(uint8_t*)((address_index + (i * 8)) + 1));
        sprintf(b2, "%02X", *(uint8_t*)((address_index + (i * 8)) + 2));
        sprintf(b3, "%02X", *(uint8_t*)((address_index + (i * 8)) + 3));
        sprintf(b4, "%02X", *(uint8_t*)((address_index + (i * 8)) + 4));
        sprintf(b5, "%02X", *(uint8_t*)((address_index + (i * 8)) + 5));
        sprintf(b6, "%02X", *(uint8_t*)((address_index + (i * 8)) + 6));
        sprintf(b7, "%02X", *(uint8_t*)((address_index + (i * 8)) + 7));

        if (memory_lines[i].line_selected) {
            if (memory_lines[i].value_selected) {
                if (button_is_pressed(Controller::DPAD_UP)) {
                    *(uint8_t*)((address_index + (i * 8)) + cursor.x) += 0x1;
                }
                if (button_is_pressed(Controller::DPAD_DOWN)) {
                    *(uint8_t*)((address_index + (i * 8)) + cursor.x) -= 0x1;
                }
                if (button_is_pressed(Controller::DPAD_RIGHT)) {
                    *(uint8_t*)((address_index + (i * 8)) + cursor.x) += 0x10;
                }
                if (button_is_pressed(Controller::DPAD_LEFT)) {
                    *(uint8_t*)((address_index + (i * 8)) + cursor.x) -= 0x10;
                }
            }

            font.gz_renderChars(address, LINE_X_OFFSET, y_offset, (cursor.y == (i + 1) ? CURSOR_RGBA : ADDRESS_RGBA), g_drop_shadows);
            font.gz_renderChars(b0, LINE_BYTE_OFFSET, y_offset, (cursor.x == 0 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(b1, LINE_BYTE_OFFSET + 25.0f, y_offset, (cursor.x == 1 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(b2, LINE_BYTE_OFFSET + 50.0f, y_offset, (cursor.x == 2 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(b3, LINE_BYTE_OFFSET + 75.0f, y_offset, (cursor.x == 3 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(b4, LINE_BYTE_OFFSET + 100.0f, y_offset, (cursor.x == 4 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(b5, LINE_BYTE_OFFSET + 125.0f, y_offset, (cursor.x == 5 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(b6, LINE_BYTE_OFFSET + 150.0f, y_offset, (cursor.x == 6 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(b7, LINE_BYTE_OFFSET + 175.0f, y_offset, (cursor.x == 7 ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
        } else {
            font.gz_renderChars(address, LINE_X_OFFSET, y_offset, (cursor.y == (i + 1) ? CURSOR_RGBA : ADDRESS_RGBA), g_drop_shadows);
            font.gz_renderChars(b0, LINE_BYTE_OFFSET, y_offset, WHITE_RGBA, g_drop_shadows);
            font.gz_renderChars(b1, LINE_BYTE_OFFSET + 25.0f, y_offset, WHITE_RGBA, g_drop_shadows);
            font.gz_renderChars(b2, LINE_BYTE_OFFSET + 50.0f, y_offset, WHITE_RGBA, g_drop_shadows);
            font.gz_renderChars(b3, LINE_BYTE_OFFSET + 75.0f, y_offset, WHITE_RGBA, g_drop_shadows);
            font.gz_renderChars(b4, LINE_BYTE_OFFSET + 100.0f, y_offset, WHITE_RGBA, g_drop_shadows);
            font.gz_renderChars(b5, LINE_BYTE_OFFSET + 125.0f, y_offset, WHITE_RGBA, g_drop_shadows);
            font.gz_renderChars(b6, LINE_BYTE_OFFSET + 150.0f, y_offset, WHITE_RGBA, g_drop_shadows);
            font.gz_renderChars(b7, LINE_BYTE_OFFSET + 175.0f, y_offset, WHITE_RGBA, g_drop_shadows);
        }
    }
}

bool check_mem_line_selected(MemoryLine memory_lines[]) {
    bool return_value = false;
    for (int i = 0; i < MAX_DISPLAY_LINES; i++) {
        if (memory_lines[i].line_selected) {
            return_value = true;
        }
    }

    return return_value;
}

bool check_mem_line_value_selected(MemoryLine memory_lines[]) {
    bool return_value = false;
    for (int i = 0; i < MAX_DISPLAY_LINES; i++) {
        if (memory_lines[i].value_selected) {
            return_value = true;
        }
    }

    return return_value;
}

void MemoryEditorMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        if (index_selected) {
            lock_cursor_y = false;
            index_selected = false;
        } else if (check_mem_line_value_selected(memory_lines)) {
            for (int i = 0; i < MAX_DISPLAY_LINES; i++) {
                memory_lines[i].value_selected = false;
            }
            lock_cursor_x = false;
        } else if (check_mem_line_selected(memory_lines)) {
            for (int i = 0; i < MAX_DISPLAY_LINES; i++) {
                memory_lines[i].line_selected = false;
            }
            lock_cursor_y = false;
        } else {
            init_once = false;
            memory_editor_visible = false;
            memory_visible = true;
            mm_visible = false;
            return;
        }
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
        switch (cursor.y) {
            case 0: {
                lock_cursor_y = true;
                index_selected = true;
            }
        }

        if (cursor.y > 0) {
            if (memory_lines[cursor.y - 1].line_selected) {
                memory_lines[cursor.y - 1].value_selected = true;
                lock_cursor_x = true;
            } else {
                memory_lines[cursor.y - 1].line_selected = true;
                lock_cursor_y = true;
            }
        }
    }

    Utilities::move_cursor(cursor, 1 + MAX_DISPLAY_LINES, 8, lock_cursor_x, lock_cursor_y);
    font.gz_renderChars("DPad to move/change value, A/B to select/cancel line/value", 25.0f, 440.f, 0xFFFFFFFF, g_drop_shadows);
    render_memory(font, cursor);
};