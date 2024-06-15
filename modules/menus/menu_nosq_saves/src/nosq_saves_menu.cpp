#include "menus/menu_nosq_saves/include/nosq_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC NoSQSavesMenu::NoSQSavesMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"bokoblin push", NOSQ_BOKO_PUSH_INDEX, "Push Bokoblins to Trill"},
          {"sword and shield skip", NOSQ_HUGO_INDEX, "Hangin' with Hugo"},
          {"faron twilight", NOSQ_FARON_TWILIGHT_INDEX, "Faron Twilight segment"},
          // {"early master sword", NOSQ_EMS_INDEX, "Super Jump to Sacred Grove"},
          {"forest temple", NOSQ_FOREST_TEMPLE_INDEX, "The Forest Temple segment"},
          {"early boomerang", NOSQ_EARLY_RANG_INDEX, "Bridge clips to get boomerang early"},
          {"forest escape", NOSQ_FRST_ESCAPE_INDEX, "LJA over S.Faron exit trigger"},
          {"gorge void", NOSQ_GORGE_VOID_INDEX, "1 frame jump attack into Gorge"},
          {"rupee roll", NOSQ_RUPEE_ROLL_INDEX, "Rupee Roll / Gorge Skip"},
          {"eldin twilight", NOSQ_ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
          // {"bomb house skip", NOSQ_BOMB_HOUSE_SKIP_INDEX, "Skip entering the Bomb House"},
          // {"post eldin", NOSQ_POST_ELDIN_INDEX, "Getting Iron Boots and going to lanayru"},
          {"lanayru gate clip", NOSQ_LANAYRU_GATE_CLIP_INDEX, "Gate Clip to Lanayru"},
          // {"kargorok flight", NOSQ_KARG_INDEX, "Clip OoB with trumpet bird"},
          {"lanayru twilight", NOSQ_LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
          // {"waterfall sidehop", NOSQ_WATERFALL_SIDEHOP_INDEX, "Waterfall sidehop after Rutela skip"},
          // {"boss bug", NOSQ_BOSS_BUG_INDEX, "Lanayru Twilight boss bug"},
          {"kb2 skip", NOSQ_KB2_SKIP_INDEX, "Clip to skip King Bulblin 2"},
          {"wagon escort", NOSQ_ESCORT_INDEX, "Telma wagon escort"},
          {"pillar clip", NOSQ_PILLAR_CLIP_INDEX, "Pillar Clip with Zora Armor"},
          {"lakebed", NOSQ_LAKEBED_INDEX, "The Lakebed Temple segment"},
          // {"deku toad", NOSQ_TOAD_INDEX, "Lakebed Temple miniboss"},
          {"lakebed bk skip", NOSQ_LAKEBED_BK_SKIP_INDEX, "Boss Key skip in Lakebed Temple"},
          {"morpheel", NOSQ_MORPHEEL_INDEX, "Morpheel fight (Zora Armor)"},
          // {"mdh", NOSQ_MDH_INDEX, "Midna's Desperate Hour"},
          // {"mountain climb", NOSQ_MOUNTAIN_INDEX, "Map glitch or Superjump up Snowpeak"},
          {"messenger skip", NOSQ_SPR_WARP_SKIP_INDEX, "LJA to skip the Snowpeak messengers"},
          {"snowpeak", NOSQ_SPR_INDEX, "The Snowpeak Ruins segment"},
          // {"bulblin camp", NOSQ_BULBLIN_CAMP_INDEX, "The camp before Arbiter's Grounds"},
          {"arbiter's grounds", NOSQ_AG_INDEX, "The Arbiter's Grounds segment"},
          // {"poe 1 skip", NOSQ_POE_1_SKIP_INDEX, "The pillar jump in Arbiter's Grounds"},
          {"death sword", NOSQ_DS_INDEX, "Arbiter's Grounds miniboss"},
          {"stallord", NOSQ_STALLORD_INDEX, "Arbiter's Grounds boss"},
          // {"city early", NOSQ_CITS_EARLY_INDEX, "Clip to the cannon early"},
          {"city 1", NOSQ_CITS_1_INDEX, "The 1st City in the Sky segment"},
          {"aeralfos skip", NOSQ_AERALFOS_SKIP_INDEX, "City in the Sky miniboss"},
          {"city 2", NOSQ_CITS_2_INDEX, "The 2nd City in the Sky segment"},
          // {"fan tower", NOSQ_FAN_TOWER_INDEX, "Final fan room in City"},
          {"argorok", NOSQ_ARGOROK_INDEX, "City in the Sky boss"},
          {"palace 1", NOSQ_PALACE_1_INDEX, "The 1st Palace of Twilight segment"},
          {"palace 2", NOSQ_PALACE_2_INDEX, "The 2nd Palace of Twilight segment"},
          {"zant", NOSQ_ZANT_INDEX, "Palace of Twilight boss"},
          {"hyrule castle", NOSQ_HC_INDEX, "The Hyrule Castle segment"},
          // {"inside castle", NOSQ_HC_INSIDE_INDEX, "Inside section of Hyrule Castle"},
          // {"beast ganon", NOSQ_BEAST_GANON_INDEX, "The Beast Ganon fight"},
          // {"horseback ganon", NOSQ_HORSEBACK_GANON_INDEX, "The Horseback Ganondorf fight"},
      } {}

NoSQSavesMenu::~NoSQSavesMenu() {}

void NoSQSavesMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        special NoSQSpecials[] = {
            special(NOSQ_HUGO_INDEX, SaveMngSpecial_Hugo, SaveMngSpecial_SpawnHugo),
            // special(NOSQ_KARG_INDEX, SaveMngSpecial_KargOoB, nullptr),
            special(NOSQ_KB2_SKIP_INDEX, SaveMngSpecial_KB2Skip, nullptr),
            special(NOSQ_ESCORT_INDEX, SaveMngSpecial_Escort, SaveMngSpecial_EscortKeys),
            special(NOSQ_LAKEBED_BK_SKIP_INDEX, SaveMngSpecial_LakebedBKSkip, nullptr),
            special(NOSQ_MORPHEEL_INDEX, nullptr, SaveMngSpecial_Morpheel),
            special(NOSQ_STALLORD_INDEX, SaveMngSpecial_Stallord, nullptr),
            special(NOSQ_FRST_ESCAPE_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(NOSQ_GORGE_VOID_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(NOSQ_RUPEE_ROLL_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(NOSQ_LANAYRU_GATE_CLIP_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(NOSQ_LAKEBED_INDEX, SaveMngSpecial_BossFlags, nullptr),
            // special(NOSQ_WATERFALL_SIDEHOP_INDEX, SaveMngSpecial_WaterfallSidehop, nullptr),
            special(NOSQ_AERALFOS_SKIP_INDEX, nullptr, SaveMngSpecial_NoSQAeralfos),
            // special(NOSQ_FAN_TOWER_INDEX, SaveMngSpecial_FanTower, nullptr),
            special(NOSQ_ARGOROK_INDEX, SaveMngSpecial_Argorok, nullptr),
            special(NOSQ_PALACE_1_INDEX, SaveMngSpecial_Palace1, nullptr),
            // special(NOSQ_BEAST_GANON_INDEX, BeastGanonSpecial_setLayer, nullptr),
        };

        SaveManager::triggerLoad(cursor.y, "nosq", NoSQSpecials,
                                 ARRAY_COUNT(NoSQSpecials));
        g_menuMgr->hide();
    }

    cursor.move(0, ARRAY_COUNT(lines));
    GZ_drawMenuLines(lines, cursor.y, ARRAY_COUNT(lines));
}