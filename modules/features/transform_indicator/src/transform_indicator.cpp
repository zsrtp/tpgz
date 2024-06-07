#include "transform_indicator.h"
#include <cstdio>
#include "pos_settings.h"
#include "tools.h"
#include "rels/include/defines.h"
#include "utils/texture.h"
#include "utils/draw.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/d/a/d_a_alink.h"

extern daMidna_c m_midnaActor;

#ifdef WII_PLATFORM
extern bool isWidescreen;
#define IS_WIDESCREEN isWidescreen
#else
#define IS_WIDESCREEN (false)
#endif

namespace TransformIndicator {
    Texture l_humanTex;
    Texture l_wolfTex;
}

void drawTexture(GXTexObj tex, bool greyed) {
    Draw::drawRect(greyed ? 0x3f3f3f7f : 0xFFFFFFFF, g_spriteOffsets[TRANSFORM_IND_INDEX],
                    {30 * (IS_WIDESCREEN ? 0.75f : 1.0f), 30}, &tex);
}

KEEP_FUNC void TransformIndicator::draw() {
    if (dComIfGs_getTransformStatus() == 0) {
        if (l_wolfTex.loadCode == TexCode::TEX_OK) {
            // TODO Grey out the icon if we can't transform into wolf
            drawTexture(l_wolfTex._texObj, true);
        }
    } else {
        if (l_humanTex.loadCode == TexCode::TEX_OK) {
            // TODO Grey out the icon if we can't transform into human
            drawTexture(l_humanTex._texObj, true);
        }
    }
}