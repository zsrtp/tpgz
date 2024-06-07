#pragma once

#include "settings.h"
#include "libtp_c/include/dolphin/mtx/vec.h"

#define SPRITES_AMNT 10
enum SpritesIndex {
    MENU_INDEX,
    VIEWER_INDEX,
    DEBUG_INFO_INDEX,
    TIMER_SPR_INDEX,
    LOAD_TIMER_SPR_INDEX,
    IGT_TIMER_SPR_INDEX,
    FIFO_SPR_INDEX,
    HEAP_INFO_INDEX,
    MASH_INFO_INDEX,
    TRANSFORM_IND_INDEX,
};

inline Vec2 GZ_getSpriteOffset(GZSettingID sprIdx) {
    auto* stng = GZStng_getSetting(sprIdx);
    return stng ? *(Vec2*)stng->data : Vec2{0.0f, 0.0f};
}
