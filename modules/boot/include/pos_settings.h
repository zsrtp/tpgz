#pragma once

#include "settings.h"
#include "libtp_c/include/dolphin/mtx/vec.h"

#define SPRITES_AMNT 12

enum SpritesIndex {
    MENU_INDEX,
    VIEWER_INDEX,
    DEBUG_INFO_INDEX,
    STAGE_INFO_INDEX,
    TIMER_SPR_INDEX,
    LOAD_TIMER_SPR_INDEX,
    IGT_TIMER_SPR_INDEX,
    FIFO_SPR_INDEX,
    HEAP_INFO_INDEX,
    MASH_INFO_INDEX,
    TRANSFORM_IND_INDEX,
    DISPLACEMENT_INDEX
};

inline Vec2 GZ_getSpriteOffset(GZSettingID sprIdx) {
    return GZStng_getData(sprIdx, Vec2{0.0f, 0.0f});
}
