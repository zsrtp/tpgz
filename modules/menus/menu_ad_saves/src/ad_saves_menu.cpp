#include "menus/menu_ad_saves/include/ad_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC ADSavesMenu::ADSavesMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"ordon gate clip", AD_ORDON_GATE_CLIP_INDEX,
                         "Gate Clip outside Ordon Spring"},
                        {"back in time", AD_BIT_INDEX, "Back in Time off the Ordon Spring bridge"},
                        {"goats", AD_GOATS_INDEX, "Goat herding 2"},
                        {"sword and shield skip", AD_HUGO_INDEX, "Hangin' with Hugo"},
                        {"faron twilight", AD_FARON_TWILGHT_INDEX, "Faron Twilight 1st half"},
                        {"early master sword", AD_EMS_INDEX, "Super Jump to Sacred Grove"},
                        {"purple mist", AD_MIST_INDEX, "Purple mist in Faron Woods (post-EMS)"},
                        {"king bulblin", AD_KB1_INDEX, "King Bulblin 1 fight"},
                        {"eldin twilight", AD_ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
                        {"forest temple", AD_FOREST_INDEX, "Forest Temple segment"},
                        {"diababa", AD_DIABABA_INDEX, "Forest Temple boss"},
                        {"pillar clip", AD_PILLAR_CLIP_INDEX,
                         "Pillar Clip in Lake Hylia (low water)"},
                        {"lakebed 1", AD_LAKEBED_1_INDEX, "The 1st Lakebed Temple segment"},
                        {"deku toad", AD_TOAD_INDEX, "Lakebed Temple miniboss"},
                        {"lanayru twilight", AD_LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
                        {"mountain umd", AD_MOUNTAIN_UMD_INDEX, "Snowpeak Mountain w/ UMD"},
                        {"snowpeak", AD_SPR_INDEX, "The Snowpeak Ruins segment"},
                        {"spr bk room", AD_SPR_BK_ROOM_INDEX, "Snowpeak Boss Key room"},
                        {"blizzeta", AD_BLIZZETA_INDEX, "Snowpeak Ruins boss"},
                        {"rusl td", AD_RUSL_TD_INDEX, "Rusl text displacement"},
                        {"early ele", AD_EARLY_ELAVATOR_INDEX, "OoB LJA to Death Mountain Elevator"},
                        {"goron mines", AD_GM_INDEX, "The Goron Mines segment"},
                        {"dangoro", AD_DANGORO_INDEX, "Goron Mines miniboss"},
                        {"lakebed bk skip", AD_BK_SKIP_INDEX, "Boss Key skip in Lakebed Temple"},
                        {"morpheel", AD_MORPHEEL_INDEX, "Morpheel fight (no Zora Armor)"},
                        {"mdh", AD_MDH_INDEX, "Midna's Desperate Hour segment"},
                        {"bulblin camp", AD_CAMP_INDEX, "Bulblin camp segment"},
                        {"arbiter's grounds", AD_AG_INDEX, "The Arbiter's Grounds segment"},
                        {"poe gate skip", AD_PGS_INDEX, "Bouncin' with Bonnie"},
                        {"death sword", AD_DSS_INDEX, "Arbiter's Grounds miniboss"},
                        {"stallord", AD_STALLORD_INDEX, "Arbiter's Grounds boss"},
                        {"faron bomb boost", AD_FARON_BOOST_INDEX, "Bomb boost to Sacred Grove"},
                        {"temple of time", AD_TOT_INDEX, "The Temple of Time segment"},
                        {"dot skip", AD_DOT_SKIP_INDEX, "Door of Time skip"},
                        {"silver rupee", AD_RUPEE_INDEX, "Silver Rupee collection"},
                        {"city 1", AD_CITS_1_INDEX, "The 1st City in the Sky segment"},
                        {"aeralfos skip", AD_AERALFOS_INDEX, "City in the Sky miniboss"},
                        {"city 2", AD_CITS_2_INDEX, "The 2nd City in the Sky segment"},
                        {"fan tower", AD_FAN_TOWER_INDEX, "Final fan room in City"},
                        {"argorok", AD_ARGOROK_INDEX, "City in the Sky boss"},
                        {"palace 1", AD_PALACE_1_INDEX, "The 1st Palace of Twilight segment"},
                        {"palace 2", AD_PALACE_2_INDEX, "The 2nd Palace of Twilight segment"},
                        {"zant", AD_ZANT_INDEX, "Palace of Twilight boss"},
                        {"hyrule castle", AD_HC_INDEX, "The Hyrule Castle segment"},
                        {"beast ganon", AD_BEAST_GANON_INDEX, "The Beast Ganon fight"},
                        {"horseback ganon", AD_HORSEBACK_INDEX, "The Horseback Ganondorf fight"},
                    } {}

ADSavesMenu::~ADSavesMenu() {}

void ADSavesMenu::draw() {
    special ADSpecials[] = {
        special(AD_HUGO_INDEX, SaveMngSpecial_Hugo, SaveMngSpecial_SpawnHugo),
        special(AD_BK_SKIP_INDEX, SaveMngSpecial_LakebedBKSkip, nullptr),
        special(AD_MORPHEEL_INDEX, nullptr, SaveMngSpecial_Morpheel),
        special(AD_STALLORD_INDEX, SaveMngSpecial_BossFlags, SaveMngSpecial_Stallord),
        special(AD_PILLAR_CLIP_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(AD_LAKEBED_1_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(AD_TOAD_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(AD_PGS_INDEX, nullptr, SaveMngSpecial_SpawnPGS),
        special(AD_ARGOROK_INDEX, SaveMngSpecial_Argorok, nullptr),
        special(AD_PALACE_1_INDEX, SaveMngSpecial_Palace1, nullptr),
        special(AD_PALACE_2_INDEX, nullptr, SaveMngSpecial_Palace2),
        special(AD_EARLY_ELAVATOR_INDEX, SaveMngSpecial_EarlyEle, SaveMngSpecial_EarlyEleSpawn)
    };

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        SaveManager::triggerLoad(cursor.y, "ad", ADSpecials, ARRAY_COUNT(ADSpecials));
        g_menuMgr->hide();
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
