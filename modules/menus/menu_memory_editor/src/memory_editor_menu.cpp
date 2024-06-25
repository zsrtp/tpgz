#include "menus/menu_memory_editor/include/memory_editor_menu.h"
#include <cstdio>
#include "memory_editor.h"
#include "settings.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define MAX_DISPLAY_LINES 15
#define MAX_ADDRESS (0x81800000 - MAX_DISPLAY_LINES * line_length)
#define WHITE_RGBA 0xFFFFFFFF
#define ADDRESS_RGBA 0xBABABAFF
#define LINE_X_OFFSET 20.0f
#define LINE_BYTE_OFFSET 100.0f

#ifdef GCN_PLATFORM
#define LINE_SIZE_BTN (GZPad::Y)
#define LINE_SIZE_TEXT "Y"
#else
#define LINE_SIZE_BTN (GZPad::MINUS)
#define LINE_SIZE_TEXT "-"
#endif

MemoryEditorMenu::MemoryEditorMenu(Cursor& cursor) : Menu(cursor) {}

MemoryEditorMenu::~MemoryEditorMenu() {}

bool l_idxSelected = false;
uint8_t l_idxPlace = 0;
uint8_t l_byteIdx = 0;
uint8_t l_cycleR = 0;
uint8_t l_cycleG = 0;
uint8_t l_cycleB = 0;

void MemoryEditorMenu::drawMemEditor() {
    char index[9] = {0};
    snprintf(index, sizeof(index), "%08X", g_memoryEditor_addressIndex);

    if (l_idxSelected) {
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            if (l_idxPlace == line_length - 1) {
                l_idxPlace = 0;
            } else if (l_idxPlace >= 0 && l_idxPlace < line_length) {
                l_idxPlace++;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            if (l_idxPlace == 0) {
                l_idxPlace = line_length - 1;
            } else if (l_idxPlace >= 0 && l_idxPlace < line_length) {
                l_idxPlace--;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
            if (l_idxPlace == 0) {
                g_memoryEditor_addressIndex = MAX_ADDRESS;
            } else {
                g_memoryEditor_addressIndex += (0x10000000 >> (l_idxPlace * 4));
            }
            if (g_memoryEditor_addressIndex > MAX_ADDRESS) {
                g_memoryEditor_addressIndex = MAX_ADDRESS;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
            g_memoryEditor_addressIndex -= (0x10000000 >> (l_idxPlace * 4));
            if (g_memoryEditor_addressIndex < 0x80000000) {
                g_memoryEditor_addressIndex = 0x80000000;
            }
        }
        GZ_drawSelectChar(index, LINE_X_OFFSET, 80.0f, l_idxPlace, 7, WHITE_RGBA);
    } else {
        GZ_drawText(index, LINE_X_OFFSET, 80.0f, (cursor.y == 0 ? CURSOR_RGBA : WHITE_RGBA),
                    GZ_checkDropShadows());
    }

    if (cursor.y > 0 && !cursor.lock_x) {
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            if (l_byteIdx == 0) {
                l_byteIdx = line_length - 1;
            } else if (l_byteIdx >= 0 && l_byteIdx < line_length) {
                l_byteIdx--;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            if (l_byteIdx == line_length - 1) {
                l_byteIdx = 0;
            } else if (l_byteIdx >= 0 && l_byteIdx < line_length) {
                l_byteIdx++;
            }
        }
    }

    for (uint8_t i = 0; i < MAX_DISPLAY_LINES; i++) {
        float y_offset;
        y_offset = ((100.0f) + (i * 20.0f));

        char address[10];
        char b[line_length][3];
        char c[line_length][3];

        snprintf(address, sizeof(address), "%08X ", g_memoryEditor_addressIndex + (i * line_length));
        for (uint8_t k = 0; k < line_length; ++k) {
            snprintf(b[k], sizeof(b[k]), "%02X", *(uint8_t*)(g_memoryEditor_addressIndex + (i * line_length) + k));
            snprintf(c[k], sizeof(c[k]), "%c", *(uint8_t*)(g_memoryEditor_addressIndex + (i * line_length) + k));
        }

        float address_offset = Font::getStrWidth(address) + LINE_X_OFFSET;
        float b_offset = Font::getStrWidth("00") + (line_length == 8 ? Font::getCharWidth(' ') : 0.0f);
        float chars_offset = address_offset + b_offset * line_length + Font::getStrWidth("  ");
        float c_offset = Font::getMaxCharRangeWidth('A', 'Z');
        if (cursor.y == (i + 1) && cursor.lock_x && cursor.lock_y) {
            if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
                *(uint8_t*)((g_memoryEditor_addressIndex + (i * line_length)) + l_byteIdx) += 0x1;
            }
            if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
                *(uint8_t*)((g_memoryEditor_addressIndex + (i * line_length)) + l_byteIdx) -= 0x1;
            }
            if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                *(uint8_t*)((g_memoryEditor_addressIndex + (i * line_length)) + l_byteIdx) += 0x10;
            }
            if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                *(uint8_t*)((g_memoryEditor_addressIndex + (i * line_length)) + l_byteIdx) -= 0x10;
            }
        }

        uint32_t mem_cursor_color;
        // cycle cursor color when value selected
        if (cursor.lock_x && cursor.lock_y) {
            if (l_cycleR < 0x00A0 && (l_cycleG == 0x0000 && l_cycleB == 0x0000)) {
                l_cycleR += 0x0001;
            } else if (l_cycleG < 0x00A0 && (l_cycleB == 0x0000 && l_cycleR == 0x00A0)) {
                l_cycleG += 0x0001;
            } else if (l_cycleB < 0x00A0 && (l_cycleG == 0x00A0 && l_cycleR == 0x00A0)) {
                l_cycleB += 0x0001;
            } else if (l_cycleR > 0x0000 && (l_cycleG == 0x00A0 && l_cycleB == 0x00A0)) {
                l_cycleR -= 0x0001;
            } else if (l_cycleG > 0x0000 && (l_cycleB == 0x00A0 && l_cycleR == 0x0000)) {
                l_cycleG -= 0x0001;
            } else {
                l_cycleB -= 0x0001;
            }
            mem_cursor_color = (l_cycleR << 24) | (l_cycleG << 16) | (l_cycleB << 8) | 0xFF;
        } else {
            mem_cursor_color = CURSOR_RGBA;
        }

        GZ_drawText(address, LINE_X_OFFSET, y_offset,
                    (cursor.y == (i + 1) ? CURSOR_RGBA : ADDRESS_RGBA), GZ_checkDropShadows());
        for (uint8_t k = 0; k < line_length; ++k) {
            float middle_offset = k < line_length / 2 ? 0.0f : Font::getCharWidth(' ');
            GZ_drawText(b[k], address_offset + b_offset * k + middle_offset, y_offset,
                        (l_byteIdx == k && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                        GZ_checkDropShadows());
            // The text version of it
            GZ_drawText(c[k], chars_offset + c_offset * k + middle_offset, y_offset,
                        (l_byteIdx == k && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                        GZ_checkDropShadows());
        }
    }
}

void MemoryEditorMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        if (l_idxSelected) {
            cursor.lock_y = false;
            l_idxSelected = false;
        } else if (cursor.lock_x || cursor.lock_y) {
            cursor.lock_x = false;
            cursor.lock_y = false;
        } else {
            g_menuMgr->pop();
            return;
        }
    }

    if (GZ_getButtonTrig(LINE_SIZE_BTN)) {
        line_length = line_length == 8 ? 16 : 8;
        if (g_memoryEditor_addressIndex > MAX_ADDRESS) {
            g_memoryEditor_addressIndex = MAX_ADDRESS;
        }
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case 0:
            cursor.lock_y = true;
            l_idxSelected = true;
            break;
        }

        if (cursor.y > 0) {
            cursor.lock_x = true;
            cursor.lock_y = true;
        }
    }

    cursor.move(line_length, 1 + MAX_DISPLAY_LINES);
    GZ_drawText("DPad to move/modify value, A/B to (de)select value;" LINE_SIZE_TEXT " toggle line size", 25.0f, 440.f, WHITE_RGBA,
                GZ_checkDropShadows());
    drawMemEditor();
}