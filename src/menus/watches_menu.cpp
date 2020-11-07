#include "font.h"
#include "menus/memory_menu.h"
#include "menus/memory_editor_menu.h"
#include "menus/settings_menu.h"
#include "controller.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/math.h"


#define WATCH_COLUMNS 6
#define WATCH_ADDRESS_X_OFFSET 25.0f
#define WHITE_RGBA 0xFFFFFFFF
#define SPEED_THRESHOLD 30

Cursor cursor;

bool init_once = false;
bool lock_cursor_y = false;
bool lock_cursor_x = false;
uint8_t button_held_counter = 0;
float speed = 1.0f;
uint8_t watch_address_index = 3;
uint8_t offset_index = 2;
MemoryWatch Watches[MAX_WATCHES] = {};

// returns the width of the rendered string
float render_selected_number_selector(const char* str, float x, float y, size_t selected_char_index, size_t max_char, uint32_t color) {
    float pos = 0.0f;
    for (size_t i = 0; i <= max_char; ++i) {
        Font::gz_renderChar(str[i], x + pos, y, selected_char_index == i ? CURSOR_RGBA : color, g_drop_shadows);
        pos += Font::get_char_width(str[i]);
    }
    return pos;
}

float max_value_f(float a, float b) {
    return MAX(a, b);
}

void render_memory_lines(MemoryWatch Watches[MAX_WATCHES], Cursor cursor) {
    const float watch_x_pos_x_offset = WATCH_ADDRESS_X_OFFSET + max_value_f(Font::get_chars_width("Address"), Font::get_chars_width("0x80000000")) + 5.0f;
    const float watch_y_pos_x_offset = watch_x_pos_x_offset + max_value_f(Font::get_chars_width("X"), Font::get_chars_width("<000>")) + 5.0f;
    const float watch_hex_x_offset = watch_y_pos_x_offset + max_value_f(Font::get_chars_width("Y"), Font::get_chars_width("<000>")) + 5.0f;
    const float watch_type_x_offset = watch_hex_x_offset + max_value_f(Font::get_chars_width("Hex"), Font::get_chars_width("<false>")) + 5.0f;
    const float watch_offset_x_offset = watch_type_x_offset + max_value_f(Font::get_chars_width("Type"), Font::get_chars_width("<u32>")) + 5.0f;
    const float watch_visible_x_offset = watch_offset_x_offset + max_value_f(Font::get_chars_width("Offset"), Font::get_chars_width("0x0000")) + 5.0f;

    Font::gz_renderChars("Address", WATCH_ADDRESS_X_OFFSET, 60.0f, WHITE_RGBA, g_drop_shadows);
    Font::gz_renderChars("X", watch_x_pos_x_offset, 60.0f, WHITE_RGBA, g_drop_shadows);
    Font::gz_renderChars("Y", watch_y_pos_x_offset, 60.0f, WHITE_RGBA, g_drop_shadows);
    Font::gz_renderChars("Hex", watch_hex_x_offset, 60.0f, WHITE_RGBA, g_drop_shadows);
    Font::gz_renderChars("Type", watch_type_x_offset, 60.0f, WHITE_RGBA, g_drop_shadows);
    Font::gz_renderChars("Offset", watch_offset_x_offset, 60.0f, WHITE_RGBA, g_drop_shadows);
    Font::gz_renderChars("Visible", watch_visible_x_offset, 60.0f, WHITE_RGBA, g_drop_shadows);
    for (int i = 0; i < MAX_WATCHES; i++) {
#define LINE_Y_OFFSET (80.0f + (i * 20.0f))
        char watch_address[11];
        char watch_x[8];
        char watch_y[8];
        char watch_hex[8];
        char watch_type[6];
        char watch_offset[7];
        char watch_visible[4];

        tp_sprintf(watch_address, "0x%08X", Watches[i].address);
        tp_sprintf(watch_x, "%.0f", Watches[i].x);
        tp_sprintf(watch_y, "%.0f", Watches[i].y);
        tp_sprintf(watch_hex, "%s", Watches[i].hex ? "true" : "false");
        switch (Watches[i].type) {
            case u8: {
                tp_sprintf(watch_type, "u8");
                break;
            }
            case u16: {
                tp_sprintf(watch_type, "u16");
                break;
            }
            case u32: {
                tp_sprintf(watch_type, "u32");
                break;
            }
            case i8: {
                tp_sprintf(watch_type, "i8");
                break;
            }
            case i16: {
                tp_sprintf(watch_type, "i16");
                break;
            }
            case i32: {
                tp_sprintf(watch_type, "i32");
                break;
            }

            case f32: {
                tp_sprintf(watch_type, "f32");
                break;
            }
            case string: {
                tp_sprintf(watch_type, "str");
            }
        }
        tp_sprintf(watch_offset, "0x%04X", Watches[i].offset);
        tp_sprintf(watch_visible, "%s", Watches[i].visible ? "[X]" : "[ ]");

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
                            if (watch_address_index == 3) {
                                Watches[i].address = 0x81FFFFFF;
                            }
                            if (watch_address_index <= 9 && watch_address_index > 3) {
                                Watches[i].address += 1 << ((9 - watch_address_index) * 4);
                            }
                            if (Watches[i].address > 0x81FFFFFF) {
                                Watches[i].address = 0x81FFFFFF;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_DOWN)) {
                            if (watch_address_index <= 9 && watch_address_index >= 3) {
                                Watches[i].address -= 1 << ((9 - watch_address_index) * 4);
                            }
                            if (Watches[i].address < 0x80000000) {
                                Watches[i].address = 0x80000000;
                            }
                        }

                        render_selected_number_selector(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, watch_address_index, 9, WHITE_RGBA);
                    } else {
                        Font::gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    Font::gz_renderChars(watch_x, watch_x_pos_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_y, watch_y_pos_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_hex, watch_hex_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_type, watch_type_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_offset, watch_offset_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_visible, watch_visible_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
                case WatchX: {
                    if (Watches[i].value_selected) {
                        if (button_is_pressed(Controller::DPAD_RIGHT)) {
                            if (Watches[i].x >= 0.0f && Watches[i].x < 600.0f) {
                                Watches[i].x += speed;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_LEFT)) {
                            if (Watches[i].x > 0.0f && Watches[i].x <= 600.0f) {
                                Watches[i].x -= speed;
                            }
                        }
                        if(Watches[i].x < 0){
                            Watches[i].x = 0;
                        }
                        if(Watches[i].x > 600){
                            Watches[i].x = 600;
                        }
                        tp_sprintf(watch_x, "<%.0f>", Watches[i].x);
                        Font::gz_renderChars(watch_x, watch_x_pos_x_offset - 8.0f, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    } else {
                        Font::gz_renderChars(watch_x, watch_x_pos_x_offset, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    Font::gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_y, watch_y_pos_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_hex, watch_hex_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_type, watch_type_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_offset, watch_offset_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_visible, watch_visible_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
                case WatchY: {
                    if (Watches[i].value_selected) {
                        if (button_is_pressed(Controller::DPAD_RIGHT)) {
                            if (Watches[i].y >= 0.0f && Watches[i].y < 500.0f) {
                                Watches[i].y += speed;
                            }
                        }
                        if (button_is_pressed(Controller::DPAD_LEFT)) {
                            if (Watches[i].y > 0.0f && Watches[i].y <= 500.0f) {
                                Watches[i].y -= speed;
                            }
                        }
                        if(Watches[i].y < 0){
                            Watches[i].y = 0;
                        }
                        if(Watches[i].y > 500){
                            Watches[i].y = 500;
                        }
                        tp_sprintf(watch_y, "<%.0f>", Watches[i].y);
                        Font::gz_renderChars(watch_y, watch_y_pos_x_offset - 8.0f, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    } else {
                        Font::gz_renderChars(watch_y, watch_y_pos_x_offset, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    Font::gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_x, watch_x_pos_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_hex, watch_hex_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_type, watch_type_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_offset, watch_offset_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_visible, watch_visible_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);

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
                        tp_sprintf(watch_hex, "<%s>", Watches[i].hex ? "true" : "false");
                        Font::gz_renderChars(watch_hex, watch_hex_x_offset - 8.0f, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    } else {
                        Font::gz_renderChars(watch_hex, watch_hex_x_offset, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    Font::gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_x, watch_x_pos_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_y, watch_y_pos_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_type, watch_type_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_offset, watch_offset_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_visible, watch_visible_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
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
                                tp_sprintf(watch_type, "<u8>");
                                break;
                            }
                            case u16: {
                                tp_sprintf(watch_type, "<u16>");
                                break;
                            }
                            case u32: {
                                tp_sprintf(watch_type, "<u32>");
                                break;
                            }
                            case i8: {
                                tp_sprintf(watch_type, "<i8>");
                                break;
                            }
                            case i16: {
                                tp_sprintf(watch_type, "<i16>");
                                break;
                            }
                            case i32: {
                                tp_sprintf(watch_type, "<i32>");
                                break;
                            }

                            case f32: {
                                tp_sprintf(watch_type, "<f32>");
                                break;
                            }
                            case string: {
                                tp_sprintf(watch_type, "<str>");
                            }
                        }
                        Font::gz_renderChars(watch_type, watch_type_x_offset - 8.0f, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    } else {
                        Font::gz_renderChars(watch_type, watch_type_x_offset, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    Font::gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_x, watch_x_pos_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_y, watch_y_pos_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_hex, watch_hex_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_offset, watch_offset_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_visible, watch_visible_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
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
                        render_selected_number_selector(watch_offset, watch_offset_x_offset, LINE_Y_OFFSET, offset_index, 5, WHITE_RGBA);
                    } else {
                        Font::gz_renderChars(watch_offset, watch_offset_x_offset, LINE_Y_OFFSET, CURSOR_RGBA, g_drop_shadows);
                    }
                    Font::gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_x, watch_x_pos_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_y, watch_y_pos_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_hex, watch_hex_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_type, watch_type_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    Font::gz_renderChars(watch_visible, watch_visible_x_offset, LINE_Y_OFFSET, WHITE_RGBA, g_drop_shadows);
                    break;
                }
            }
        } else {
            Font::gz_renderChars(watch_address, WATCH_ADDRESS_X_OFFSET, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            Font::gz_renderChars(watch_x, watch_x_pos_x_offset, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            Font::gz_renderChars(watch_y, watch_y_pos_x_offset, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            Font::gz_renderChars(watch_hex, watch_hex_x_offset, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            Font::gz_renderChars(watch_type, watch_type_x_offset, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            Font::gz_renderChars(watch_offset, watch_offset_x_offset, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
            Font::gz_renderChars(watch_visible, watch_visible_x_offset, LINE_Y_OFFSET, (cursor.y == i ? CURSOR_RGBA : WHITE_RGBA), g_drop_shadows);
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

void WatchesMenu::render() {
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
            MenuRendering::set_menu(MN_MEMORY_INDEX);
            return;
        }
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == Controller::Pad::A && a_held == false) {
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
        MenuRendering::set_menu(MN_MEMORY_EDITOR_INDEX);
    }

    if (button_is_down(Controller::DPAD_RIGHT) || button_is_down(Controller::DPAD_LEFT)) {
        button_held_counter++;
        if (button_held_counter < SPEED_THRESHOLD) {
            speed = 1.0f;
        }
        if (button_held_counter > SPEED_THRESHOLD) {
            speed = 20.0f;
        }
        if(button_held_counter >= 60){
            button_held_counter = 60;
        }
    } else {
        button_held_counter = 0;
        speed = 1.0f;
    }

    Utilities::move_cursor(cursor, MAX_WATCHES, WATCH_COLUMNS, lock_cursor_x, lock_cursor_y);
    Font::gz_renderChars("Press z to enable/disable watch. Y to jump to editor address", 25.0f, 440.f, 0xFFFFFFFF, g_drop_shadows);
    render_memory_lines(Watches, cursor);
};