#include "menus/menu_any_bite_saves/include/any_bite_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC AnyBiTESavesMenu::AnyBiTESavesMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
#ifdef GCN_PLATFORM
          {"ordon gate clip", BITE_ORDON_GATE_CLIP_INDEX, "Gate Clip outside Ordon Spring"},
          {"back in time", BITE_BACK_IN_TIME_INDEX, "Back in Time off the Ordon Spring bridge"},
          {"goats", BITE_GOATS_INDEX, "Goat herding 2"},
          {"sword and shield skip", BITE_HUGO_INDEX, "Hangin' with Hugo"},
          {"faron twilight", BITE_FARON_TWILIGHT_INDEX, "Faron Twilight tears"},
          {"early master sword", BITE_EMS_INDEX, "Super Jump to Sacred Grove"},
          {"purple mist", BITE_MIST_INDEX, "Purple mist in Faron Woods (post-EMS)"},
          {"forest bit", BITE_FRST_BIT_INDEX, "Back in Time in Forest Temple"},
          {"forest escape", BITE_FRST_ESCAPE_INDEX, "LJA over S.Faron exit trigger"},
          {"lanayru gate clip", BITE_LANAYRU_GATE_CLIP_INDEX, "Gate Clip to Lanayru"},
          {"pillar clip", BITE_PILLAR_CLIP_INDEX, "Pillar Clip in Lake Hylia (low water)"},
          {"lakebed 1", BITE_LAKEBED_1_INDEX, "The 1st Lakebed Temple segment"},
          {"deku toad", BITE_TOAD_INDEX, "Lakebed Temple miniboss"},
          {"kargorok flight", BITE_KARG_INDEX, "Clip OoB with trumpet bird"},
          {"king bulblin", BITE_KB1_INDEX, "King Bulblin 1 fight"},
          {"eldin twilight", BITE_ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
          {"lanayru twilight", BITE_LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
          {"waterfall sidehop", BITE_WATERFALL_SIDEHOP_INDEX,
           "Waterfall sidehop after Rutela skip"},
          {"iza", BITE_IZA_INDEX, "Steal Iza's bomb bag"},
          {"messenger skip", BITE_SPR_WARP_SKIP_INDEX, "LJA to skip the Snowpeak messengers"},
          {"snowpeak", BITE_SPR_INDEX, "The Snowpeak Ruins segment"},
          {"darkhammer", BITE_DARK_HAMMER_INDEX, "Snowpeak Ruins miniboss"},
          {"lakebed bk skip", BITE_LAKEBED_BK_SKIP_INDEX, "Boss Key skip in Lakebed Temple"},
          {"morpheel", BITE_ONEBOMB_INDEX, "Morpheel fight (no Zora Armor)"},
          {"mdh tower", BITE_MDH_TOWER_INDEX, "MDH tower climb"},
          {"mdh bridge", BITE_MDH_BRIDGE_INDEX, "MDH castle rooftops"},
          {"bulblin camp", BITE_BULBLIN_CAMP_INDEX, "The camp before Arbiter's Grounds"},
          {"arbiter's grounds", BITE_AG_INDEX, "The Arbiter's Grounds segment"},
          {"poe gate skip", BITE_PGS_INDEX, "Bouncin' with Bonnie"},
          {"death sword", BITE_DSS_INDEX, "Arbiter's Grounds miniboss"},
          {"stallord", BITE_STALLORD_INDEX, "Arbiter's Grounds boss"},
          {"stallord 2", BITE_STALLORD2_INDEX, "Stallord 2nd phase"},
          {"silver rupee", BITE_SILVER_RUPEE, "Silver Rupee in Kakariko"},
          {"city early", BITE_CITS_EARLY_INDEX, "Clip to the cannon early"},
          {"city 1", BITE_CITS_1_INDEX, "The 1st City in the Sky segment"},
          {"aeralfos skip", BITE_AERALFOS_SKIP_INDEX, "City in the Sky miniboss"},
          {"fan tower", BITE_FAN_TOWER_INDEX, "Final fan room in City"},
          {"argorok", BITE_ARGOROK_INDEX, "City in the Sky boss"},
          {"palace 1", BITE_PALACE_1_INDEX, "The 1st Palace of Twilight segment"},
          {"palace 2", BITE_PALACE_2_INDEX, "The 2nd Palace of Twilight segment"},
          {"early platform", BITE_EARLY_PLATFORM_INDEX, "Early platform in Palace of Twilight"},
          {"zant", BITE_ZANT_INDEX, "Palace of Twilight boss"},
          {"hyrule castle", BITE_HC_INDEX, "The Hyrule Castle segment"},
          {"final tower climb", BITE_HC_TOWER_INDEX, "The tower climb before Ganondorf"},
          {"beast ganon", BITE_BEAST_GANON_INDEX, "The Beast Ganon fight"},
          {"horseback ganon", BITE_HORSEBACK_GANON_INDEX, "The Horseback Ganondorf fight"},
#endif
#ifdef WII_PLATFORM
          {"ordon gate clip", BITE_ORDON_GATE_CLIP_INDEX, "Gate Clip outside Ordon Spring"},
          {"back in time", BITE_BACK_IN_TIME_INDEX, "Back in Time off the Ordon Spring bridge"},
          {"seam clip", BITE_SEAM_CLIP_INDEX, "Seam Clip in Hyrule Field South"},
          {"goats", BITE_GOATS_INDEX, "Goat herding 2"},
          {"sword and shield skip", BITE_HUGO_INDEX, "Hangin' with Hugo"},
          {"faron twilight", BITE_FARON_TWILIGHT_INDEX, "Faron Twilight tears"},
          {"early master sword", BITE_EMS_INDEX, "Super Jump to Sacred Grove"},
          {"purple mist", BITE_MIST_INDEX, "Purple mist in Faron Woods (post-EMS)"},
          {"king bulblin 1", BITE_KB1_INDEX, "King Bulblin 1 fight"},
          {"eldin twilight", BITE_ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
          {"bombhouse skip", BITE_BOMBHOUSE_SKIP_INDEX, "Bombhouse skip in Kakariko"},
          {"epona oob", BITE_EPONA_OOB_INDEX, "Epona OoB in Eldin Province"},
          {"lanayru twilight", BITE_LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
          {"waterfall sidehop", BITE_WATERFALL_SIDEHOP_INDEX, "Waterfall sidehop after Rutela skip"},
          {"boss bug", BITE_BOSS_BUG_INDEX, "Boss Bug in Lake Hylia"},
          {"iza", BITE_IZA_INDEX, "Steal Iza's bomb bag"},
          {"plumm oob", BITE_PLUMM_OOB_INDEX, "Plumm OoB in Zora's Domain"},
          {"enter lakebed", BITE_ENTER_LAKEBED_INDEX, "Enter Lakebed Temple"},
          {"lakebed 1", BITE_LAKEBED_1_INDEX, "The 1st Lakebed Temple segment"},
          {"deku toad", BITE_TOAD_INDEX, "Lakebed Temple miniboss"},
          {"onebomb morpheel", BITE_ONEBOMB_INDEX, "Morpheel fight (no Zora Armor)"},
          {"mdh tower", BITE_MDH_TOWER_INDEX, "MDH tower climb"},
          {"mdh bridge", BITE_MDH_BRIDGE_INDEX, "MDH castle rooftops"},
          {"messenger skip", BITE_MESSENGER_SKIP_INDEX, "LJA to skip the Snowpeak messengers"},
          {"snowpeak mbbb", BITE_SPR_MBBB_INDEX, "Snowpeak Ruins miniboss"},
          {"freezard skip", BITE_FREEZARD_SKIP_INDEX, "Freezard skip in Snowpeak Ruins"},
          {"darkhammer", BITE_DARK_HAMMER_INDEX, "Snowpeak Ruins miniboss"},
          {"bulblin camp", BITE_BULBLIN_CAMP_INDEX, "The camp before Arbiter's Grounds"},
          {"arbiter's grounds", BITE_AG_INDEX, "The Arbiter's Grounds segment"},
          {"poe gate skip", BITE_PGS_INDEX, "Bouncin' with Bonnie"},
          {"early boss key", BITE_EARLY_BOSS_KEY_INDEX, "Early Boss Key in Arbiter's Grounds"},
          {"death sword", BITE_DSS_INDEX, "Arbiter's Grounds miniboss"},
          {"stallord", BITE_STALLORD_INDEX, "Arbiter's Grounds boss"},
          {"stallord 2", BITE_STALLORD2_INDEX, "Stallord 2nd phase"},
          {"city early", BITE_CITS_EARLY_INDEX, "Clip to the cannon early"},
          {"city 1", BITE_CITS_1_INDEX, "The 1st City in the Sky segment"},
          {"aeralfos skip", BITE_AERALFOS_SKIP_INDEX, "City in the Sky miniboss"},
          {"city 2", BITE_CITS_2_INDEX, "The 2nd City in the Sky segment"},
          {"fan tower", BITE_FAN_TOWER_INDEX, "Final fan room in City"},
          {"argorok", BITE_ARGOROK_INDEX, "City in the Sky boss"},
          {"palace sol 1", BITE_PALACE_1_INDEX, "The 1st Sol of Palace of Twilight"},
          {"palace sol 2", BITE_STUPID_ROOM_INDEX, "The 2nd Sol of Palace of Twilight"},
          {"palace 2", BITE_PALACE_2_INDEX, "After light sword"},
          {"early platform", BITE_EARLY_PLATFORM_INDEX, "Early platform in Palace of Twilight"},
          {"zant", BITE_ZANT_INDEX, "Palace of Twilight boss"},
          {"hyrule castle", BITE_HC_INDEX, "The Hyrule Castle segment"},
          {"darknut", BITE_DARKNUT_INDEX, "The Darknut fight in Hyrule Castle"},
          {"final tower climb", BITE_HC_TOWER_INDEX, "The tower climb before Ganondorf"},
          {"beast ganon", BITE_BEAST_GANON_INDEX, "The Beast Ganon fight"},
          {"horseback ganon", BITE_HORSEBACK_GANON_INDEX, "The Horseback Ganondorf fight"},
#endif
      } {}

AnyBiTESavesMenu::~AnyBiTESavesMenu() {}

void AnyBiTESavesMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        special AnySpecials[] = {
            special(BITE_ORDON_GATE_CLIP_INDEX, nullptr, SaveMngSpecial_OrdonRock),
            special(BITE_HUGO_INDEX, SaveMngSpecial_Hugo, SaveMngSpecial_SpawnHugo),
#ifdef GCN_PLATFORM
            special(BITE_KARG_INDEX, SaveMngSpecial_KargOoB, nullptr),
            special(BITE_LAKEBED_BK_SKIP_INDEX, SaveMngSpecial_LakebedBKSkip, nullptr),
            special(BITE_FRST_ESCAPE_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(BITE_LANAYRU_GATE_CLIP_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(BITE_PILLAR_CLIP_INDEX, SaveMngSpecial_BossFlags, nullptr),
#endif
            special(BITE_TOAD_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(BITE_ONEBOMB_INDEX, nullptr, SaveMngSpecial_Morpheel),
            special(BITE_STALLORD_INDEX, SaveMngSpecial_Stallord, nullptr),
            special(BITE_STALLORD2_INDEX, SaveMngSpecial_Stallord2_init, SaveMngSpecial_Stallord2),
            special(BITE_LAKEBED_1_INDEX, SaveMngSpecial_BossFlags, nullptr),
            special(BITE_WATERFALL_SIDEHOP_INDEX, SaveMngSpecial_WaterfallSidehop, nullptr),
            special(BITE_DARK_HAMMER_INDEX, SaveMngSpecial_BossFlags, SaveMngSpecial_Darkhammer),
            special(BITE_FAN_TOWER_INDEX, SaveMngSpecial_FanTower, nullptr),
            special(BITE_PGS_INDEX, nullptr, SaveMngSpecial_SpawnPGS),
            special(BITE_ARGOROK_INDEX, SaveMngSpecial_Argorok, nullptr),
            special(BITE_PALACE_1_INDEX, SaveMngSpecial_Palace1, nullptr),
            special(BITE_PALACE_2_INDEX, nullptr, SaveMngSpecial_Palace2),
            special(BITE_BEAST_GANON_INDEX, BeastGanonSpecial_setLayer, nullptr),
        };
        SaveManager::triggerLoad(cursor.y, "any_bite", AnySpecials, ARRAY_COUNT(AnySpecials));
        g_menuMgr->hide();
    }

    cursor.move(0, ARRAY_COUNT(lines));
    GZ_drawMenuLines(lines, cursor.y, ARRAY_COUNT(lines));
}