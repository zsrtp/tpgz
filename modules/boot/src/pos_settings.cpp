#include "pos_settings.h"
#include "rels/include/defines.h"

KEEP_VAR Vec2 g_spriteOffsets[SPRITES_AMNT];

KEEP_FUNC void GZ_PosSettings_initDefaults() {
#ifdef GCN_PLATFORM
    g_spriteOffsets[VIEWER_INDEX] = {220.f, 380.f};
#elif defined(WII_PLATFORM)
    g_spriteOffsets[VIEWER_INDEX] = {250.f, 360.f};
#endif
    g_spriteOffsets[MENU_INDEX] = {25.f, 60.f};
    g_spriteOffsets[DEBUG_INFO_INDEX] = {450.0f, 200.f};
    g_spriteOffsets[TIMER_SPR_INDEX] = {525.0f, 420.f};
    g_spriteOffsets[LOAD_TIMER_SPR_INDEX] = {525.0f, 30.f};
    g_spriteOffsets[IGT_TIMER_SPR_INDEX] = {35.0f, 30.f};
    g_spriteOffsets[FIFO_SPR_INDEX] = {5.0f, 440.f};
    g_spriteOffsets[HEAP_INFO_INDEX] = {145.0f, 25.0f};
}
