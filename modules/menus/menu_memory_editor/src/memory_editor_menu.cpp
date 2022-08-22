#include "menus/menu_memory_editor/include/memory_editor_menu.h"
#include <cstdio>
#include "memory_editor.h"
#include "settings.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define MAX_DISPLAY_LINES 15
#define WHITE_RGBA 0xFFFFFFFF
#define ADDRESS_RGBA 0xBABABAFF
#define LINE_X_OFFSET 20.0f
#define LINE_BYTE_OFFSET 100.0f

MemoryEditorMenu::MemoryEditorMenu(Cursor& cursor) : Menu(), cursor(cursor) {}

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
            if (l_idxPlace == 7) {
                l_idxPlace = 0;
            } else if (l_idxPlace >= 0 && l_idxPlace < 8) {
                l_idxPlace++;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            if (l_idxPlace == 0) {
                l_idxPlace = 7;
            } else if (l_idxPlace >= 0 && l_idxPlace < 8) {
                l_idxPlace--;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
            if (l_idxPlace == 0) {
                g_memoryEditor_addressIndex = 0x817FFF88;
            } else {
                g_memoryEditor_addressIndex += (0x10000000 >> (l_idxPlace * 4));
            }
            if (g_memoryEditor_addressIndex > 0x817FFF88) {
                g_memoryEditor_addressIndex = 0x817FFF88;
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
                l_byteIdx = 7;
            } else if (l_byteIdx >= 0 && l_byteIdx < 8) {
                l_byteIdx--;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            if (l_byteIdx == 7) {
                l_byteIdx = 0;
            } else if (l_byteIdx >= 0 && l_byteIdx < 8) {
                l_byteIdx++;
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

        snprintf(address, sizeof(address), "%08X ", g_memoryEditor_addressIndex + (i * 8));
        snprintf(b0, sizeof(b0), "%02X", *(uint8_t*)(g_memoryEditor_addressIndex + (i * 8)));
        snprintf(b1, sizeof(b1), "%02X", *(uint8_t*)((g_memoryEditor_addressIndex + (i * 8)) + 1));
        snprintf(b2, sizeof(b2), "%02X", *(uint8_t*)((g_memoryEditor_addressIndex + (i * 8)) + 2));
        snprintf(b3, sizeof(b3), "%02X", *(uint8_t*)((g_memoryEditor_addressIndex + (i * 8)) + 3));
        snprintf(b4, sizeof(b4), "%02X", *(uint8_t*)((g_memoryEditor_addressIndex + (i * 8)) + 4));
        snprintf(b5, sizeof(b5), "%02X", *(uint8_t*)((g_memoryEditor_addressIndex + (i * 8)) + 5));
        snprintf(b6, sizeof(b6), "%02X", *(uint8_t*)((g_memoryEditor_addressIndex + (i * 8)) + 6));
        snprintf(b7, sizeof(b7), "%02X", *(uint8_t*)((g_memoryEditor_addressIndex + (i * 8)) + 7));

        float address_offset = Font::getStrWidth(address) + LINE_X_OFFSET;
        float b_offset = Font::getStrWidth(" 00");
        if (cursor.y == (i + 1) && cursor.lock_x && cursor.lock_y) {
            if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
                *(uint8_t*)((g_memoryEditor_addressIndex + (i * 8)) + l_byteIdx) += 0x1;
            }
            if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
                *(uint8_t*)((g_memoryEditor_addressIndex + (i * 8)) + l_byteIdx) -= 0x1;
            }
            if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                *(uint8_t*)((g_memoryEditor_addressIndex + (i * 8)) + l_byteIdx) += 0x10;
            }
            if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                *(uint8_t*)((g_memoryEditor_addressIndex + (i * 8)) + l_byteIdx) -= 0x10;
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
        GZ_drawText(b0, address_offset, y_offset,
                    (l_byteIdx == 0 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                    GZ_checkDropShadows());
        GZ_drawText(b1, address_offset + b_offset * 1, y_offset,
                    (l_byteIdx == 1 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                    GZ_checkDropShadows());
        GZ_drawText(b2, address_offset + b_offset * 2, y_offset,
                    (l_byteIdx == 2 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                    GZ_checkDropShadows());
        GZ_drawText(b3, address_offset + b_offset * 3, y_offset,
                    (l_byteIdx == 3 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                    GZ_checkDropShadows());
        GZ_drawText(b4, address_offset + b_offset * 4, y_offset,
                    (l_byteIdx == 4 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                    GZ_checkDropShadows());
        GZ_drawText(b5, address_offset + b_offset * 5, y_offset,
                    (l_byteIdx == 5 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                    GZ_checkDropShadows());
        GZ_drawText(b6, address_offset + b_offset * 6, y_offset,
                    (l_byteIdx == 6 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                    GZ_checkDropShadows());
        GZ_drawText(b7, address_offset + b_offset * 7, y_offset,
                    (l_byteIdx == 7 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                    GZ_checkDropShadows());
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

    cursor.move(8, 1 + MAX_DISPLAY_LINES);
    GZ_drawText("DPad to move/modify value, A/B to (de)select value", 25.0f, 440.f, WHITE_RGBA,
                GZ_checkDropShadows());
    drawMemEditor();
}