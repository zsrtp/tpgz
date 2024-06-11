#include "menus/menu_credits/include/credits_menu.h"
#include <cstdio>
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/d/meter/d_meter_HIO.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "utils/draw.h"

#ifdef WII_PLATFORM
extern bool isWidescreen;
#else
#define isWidescreen (false)
#endif

KEEP_FUNC CreditsMenu::CreditsMenu(Cursor& cursor) : Menu(cursor) {}

CreditsMenu::~CreditsMenu() {}

Texture l_creditsHeart;

void CreditsMenu::draw() {
    if (l_creditsHeart.loadCode == TexCode::TEX_UNLOADED) {
        load_texture("/tpgz/tex/heart.tex", &l_creditsHeart);
    }

    float scale = isWidescreen ? 0.75f : 1.0f;
    float offset = isWidescreen ? 100.0f : 0.0f;

    if (l_creditsHeart.loadCode == TexCode::TEX_OK) {
            Draw::drawRect(0xFFFFFFFF, {offset + 315.0f * scale, 65.0f},{30 * scale, 30}, &l_creditsHeart._texObj);
        }

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    Font::GZ_drawStr("tpgz - the twilight princess practice rom", offset + 25.0f * scale, 60.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 25.0f);
    Font::GZ_drawStr("made with", offset + 175.0f * scale, 90.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 25.0f);
    Font::GZ_drawStr("by", offset + 360.0f * scale, 90.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 25.0f);

    Font::GZ_drawStr("kipcode", offset + 135.0f * scale, 110.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 20.0f);  
    Font::GZ_drawStr("pheenoh", offset + 265.0f * scale, 110.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 20.0f);
    Font::GZ_drawStr("taka", offset + 390.0f * scale, 110.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 20.0f);

    Font::GZ_drawStr("special thanks", offset + 175.0f * scale, 170.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 25.0f);
    Font::GZ_drawStr("tp decomp team", offset + 85.0f * scale, 190.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 17.0f);
    Font::GZ_drawStr("tp speedrun community", offset + 345.0f * scale, 190.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 17.0f);
    Font::GZ_drawStr("c_midnight", offset + 85.0f * scale, 210.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 17.0f);
    Font::GZ_drawStr("cryze", offset + 245.0f * scale, 210.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 17.0f);
    Font::GZ_drawStr("jdflyer", offset + 345.0f * scale, 210.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 17.0f);
    Font::GZ_drawStr("icogn", offset + 85.0f * scale, 230.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 17.0f);
    Font::GZ_drawStr("lunarsoap", offset + 245.0f * scale, 230.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 17.0f);
    Font::GZ_drawStr("zephiles", offset + 345.0f * scale, 230.0f, 0xFFFFFFFF, GZ_checkDropShadows(), 17.0f);
}
