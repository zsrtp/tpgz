#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "libtp_c/include/system.h"
#include <stdio.h>

#define WATCH_COLUMNS 6
#define WATCH_ADDRESS_X_OFFSET 25.0f
#define WATCH_X_POS_X_OFFSET 133.0f
#define WATCH_Y_POS_X_OFFSET 171.0f
#define WATCH_HEX_X_OFFSET 208.5f
#define WATCH_TYPE_X_OFFSET 260.5f
#define WATCH_OFFSET_X_OFFSET 294.5f
#define WATCH_VISIBLE_X_OFFSET 364.0f
#define WHITE_RGBA 0xFFFFFFFF

Cursor cursor;

bool watches_visible;
bool init_once = false;
bool lock_cursor_y = false;
bool lock_cursor_x = false;
uint8_t watch_address_index = 3;
uint8_t offset_index = 2;
MemoryWatch Watches[MAX_WATCHES] = {};

void render_memory_lines(Font& font, MemoryWatch Watches[MAX_WATCHES], Cursor cursor) {
    font.gz_renderChars("Address     X   Y   Hex Type Offset Visible", 25.0f, 60.0f, 0xFFFFFFFF, g_drop_shadows);
    for (int i = 0; i < MAX_WATCHES; i++) {
#define LINE_Y_OFFSET (80.0f + (i * 20.0f))
        char watch_address[11];
        char watch_x[8];
        char watch_y[8];
        char watch_hex[8];
        char watch_type[6];
        char watch_offset[7];
        char watch_visible[4];

        sprintf(watch_address, "0x%08X", Watches[i].address);
        sprintf(watch_x, "%.0f", Watches[i].x);
        sprintf(watch_y, "%.0f", Watches[i].y);
        sprintf(watch_hex, "%s", Watches[i].hex ? "true" : "false");
        switch (Watches[i].type) {
            case u8: {
                sprintf(watch_type, "u8");
                break;
            }
            case u16: {
                sprintf(watch_type, "u16");
                break;
            }
            case u32: {
                sprintf(watch_type, "u32");
                break;
            }
            case i8: {
                sprintf(watch_type, "i8");
                break;
            }
            case i16: {
                sprintf(watch_type, "i16");
                break;
            }
            case i32: {
                sprintf(watch_type, "i32");
                break;
            }

            case f32: {
                sprintf(watch_type, "f32");
                break;
            }
            case string: {
                sprintf(watch_type, "str");
            }
        }
        sprintf(watch_offset, "0x%04X", Watches[i].offset);
        sprintf(watch_visible, "%s", Watches[i].visible ? "[X]" : "[ ]");

        if (Watches[i].line_selected) {
            switch (cursor.x) {
                case WatchAddress: {
                    if (Watches[i].value_selected) {
                        if (button_is_pressed(Controller::DPAD_RIGHT)) {
                            if (watch_address_index == 9) {
                                watch_address_index = 3;
                            } else if (watch_address_index >= 3 && watch_address_index < 9) {
                                watch_address_index++;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_LEFT)) {
                            if (watch_address_index == 3) {
                                watch_address_index = 9;
                            } else if (watch_address_index > 3 && watch_address_index <= 9) {
                                watch_address_index--;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_UP)) {
                            switch (watch_address_index) {
                                case 3: {
                                    Watches[i].address = 0x81FFFFFF;
                                    break;
                                }
                                case 4: {
                                    Watches[i].address += 0x100000;
                                    break;
                                }
                                case 5: {
                                    Watches[i].address += 0x10000;
                                    break;
                                }
                                case 6: {
                                    Watches[i].address += 0x1000;
                                    break;
                                }
                                case 7: {
                                    Watches[i].address += 0x100;
                                    break;
                                }
                                case 8: {
                                    Watches[i].address += 0x10;
                                    break;
                                }
                                case 9: {
                                    Watches[i].address += 0x1;
                                    break;
                                }
                            }
                            if (Watches[i].address > 0x81FFFFFF) {
                                Watches[i].address = 0x81FFFFFF;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_DOWN)) {
                            switch (watch_address_index) {
                                case 3: {
                                    Watches[i].address -= 0x1000000;
                                    break;
                                }
                                case 4: {
                                    Watches[i].address -= 0x100000;
                                    break;
                                }
                                case 5: {
                                    Watches[i].address -= 0x10000;
                                    break;
                                }
                                case 6: {
                                    Watches[i].address -= 0x1000;
                                    break;
                                }
                                case 7: {
                                    Watches[i].address -= 0x100;
                                    break;
                                }
                                case 8: {
                                    Watches[i].address -= 0x10;
                                    break;
                                }
                                case 9: {
                                    Watches[i].address -= 0x1;
                                    break;
                                }
                            }
                            if (Watches[i].address < 0x80000000) {
                                Watches[i].address = 0x80000000;
                            }
                        }

                        font.gz_renderChar(watch_address[0], WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_address[1], WATCH_ADDRESS_X_OFFSET + 10.0f, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_address[2], WATCH_ADDRESS_X_OFFSET + 20.0f, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_address[3], WATCH_ADDRESS_X_OFFSET + 28.0f, LINE_Y_OFFSET, watch_address_index == 3 ? CURSOR_RGBA : WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_address[4], WATCH_ADDRESS_X_OFFSET + 38.0f, LINE_Y_OFFSET, watch_address_index == 4 ? CURSOR_RGBA : WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_address[5], WATCH_ADDRESS_X_OFFSET + 48.0f, LINE_Y_OFFSET, watch_address_index == 5 ? CURSOR_RGBA : WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_address[6], WATCH_ADDRESS_X_OFFSET + 58.0f, LINE_Y_OFFSET, watch_address_index == 6 ? CURSOR_RGBA : WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_address[7], WATCH_ADDRESS_X_OFFSET + 68.0f, LINE_Y_OFFSET, watch_address_index == 7 ? CURSOR_RGBA : WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_address[8], WATCH_ADDRESS_X_OFFSET + 78.0f, LINE_Y_OFFSET, watch_address_index == 8 ? CURSOR_RGBA : WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_address[9], WATCH_ADDRESS_X_OFFSET + 88.0f, LINE_Y_OFFSET, watch_address_index == 9 ? CURSOR_RGBA : WHITE_RGBA, g_drop_shadows);
                    } else {
                        font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
                case WatchX: {
                    if (Watches[i].value_selected) {
                        if (button_is_pressed(Controller::DPAD_RIGHT)) {
                            if (Watches[i].x >= 0.0f && Watches[i].x < 500.0f) {
                                Watches[i].x++;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_LEFT)) {
                            if (Watches[i].x > 0.0f && Watches[i].x <= 500.0f) {
                                Watches[i].x--;
                            }
                        }
                        sprintf(watch_x, "<%.0f>", Watches[i].x);
                        font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET - 8.0f, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    } else {
                        font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
                case WatchY: {
                    if (Watches[i].value_selected) {
                        if (button_is_pressed(Controller::DPAD_RIGHT)) {
                            if (Watches[i].y >= 0.0f && Watches[i].y < 500.0f) {
                                Watches[i].y++;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_LEFT)) {
                            if (Watches[i].y > 0.0f && Watches[i].y <= 500.0f) {
                                Watches[i].y--;
                            }
                        }
                        sprintf(watch_y, "<%.0f>", Watches[i].y);
                        font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET - 8.0f, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    } else {
                        font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);

                    break;
                }
                case WatchHex: {
                    if (Watches[i].value_selected) {
                        if (button_is_pressed(Controller::DPAD_RIGHT)) {
                            Watches[i].hex = !Watches[i].hex;
                        }
                        if (button_is_pressed(Controller::DPAD_LEFT)) {
                            Watches[i].hex = !Watches[i].hex;
                        }
                        sprintf(watch_hex, "<%s>", Watches[i].hex ? "true" : "false");
                        font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET - 8.0f, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    } else {
                        font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
                case WatchType: {
                    if (Watches[i].value_selected) {
                        if (button_is_pressed(Controller::DPAD_RIGHT)) {
                            if (Watches[i].type == string) {
                                Watches[i].type = u8;
                            } else if (Watches[i].type >= u8 && Watches[i].type < string) {
                                Watches[i].type++;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_LEFT)) {
                            if (Watches[i].type == u8) {
                                Watches[i].type = string;
                            } else if (Watches[i].type > u8 && Watches[i].type <= string) {
                                Watches[i].type--;
                            }
                        }
                        switch (Watches[i].type) {
                            case u8: {
                                sprintf(watch_type, "<u8>");
                                break;
                            }
                            case u16: {
                                sprintf(watch_type, "<u16>");
                                break;
                            }
                            case u32: {
                                sprintf(watch_type, "<u32>");
                                break;
                            }
                            case i8: {
                                sprintf(watch_type, "<i8>");
                                break;
                            }
                            case i16: {
                                sprintf(watch_type, "<i16>");
                                break;
                            }
                            case i32: {
                                sprintf(watch_type, "<i32>");
                                break;
                            }

                            case f32: {
                                sprintf(watch_type, "<f32>");
                                break;
                            }
                            case string: {
                                sprintf(watch_type, "<str>");
                            }
                        }
                        font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET - 8.0f, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    } else {
                        font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
                case WatchOffset: {
                    if (Watches[i].value_selected) {
                        if (button_is_pressed(Controller::DPAD_RIGHT)) {
                            if (offset_index == 5) {
                                offset_index = 2;
                            } else if (offset_index >= 2 && offset_index < 5) {
                                offset_index++;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_LEFT)) {
                            if (offset_index == 2) {
                                offset_index = 5;
                            } else if (offset_index > 2 && offset_index <= 5) {
                                offset_index--;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_UP)) {
                            switch (offset_index) {
                                case 2: {
                                    Watches[i].offset += 0x1000;
                                    break;
                                }
                                case 3: {
                                    Watches[i].offset += 0x100;
                                    break;
                                }
                                case 4: {
                                    Watches[i].offset += 0x10;
                                    break;
                                }
                                case 5: {
                                    Watches[i].offset += 0x1;
                                    break;
                                }
                            }
                            if (Watches[i].offset > 0xFFFF) {
                                Watches[i].offset = 0xFFFF;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_DOWN)) {
                            switch (offset_index) {
                                case 2: {
                                    Watches[i].offset -= 0x1000;
                                    break;
                                }
                                case 3: {
                                    Watches[i].offset -= 0x100;
                                    break;
                                }
                                case 4: {
                                    Watches[i].offset -= 0x10;
                                    break;
                                }
                                case 5: {
                                    Watches[i].offset -= 0x1;
                                    break;
                                }
                            }
                            if (Watches[i].offset < 0x0000) {
                                Watches[i].offset = 0x0000;
                            }
                        }
                        font.gz_renderChar(watch_offset[0], WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_offset[1], WATCH_OFFSET_X_OFFSET + 10.0f, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_offset[2], WATCH_OFFSET_X_OFFSET + 20.0f, LINE_Y_OFFSET, offset_index == 2 ? CURSOR_RGBA : WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_offset[3], WATCH_OFFSET_X_OFFSET + 30.0f, LINE_Y_OFFSET, offset_index == 3 ? CURSOR_RGBA : WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_offset[4], WATCH_OFFSET_X_OFFSET + 40.0f, LINE_Y_OFFSET, offset_index == 4 ? CURSOR_RGBA : WHITE_RGBA, g_drop_shadows);
                        font.gz_renderChar(watch_offset[5], WATCH_OFFSET_X_OFFSET + 50.0f, LINE_Y_OFFSET, offset_index == 5 ? CURSOR_RGBA : WHITE_RGBA, g_drop_shadows);
                    } else {
                        font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
            }
        } else {
            font.gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(watch_x, WATCH_X_POS_X_OFFSET, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(watch_y, WATCH_Y_POS_X_OFFSET, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(watch_hex, WATCH_HEX_X_OFFSET, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(watch_type, WATCH_TYPE_X_OFFSET, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(watch_offset, WATCH_OFFSET_X_OFFSET, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            font.gz_renderChars(watch_visible, WATCH_VISIBLE_X_OFFSET, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
        }
    }
}

bool check_if_any_memory_line_is_selected(MemoryWatch Watches[]) {
    bool return_value = false;
    for (int i = 0; i < MAX_WATCHES; i++) {
        if (Watches[i].line_selected) {
            return_value = true;
        }
    }
    return return_value;
}

bool check_if_any_line_value_is_selected(MemoryWatch Watches[]) {
    bool return_value = false;
    for (int i = 0; i < MAX_WATCHES; i++) {
        if (Watches[i].value_selected) {
            return_value = true;
        }
    }

    return return_value;
}

void WatchesMenu::render(Font& font) {
    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (button_is_pressed(Controller::B)) {
        if (check_if_any_line_value_is_selected(Watches)) {
            for (int i = 0; i < MAX_WATCHES; i++) {
                Watches[i].value_selected = false;
            }
            Watches[cursor.y].value_selected = false;
            lock_cursor_x = false;
        } else if (check_if_any_memory_line_is_selected(Watches)) {
            for (int i = 0; i < MAX_WATCHES; i++) {
                Watches[i].line_selected = false;
            }
            Watches[cursor.y].line_selected = false;
            lock_cursor_y = false;
        } else {
            init_once = false;
            watches_visible = false;
            memory_visible = true;
            mm_visible = false;
            return;
        }
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
        // finish
        if (Watches[cursor.y].value_selected) {
            Watches[cursor.y].value_selected = false;
            lock_cursor_x = false;
        } else if (Watches[cursor.y].line_selected) {
            Watches[cursor.y].value_selected = true;
            lock_cursor_x = true;
        } else {
            Watches[cursor.y].line_selected = true;
            lock_cursor_y = true;
        }
    }

    if (button_is_pressed(Controller::Z)) {
        Watches[cursor.y].visible = !Watches[cursor.y].visible;
    }

    if (button_is_pressed(Controller::Y)) {
        address_index = Watches[cursor.y].address;
        init_once = false;
        watches_visible = false;
        memory_editor_visible = true;
    }

    Utilities::move_cursor(cursor, MAX_WATCHES, WATCH_COLUMNS, lock_cursor_x, lock_cursor_y);
    font.gz_renderChars("Press z to enable/disable watch. Y to jump to editor address", 25.0f, 440.f, 0xFFFFFFFF, g_drop_shadows);
    render_memory_lines(font, Watches, cursor);
};