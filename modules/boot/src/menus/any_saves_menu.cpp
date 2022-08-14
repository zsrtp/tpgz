#include "menus/any_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"

#ifdef GCN_PLATFORM
AnySavesMenu::AnySavesMenu()
    : Menu(), lines{
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
                  {"pillar clip", PILLAR_CLIP_INDEX, "Pillar Clip in Lake Hylia (low water)"},
                  {"lakebed 1", LAKEBED_1_INDEX, "The 1st Lakebed Temple segment"},
                  {"deku toad", TOAD_INDEX, "Lakebed Temple miniboss"},
                  {"kargorok flight", KARG_INDEX, "Clip OoB with trumpet bird"},
                  {"eldin twilight", ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
                  {"lanayru twilight", LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
                  {"waterfall sidehop", WATERFALL_SIDEHOP_INDEX,
                   "Waterfall sidehop after Rutela skip"},
                  {"boss bug", BOSS_BUG_INDEX, "Lanayru Twilight boss bug"},
                  {"iza", IZA_INDEX, "Steal Iza's bomb bag"},
                  {"norgor", NORGOR_INDEX, "Goron bomb bag without water bombs"},
                  {"messenger skip", SPR_WARP_SKIP_INDEX, "LJA to skip the Snowpeak messengers"},
                  {"snowpeak", SPR_INDEX, "The Snowpeak Ruins segment"},
                  {"dark hammer", DARK_HAMMER_INDEX, "Snowpeak Ruins miniboss"},
                  {"lakebed bk skip", LAKEBED_BK_SKIP_INDEX, "Boss Key skip in Lakebed Temple"},
                  {"morpheel", ONEBOMB_INDEX, "Morpheel fight (no Zora Armor)"},
                  {"mdh tower", MDH_TOWER_INDEX, "MDH tower climb"},
                  {"mdh bridge", MDH_BRIDGE_INDEX, "MDH castle rooftops"},
                  {"bulblin camp", BULBLIN_CAMP_INDEX, "The camp before Arbiter's Grounds"},
                  {"arbiter's grounds", AG_INDEX, "The Arbiter's Grounds segment"},
                  {"poe 1 skip", POE_1_SKIP_INDEX, "The pillar jump in Arbiter's Grounds"},
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
#endif
#ifdef WII_PLATFORM
AnySavesMenu::AnySavesMenu()
    : Menu(),
      lines{{"ordon gate clip", ORDON_GATE_CLIP_INDEX, "Gate Clip outside Ordon Spring"},
            {"back in time", BACK_IN_TIME_INDEX, "Back In Time off the Ordon Spring bridge"},
            {"goats", GOATS_INDEX, "Goat herding 2"},
            {"sword and shield skip", HUGO_INDEX, "Hangin' with Hugo"},
            {"early master sword", EMS_INDEX, "Super Jump to early Sacred Grove"},
            {"purple mist", MIST_INDEX, "Purple mist in Faron Woods (post-EMS)"},
            {"forest temple", FRST_INDEX, "first entry into Forest Temple"},
            {"early gale", EARLY_GALE_INDEX, "Platforming to Ook"},
            {"deku like skip", DEKU_LIKE_INDEX, "frame perfect jump from the deku like platform"},
            {"diababa", DIABABA_INDEX, "diababa fight"},
            {"mailman skip", MAILMAN_SKIP_INDEX, "jump attack over mailman trigger twice"},
            {"lanayru gate clip", LANAYRU_GATE_CLIP_INDEX, "gate clip outside Lake Hylia"},
            {"kargorok fight", KARG_FIGHT_INDEX, "fight with the kargarok"},
            {"kargorok flight", KARG_FLIGHT_INDEX, "clip OoB with trumpet bird"},
            {"eldin twilight", ELDIN_TWILIGHT_INDEX, "eldin Twilight tears"},
            {"bombhouse skip", BOMBHOUSE_SKIP_INDEX, "jump from the bomb shop to the bombhouse"},
            {"midna text skip", MIDNA_TEXT_SKIP_INDEX, "frame perfect sidehop to skip midna text"},
            {"midna dive", MIDNA_DIVE_INDEX, "Pillar Clip in Lake Hylia (high water)"},
            {"lakebed 1", LAKEBED_1_INDEX, "The first Lakebed Temple segment"},
            {"jake", JAKE_INDEX, "use the helmasaur (jake) to LJA to the upper ledge"},
            {"lanayru twilight", LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
            {"waterfall sidehop", WATERFALL_SIDEHOP_INDEX, "Waterfall sidehop after Rutela skip"},
            {"boss bug", BOSS_BUG_INDEX, "Lanayru Twilight boss bug"},
            {"iza", IZA_INDEX, "Steal Iza's bomb bag"},
            {"deku toad", TOAD_INDEX, "The miniboss of Lakebed Temple"},
            {"morpheel", MORPHEEL_INDEX, "Morpheel fight (no Zora Armor)"},
            {"mdh tower", MDH_TOWER_INDEX, "MDH tower climb before castle rooftops"},
            {"mdh bridge", MDH_BRIDGE_INDEX, "The falling bridge on castle rooftops"},
            {"bulblin camp", BULBLIN_CAMP_INDEX, "The area before Arbiter's Grounds"},
            {"arbiter's grounds", AG_INDEX, "The Arbiter's Grounds segment"},
            {"poe 1 skip", POE_1_SKIP_INDEX, "The pillar jump in Arbiter's Grounds"},
            {"death sword", DSS_INDEX, "The Arbiter's Grounds miniboss"},
            {"stallord", STALLORD_INDEX, "The Arbiter's Grounds boss"},
            {"snowpeak", SPR_INDEX, "The Snowpeak Ruins dungeon segment"},
            {"snowpeak spinner bomb boost", SPR_BOOST_INDEX, "spinner bomb boost over the wall."},
            {"freezard clip", SPR_FREEZARD_INDEX, "clip through the door behind freezard"},
            {"dark hammer", DARK_HAMMER_INDEX, "The Snowpeak Ruins miniboss"},
            {"city in the sky early", CITS_EARLY_INDEX, "Clip to the cannon early"},
            {"city in the sky 1", CITS_1_INDEX, "The first City in the Sky segment"},
            {"aeralfos skip", AERALFOS_SKIP_INDEX, "The City in the Sky miniboss"},
            {"city in the sky 2", CITS_2_INDEX, "The second City in the Sky segment"},
            {"fan tower", FAN_TOWER_INDEX, "Final fan room in CitS before the boss"},
            {"argorok", ARGOROK_INDEX, "The City in the Sky boss"},
            {"palace of twilight 1", PALACE_1_INDEX, "The first Palace of Twilight segment"},
            {"palace of twilight 2", PALACE_2_INDEX,
             "The second Palace of Twilight segment (after both Sols)"},
            {"early platform", EARLY_PLATFORM_INDEX, "Early platform in Palace of Twilight"},
            {"zant", ZANT_INDEX, "The Palace of Twilight boss"},
            {"hyrule castle", HC_INDEX, "The Hyrule Castle segment"},
            {"darknut fight", DARKNUT_INDEX, "The Darknut fight in Hyrule Castle"},
            {"final tower climb", HC_TOWER_INDEX, "The tower climb before the final boss fights"},
            {"beast ganon", BEAST_GANON_INDEX, "The Beast Ganon fight"},
            {"horseback ganon", HORSEBACK_GANON_INDEX, "The horseback Ganondorf fight"}} {};
#endif

void AnySavesMenu::draw() {
#ifdef GCN_PLATFORM
    special AnySpecials[ANY_SPECIALS_AMNT] = {
        special(HUGO_INDEX, SaveMngSpecial_Hugo, SaveMngSpecial_SpawnHugo),
        special(KARG_INDEX, SaveMngSpecial_KargOoB, nullptr),
        special(NORGOR_INDEX, nullptr, SaveMngSpecial_Norgor),
        special(LAKEBED_BK_SKIP_INDEX, SaveMngSpecial_LakebedBKSkip, nullptr),
        special(ONEBOMB_INDEX, nullptr, SaveMngSpecial_Morpheel),
        special(STALLORD_INDEX, SaveMngSpecial_Stallord, nullptr),
        special(STALLORD2_INDEX, SaveMngSpecial_Stallord2_init, SaveMngSpecial_Stallord2),
        special(FRST_ESCAPE_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(GORGE_VOID_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(RUPEE_ROLL_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(LANAYRU_GATE_CLIP_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(PILLAR_CLIP_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(LAKEBED_1_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(WATERFALL_SIDEHOP_INDEX, SaveMngSpecial_WaterfallSidehop, nullptr),
        special(DARK_HAMMER_INDEX, SaveMngSpecial_BossFlags, SaveMngSpecial_Darkhammer),
        special(FAN_TOWER_INDEX, SaveMngSpecial_FanTower, nullptr),
        special(ARGOROK_INDEX, SaveMngSpecial_Argorok, nullptr),
        special(PALACE_1_INDEX, SaveMngSpecial_Palace1, nullptr),
        special(PALACE_2_INDEX, nullptr, SaveMngSpecial_Palace2),
    };
#endif
#ifdef WII_PLATFORM
    special AnySpecials[ANY_SPECIALS_AMNT] = {
        special(HUGO_INDEX, SaveMngSpecial_Hugo, SaveMngSpecial_SpawnHugo),
        special(KARG_FLIGHT_INDEX, SaveMngSpecial_KargOoB, nullptr),
        special(MORPHEEL_INDEX, nullptr, SaveMngSpecial_Morpheel),
        special(STALLORD_INDEX, SaveMngSpecial_Stallord, nullptr),
        special(LAKEBED_1_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(WATERFALL_SIDEHOP_INDEX, SaveMngSpecial_WaterfallSidehop, nullptr),
        special(DARK_HAMMER_INDEX, SaveMngSpecial_BossFlags, SaveMngSpecial_Darkhammer),
        special(FAN_TOWER_INDEX, SaveMngSpecial_FanTower, nullptr),
        special(ARGOROK_INDEX, SaveMngSpecial_Argorok, nullptr),
        special(PALACE_1_INDEX, SaveMngSpecial_Palace1, nullptr),
        special(PALACE_2_INDEX, nullptr, SaveMngSpecial_Palace2),
    };
#endif

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(GZ_PRACTICE_MENU);
        GZ_setReturnMenu(GZ_NO_MENU);
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        SaveManager::loadSave(cursor.y, "any", AnySpecials,
                              sizeof(AnySpecials) / sizeof(AnySpecials[0]));
        GZ_setReturnMenu(GZ_ANY_SAVES_MENU);
    }

    cursor.move(0, sizeof(lines) / sizeof(lines[0]));
    GZ_drawMenuLines(lines, cursor.y, sizeof(lines) / sizeof(lines[0]));
}