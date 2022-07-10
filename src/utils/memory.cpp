#include "utils/memory.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/memory_menu.h"
#include "menus/settings_menu.h"
#include "libtp_c/include/JSystem/JKernel/JKRExpHeap.h"

void GZ_drawWatches() {
    for (int i = 0; i < MAX_WATCHES; i++) {
        if (g_watches[i].visible) {
            char rendered_value[8];
            switch (g_watches[i].type) {
            case u32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%08X" : "%u",
                               *(uint32_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%08X" : "%u",
                               *(uint32_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                     g_dropShadows);
                break;
            case u16:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%04X" : "%u",
                               *(uint16_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%04X" : "%u",
                               *(uint16_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                     g_dropShadows);
                break;
            case u8:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%02X" : "%u",
                               *(uint8_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%02X" : "%u",
                               *(uint8_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                     g_dropShadows);
                break;
            case i32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%08X" : "%i",
                               *(int32_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%08X" : "%i",
                               *(int32_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                     g_dropShadows);
                break;
            case i16:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%04X" : "%i",
                               *(int16_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%04X" : "%i",
                               *(int16_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                     g_dropShadows);
                break;
            case i8:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%02X" : "%i",
                               *(int8_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tp_sprintf(rendered_value, g_watches[i].hex ? "%02X" : "%i",
                               *(int8_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                     g_dropShadows);
                break;
            case f32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tp_sprintf(rendered_value, "%.2f",
                               *(float*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tp_sprintf(rendered_value, "%.2f", *(float*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                     g_dropShadows);
                break;
            case string:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tp_sprintf(rendered_value, "%s",
                               (char*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tp_sprintf(rendered_value, "%s", (char*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                     g_dropShadows);
                break;
            }
        }
    }
}

void GZ_drawHeapInfo() {
    if (zeldaHeap && gameHeap && archiveHeap) {
        uint32_t zeldaFree = JKRHeap__getFreeSize(zeldaHeap);
        uint32_t zeldaTotal = JKRHeap__getTotalFreeSize(zeldaHeap);
        uint32_t gameFree = JKRHeap__getFreeSize(gameHeap);
        uint32_t gameTotal = JKRHeap__getTotalFreeSize(gameHeap);
        uint32_t archiveFree = JKRHeap__getFreeSize(archiveHeap);
        uint32_t archiveTotal = JKRHeap__getTotalFreeSize(archiveHeap);

        Font::GZ_drawStr("-- Heap Free / Total Free (KB) --", 145.0f, 25.0f, 0xFFFFFFFF, g_dropShadows);
        char zelBuf[22];
        tp_sprintf(zelBuf, "  Zelda %5d / %5d", zeldaFree >> 10, zeldaTotal >> 10);
        char gameBuf[22];
        tp_sprintf(gameBuf, "   Game %5d / %5d", gameFree >> 10, gameTotal >> 10);
        char arcBuf[22];
        tp_sprintf(arcBuf, "Archive %5d / %5d", archiveFree >> 10, archiveTotal >> 10);

        Font::GZ_drawStr(zelBuf, 200.0f, 45.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(gameBuf, 200.0f, 65.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(arcBuf, 200.0f, 85.0f, 0xFFFFFFFF, g_dropShadows);
    }   
}