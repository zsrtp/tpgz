#include "menus/menu_glitchless_saves/include/menu_glitchless_saves.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC GlitchlessSavesMenu::GlitchlessSavesMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"faron twilight", GL_FARON_TWILIGHT_INDEX, "Faron Twilight tears"},
          {"forest temple", GL_FOREST_INDEX, "The Forest Temple segment"},
          {"diababa", GL_DIABABA_INDEX, "Forest Temple boss"},
          {"eldin twilight", GL_ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
          {"post twilight", GL_POST_TWILIGHT_INDEX, "After Eldin Twilight"},
          {"king bulblin 1", GL_KB1_INDEX, "King Bulblin 1 fight"},
          {"goron mines", GL_MINES_INDEX, "The Goron Mines segment"},
          {"dangoro", GL_DANGORO_INDEX, "Goron Mines miniboss"},
          {"lanayru twilight", GL_LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
          {"wagon escort", GL_ESCORT_INDEX, "Telma wagon escort"},
          {"lakebed", GL_LAKEBED_INDEX, "The Lakebed Temple segment"},
          {"deku toad", GL_TOAD_INDEX, "Lakebed Temple miniboss"},
          {"mdh", GL_MDH_INDEX, "Midna's Desperate Hour segment"},
          {"post mdh", GL_POST_MDH_INDEX, "After Midna's Desperate Hour"},
          {"post ms", GL_POST_MS_INDEX, "After Master Sword"},
          {"arbiter's grounds", GL_AG_INDEX, "The Arbiter's Grounds segment"},
          {"death sword", GL_DEATH_SWORD_INDEX, "Arbiter's Grounds miniboss"},
          {"post ag", GL_POST_AG_INDEX, "After Arbiter's Grounds"},
          {"snowpeak", GL_SPR_INDEX, "The Snowpeak Ruins segment"},
          {"darkhammer", GL_DARKHAMMER_INDEX, "Snowpeak Ruins miniboss"},
          {"post spr", GL_POST_SPR_INDEX, "After Snowpeak Ruins"},
          {"temple of time", GL_TOT_INDEX, "The Temple of Time segment"},
          {"tot darknut", GL_DARKNUT_INDEX, "Temple of Time miniboss"},
          {"post tot", GL_POST_TOT_INDEX, "After Temple of Time"},
          {"hugo archery", GL_HV_INDEX, "Archery in Hidden Village"},
          {"city", GL_CITY_INDEX, "The City in the Sky segment"},
          {"aeralfos", GL_AERALFOS_INDEX, "The City in the Sky miniboss"},
          {"palace", GL_PALACE_INDEX, "The Palace of Twilight segment"},
          {"zant", GL_ZANT_INDEX, "Palace of Twilight boss"},
          {"hyrule castle", GL_HYRULE_INDEX, "The Hyrule Castle segment"},
          {"beast ganon", GL_BEAST_GANON_INDEX, "The Beast Ganon fight"},
          {"horseback ganon", GL_HORSEBACK_GANON_INDEX, "The Horseback Ganondorf fight"},
      } {}

GlitchlessSavesMenu::~GlitchlessSavesMenu() {}

void GlitchlessSavesMenu::draw() {
    special GlitchlessSpecials[GL_SPECIALS_AMNT] = {
        special(GL_DANGORO_INDEX, nullptr, SaveMngSpecial_Dangoro),
        special(GL_DARKHAMMER_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(GL_PALACE_INDEX, SaveMngSpecial_Palace1, nullptr),
    };

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        SaveManager::triggerLoad(cursor.y, "glitchless", GlitchlessSpecials, GL_SPECIALS_AMNT);
        g_menuMgr->hide();
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}