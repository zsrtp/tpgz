#include "menus/menu_any_saves/include/any_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC AnySavesMenu::AnySavesMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"ordon gate clip", ORDON_GATE_CLIP_INDEX, "Gate Clip outside Ordon Spring"},
          {"back in time", BACK_IN_TIME_INDEX, "Back in Time off the Ordon Spring bridge"},
          {"goats", GOATS_INDEX, "Goat herding 2"},
          {"sword and shield skip", HUGO_INDEX, "Hangin' with Hugo"},
          {"early master sword", EMS_INDEX, "Super Jump to Sacred Grove"},
          {"purple mist", MIST_INDEX, "Purple mist in Faron Woods (post-EMS)"},
          {"forest bit", FRST_BIT_INDEX, "Back in Time in Forest Temple"},
          {"forest escape", FRST_ESCAPE_INDEX, "LJA over S.Faron exit trigger"},
          {"gorge void", GORGE_VOID_INDEX, "1 frame jump attack into Gorge"},
          {"rupee roll", RUPEE_ROLL_INDEX, "Rupee Roll / Gorge Skip"},
          {"lanayru gate clip", LANAYRU_GATE_CLIP_INDEX, "Gate Clip to Lanayru"},
          {"kargorok flight", KARG_INDEX, "Clip OoB with trumpet bird"},
          {"eldin twilight", ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
          {"bomb house skip", BOMB_HOUSE_SKIP_INDEX, "Skip entering the Bomb House"},
          {"lanayru twilight", LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
          {"waterfall sidehop", WATERFALL_SIDEHOP_INDEX, "Waterfall sidehop after Rutela skip"},
          {"boss bug", BOSS_BUG_INDEX, "Lanayru Twilight boss bug"},
          {"iza", IZA_INDEX, "Steal Iza's bomb bag"},
          {"plumm oob", PLUMM_OOB_INDEX, "Clip OoB during the Plumm flight"},
          {"enter lakebed", ELH_INDEX, "Enter Lakebed with Empty Lake Hylia"},
          {"lakebed", LAKEBED_1_INDEX, "The Lakebed Temple segment"},
          {"deku toad", TOAD_INDEX, "Lakebed Temple miniboss"},
          {"lakebed bk skip", LAKEBED_BK_SKIP_INDEX, "Boss Key skip in Lakebed Temple"},
          {"morpheel", ONEBOMB_INDEX, "Morpheel fight (no Zora Armor)"},
          {"mdh tower", MDH_TOWER_INDEX, "MDH tower climb"},
          {"mdh bridge", MDH_BRIDGE_INDEX, "MDH castle rooftops"},
          {"messenger skip", SPR_WARP_SKIP_INDEX, "LJA to skip the Snowpeak messengers"},
          {"snowpeak", SPR_INDEX, "The Snowpeak Ruins segment"},
          {"darkhammer", DARK_HAMMER_INDEX, "Snowpeak Ruins miniboss"},
          {"bulblin camp", BULBLIN_CAMP_INDEX, "The camp before Arbiter's Grounds"},
          {"arbiter's grounds", AG_INDEX, "The Arbiter's Grounds segment"},
          {"poe gate skip", PGS_INDEX, "Bouncin' with Bonnie"},
          {"death sword", DSS_INDEX, "Arbiter's Grounds miniboss"},
          {"stallord", STALLORD_INDEX, "Arbiter's Grounds boss"},
          {"stallord 2", STALLORD2_INDEX, "Stallord 2nd phase"},
          {"city early", CITS_EARLY_INDEX, "Clip to the cannon early"},
          {"city 1", CITS_1_INDEX, "The 1st City in the Sky segment"},
          {"aeralfos skip", AERALFOS_SKIP_INDEX, "City in the Sky miniboss"},
          {"city 2", CITS_2_INDEX, "The 2nd City in the Sky segment"},
          {"fan tower", FAN_TOWER_INDEX, "Final fan room in City"},
          {"argorok", ARGOROK_INDEX, "City in the Sky boss"},
          {"palace 1", PALACE_1_INDEX, "The 1st Palace of Twilight segment"},
          {"palace 2", PALACE_2_INDEX, "The 2nd Palace of Twilight segment"},
          {"early platform", EARLY_PLATFORM_INDEX, "Early platform in Palace of Twilight"},
          {"zant", ZANT_INDEX, "Palace of Twilight boss"},
          {"hyrule castle", HC_INDEX, "The Hyrule Castle segment"},
          {"darknut fight", DARKNUT_INDEX, "The 1st Darknut fight in Hyrule Castle"},
          {"final tower climb", HC_TOWER_INDEX, "The tower climb before Ganondorf"},
          {"beast ganon", BEAST_GANON_INDEX, "The Beast Ganon fight"},
          {"horseback ganon", HORSEBACK_GANON_INDEX, "The Horseback Ganondorf fight"},
      } {}

AnySavesMenu::~AnySavesMenu() {}

void AnySavesMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        special AnySpecials[] = {
            special(ORDON_GATE_CLIP_INDEX, nullptr, SaveMngSpecial_OrdonRock),
            special(HUGO_INDEX, SaveMngSpecial_Hugo, SaveMngSpecial_SpawnHugo),
            special(KARG_INDEX, SaveMngSpecial_KargOoB, nullptr),
            special(PLUMM_OOB_INDEX, SaveMngSpecial_AnyPlummOoB, nullptr),
            special(LAKEBED_BK_SKIP_INDEX, SaveMngSpecial_LakebedBKSkip, nullptr),
            special(ONEBOMB_INDEX, nullptr, SaveMngSpecial_Morpheel),
            special(STALLORD_INDEX, SaveMngSpecial_BossFlags, SaveMngSpecial_Stallord),
            special(STALLORD2_INDEX, SaveMngSpecial_Stallord2_init, SaveMngSpecial_Stallord2),
            special(FRST_ESCAPE_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(GORGE_VOID_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(RUPEE_ROLL_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(LANAYRU_GATE_CLIP_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(LAKEBED_1_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(TOAD_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(WATERFALL_SIDEHOP_INDEX, SaveMngSpecial_WaterfallSidehop, nullptr),
            special(DARK_HAMMER_INDEX, SaveMngSpecial_BossFlags, SaveMngSpecial_Darkhammer),
            special(PGS_INDEX, nullptr, SaveMngSpecial_SpawnPGS),
            special(FAN_TOWER_INDEX, SaveMngSpecial_FanTower, nullptr),
            special(ARGOROK_INDEX, SaveMngSpecial_Argorok, nullptr),
            special(PALACE_1_INDEX, SaveMngSpecial_Palace1, nullptr),
            special(PALACE_2_INDEX, nullptr, SaveMngSpecial_Palace2),
            special(BEAST_GANON_INDEX, BeastGanonSpecial_setLayer, nullptr),
            special(ELH_INDEX, SaveMngSpecial_emptyLake, nullptr),
            special(IZA_INDEX, SaveMngSpecial_BossFlags, nullptr),
        };
        SaveManager::triggerLoad(cursor.y, "any", AnySpecials, ARRAY_COUNT(AnySpecials));
        g_menuMgr->hide();
    }

    cursor.move(0, ARRAY_COUNT(lines));
    GZ_drawMenuLines(lines, cursor.y, ARRAY_COUNT(lines));
}
