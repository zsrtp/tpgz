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

    if (l_creditsHeart.loadCode == TexCode::TEX_OK) {
            Draw::drawRect(0xFFFFFFFF, {318.0f, 65.0f},{30 * (isWidescreen ? 0.75f : 1.0f), 30}, &l_creditsHeart._texObj);
        }

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    
    Font::GZ_drawStr("tpgz - the twilight princess practice rom", 25.0f, 60.0f, 0xFFFFFFFF, g_dropShadows, 25.0f);
    Font::GZ_drawStr("made with", 175.0f, 90.0f, 0xFFFFFFFF, g_dropShadows, 25.0f);
    Font::GZ_drawStr("by", 360.0f, 90.0f, 0xFFFFFFFF, g_dropShadows, 25.0f);

    Font::GZ_drawStr("kipcode", 135.0f, 110.0f, 0xFFFFFFFF, g_dropShadows, 20.0f);  
    Font::GZ_drawStr("pheenoh", 265.0f, 110.0f, 0xFFFFFFFF, g_dropShadows, 20.0f);
    Font::GZ_drawStr("taka", 390.0f, 110.0f, 0xFFFFFFFF, g_dropShadows, 20.0f);

    Font::GZ_drawStr("special thanks", 175.0f, 170.0f, 0xFFFFFFFF, g_dropShadows, 25.0f);
    Font::GZ_drawStr("tp decomp team", 85.0f, 190.0f, 0xFFFFFFFF, g_dropShadows, 17.0f);
    Font::GZ_drawStr("tp speedrun community", 345.0f, 190.0f, 0xFFFFFFFF, g_dropShadows, 17.0f);
    Font::GZ_drawStr("c_midnight", 85.0f, 210.0f, 0xFFFFFFFF, g_dropShadows, 17.0f);
    Font::GZ_drawStr("cryze", 245.0f, 210.0f, 0xFFFFFFFF, g_dropShadows, 17.0f);
    Font::GZ_drawStr("ferdi265", 345.0f, 210.0f, 0xFFFFFFFF, g_dropShadows, 17.0f);
    Font::GZ_drawStr("jdflyer", 85.0f, 230.0f, 0xFFFFFFFF, g_dropShadows, 17.0f);
    Font::GZ_drawStr("icogn", 245.0f, 230.0f, 0xFFFFFFFF, g_dropShadows, 17.0f);
    Font::GZ_drawStr("lunarsoap", 345.0f, 230.0f, 0xFFFFFFFF, g_dropShadows, 17.0f);
    Font::GZ_drawStr("zephiles", 245.0f, 250.0f, 0xFFFFFFFF, g_dropShadows, 17.0f);
}
