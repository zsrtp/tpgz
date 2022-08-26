#include "utils/memory.h"
#include <cstdio>
#include "watches.h"
#include "pos_settings.h"
#include "settings.h"
#include "libtp_c/include/JSystem/JKernel/JKRExpHeap.h"
#include "libtp_c/include/m_Do/m_Do_ext.h"
#include "rels/include/defines.h"
#include "tools.h"

KEEP_FUNC void GZ_drawWatches() {
    for (int i = 0; i < MAX_WATCHES; i++) {
        if (g_watches[i].visible) {
            char rendered_value[9];
            switch (g_watches[i].type) {
            case u32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%08X" : "%u",
                             *(uint32_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%08X" : "%u", *(uint32_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case u16:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%04X" : "%u",
                             *(uint16_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%04X" : "%u", *(uint16_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case u8:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%02X" : "%u",
                             *(uint8_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%02X" : "%u", *(uint8_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case i32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%08X" : "%i",
                             *(int32_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%08X" : "%i", *(int32_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case i16:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%04X" : "%i",
                             *(int16_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%04X" : "%i", *(int16_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case i8:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%02X" : "%i",
                             *(int8_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value),
                             g_watches[i].hex ? "%02X" : "%i", *(int8_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case f32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value), "%.2f",
                             *(float*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value), "%.2f",
                             *(float*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case string:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    snprintf(rendered_value, sizeof(rendered_value), "%s",
                             (char*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    snprintf(rendered_value, sizeof(rendered_value), "%s",
                             (char*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            }
        }
    }
}

KEEP_FUNC void GZ_drawHeapInfo() {
    if (!g_tools[HEAP_DEBUG_INDEX].active) {
        return;
    }
    if (m_Do_ext::zeldaHeap && m_Do_ext::gameHeap && m_Do_ext::archiveHeap) {
        uint32_t zeldaFree = JKRHeap__getFreeSize(m_Do_ext::zeldaHeap);
        uint32_t zeldaTotal = JKRHeap__getTotalFreeSize(m_Do_ext::zeldaHeap);
        uint32_t gameFree = JKRHeap__getFreeSize(m_Do_ext::gameHeap);
        uint32_t gameTotal = JKRHeap__getTotalFreeSize(m_Do_ext::gameHeap);
        uint32_t archiveFree = JKRHeap__getFreeSize(m_Do_ext::archiveHeap);
        uint32_t archiveTotal = JKRHeap__getTotalFreeSize(m_Do_ext::archiveHeap);

        Vec2 pos = {0.f, 0.f};
        pos.x += g_spriteOffsets[HEAP_INFO_INDEX].x;
        pos.y += g_spriteOffsets[HEAP_INFO_INDEX].y;

        Font::GZ_drawStr("-- Heap Free / Total Free (KB) --", pos.x, pos.y, 0xFFFFFFFF,
                         g_dropShadows);
        char zelBuf[22];
        snprintf(zelBuf, sizeof(zelBuf), "  Zelda %5d / %5d", zeldaFree >> 10, zeldaTotal >> 10);
        char gameBuf[22];
        snprintf(gameBuf, sizeof(gameBuf), "   Game %5d / %5d", gameFree >> 10, gameTotal >> 10);
        char arcBuf[22];
        snprintf(arcBuf, sizeof(arcBuf), "Archive %5d / %5d", archiveFree >> 10,
                 archiveTotal >> 10);

        Font::GZ_drawStr(zelBuf, pos.x + 55.0f, pos.y + 20.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(gameBuf, pos.x + 55.0f, pos.y + 40.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(arcBuf, pos.x + 55.0f, pos.y + 60.0f, 0xFFFFFFFF, g_dropShadows);
    }
}