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
                        {"coro bugs", AD_CORO_BUGS_INDEX, "Tears inside of Coro's house"},
                        {"purple mist 1", AD_MIST_1_INDEX, "Purple mist in Faron Woods (pre-EMS)"},
                        {"early master sword", AD_EMS_INDEX, "Super Jump to Sacred Grove"},
                        {"purple mist 2", AD_MIST_INDEX, "Purple mist in Faron Woods (post-EMS)"},
                        {"king bulblin", AD_KB1_INDEX, "King Bulblin 1 fight"},
                        {"kak dc", AD_KAK_DC_INDEX, "Displacement clip through the rock"},
                        {"eldin twilight", AD_ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
                        {"forest temple", AD_FOREST_INDEX, "Forest Temple segment"},
                        {"forest temple 2", AD_FOREST_2_INDEX, "Forest Temple 2nd segment"},
                        {"diababa", AD_DIABABA_INDEX, "Forest Temple boss"},
                        {"pillar clip", AD_PILLAR_CLIP_INDEX, "Pillar Clip in Lake Hylia (low water)"},
                        {"lakebed 1", AD_LAKEBED_1_INDEX, "The 1st Lakebed Temple segment"},
                        {"lakebed main", AD_LAKEBED_MAIN_INDEX, "LBT central staircase room"},
                        {"cog double lja", AD_EDT_DOUBLE_LJA_INDEX, "Double LJA in cog room 1F"},
                        {"deku toad dc", AD_EDT_DC_INDEX, "Displacement clip through gate before Deku Toad"},
                        {"deku toad", AD_TOAD_INDEX, "Lakebed Temple miniboss"},
                        {"lanayru twilight", AD_LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
                        {"mountain umd", AD_MOUNTAIN_UMD_INDEX, "Snowpeak Mountain w/ UMD"},
                        {"snowpeak", AD_SPR_INDEX, "The Snowpeak Ruins segment"},
                        {"darkhammer", AD_DARKHAMMER_INDEX, "Snowpeak Ruins miniboss"},
                        {"snowpeak 2", AD_SPR_2_INDEX, "The Snowpeak Ruins 2nd segment"},
                        {"lfc", AD_LFC_INDEX, "Ladder freezard cancel"},
                        {"spr bk room", AD_SPR_BK_ROOM_INDEX, "Snowpeak Boss Key room"},
                        {"blizzeta", AD_BLIZZETA_INDEX, "Snowpeak Ruins boss"},
                        {"rusl td", AD_RUSL_TD_INDEX, "Rusl text displacement"},
                        {"early elevator", AD_EARLY_ELEVATOR_INDEX, "OoB LJA to Death Mountain Elevator"},
                        {"elevator escape", AD_ELEVATOR_ESCAPE_INDEX, "Escape from the elevator"},
                        {"goron mines", AD_GM_INDEX, "The Goron Mines segment"},
                        {"kitty climb", AD_KITTY_CLIMB_INDEX, "Climb to 2f from the railing OoB in GM main room"},
                        {"clawshot switch", AD_CLAWSHOT_SWITCH_INDEX, "Clawshot switch room"},
                        {"dangoro", AD_DANGORO_INDEX, "Goron Mines miniboss"},
                        {"goron mines 2", AD_GM_2_INDEX, "The Goron Mines 2nd segment"},
                        {"water lja", AD_WATER_LJA_INDEX, "LJA in water room on way back to outside"},
                        {"fyrus", AD_FYRUS_INDEX, "Goron Mines boss"},
                        {"lakebed bk skip", AD_BK_SKIP_INDEX, "Boss Key skip in Lakebed Temple"},
                        {"morpheel", AD_MORPHEEL_INDEX, "Morpheel fight (no Zora Armor)"},
                        {"mdh", AD_MDH_INDEX, "Midna's Desperate Hour segment"},
                        {"bulblin camp", AD_CAMP_INDEX, "Bulblin camp segment"},
                        {"arbiter's grounds", AD_AG_INDEX, "The Arbiter's Grounds segment"},
                        {"poe gate clip", AD_PGC_INDEX, "Clipping through the Arbiter's poe gate"},
                        {"ag early bk", AD_AG_EARLY_BK_INDEX, "Early Boss Key in Arbiter's Grounds"},
                        {"stalfos skip", AD_STALFOS_SKIP_INDEX, "Triple Stalfos Skip before Death Sword"},
                        {"death sword", AD_DSS_INDEX, "Arbiter's Grounds miniboss"},
                        {"arbiter's grounds 2", AD_AG_2_INDEX, "The Arbiter's Grounds 2nd segment"},
                        {"stallord", AD_STALLORD_INDEX, "Arbiter's Grounds boss"},
                        {"faron bomb boost", AD_FARON_BOOST_INDEX, "Bomb boost to Sacred Grove"},
                        {"lost woods 2", AD_LOST_WOODS_2_INDEX, "2nd Skull Kid chase in Lost Woods"},
                        {"sacred grove", AD_SACRED_GROVE_INDEX, "Post 2nd Skull Kid fight"},
                        {"temple of time", AD_TOT_INDEX, "The Temple of Time segment"},
                        {"first staircase", AD_FIRST_STAIRCASE_INDEX, "1st staircase ascent in ToT"},
                        {"turning platform", AD_TURNING_PLATFORM_INDEX, "Turning platform room ascent in ToT"},
                        {"double armos", AD_STATUE_THROWS_INDEX, "Bomb arrow the BS armos hitboxes"},
                        {"second staircase", AD_SECOND_STAIRCASE_INDEX, "2nd staircase ascent in ToT"},
                        {"tot bk room", AD_TOT_BK_INDEX, "Temple of Time boss key room"},
                        {"third staircase", AD_THIRD_STAIRCASE_INDEX, "3rd staircase ascent in ToT"},
                        {"tot darknut", AD_TOT_DARKNUT_INDEX, "Temple of Time miniboss"},
                        {"dot skip", AD_DOT_SKIP_INDEX, "Door of Time skip"},
                        {"silver rupee", AD_RUPEE_INDEX, "Silver Rupee collection"},
                        {"city 1", AD_CITS_1_INDEX, "The 1st City in the Sky segment"},
                        {"city gate clip", AD_CGC_INDEX, "Clipping through the city gate before Aeralfos"},
                        {"aeralfos skip", AD_AERALFOS_INDEX, "City in the Sky miniboss"},
                        {"city 2", AD_CITS_2_INDEX, "The 2nd City in the Sky segment"},
                        {"city bk clip", AD_BK_CLIP_INDEX, "Boss Key clip during City in the Sky"},
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
        special(AD_ORDON_GATE_CLIP_INDEX, nullptr, SaveMngSpecial_OrdonRock),
        special(AD_HUGO_INDEX, SaveMngSpecial_Hugo, SaveMngSpecial_SpawnHugo),
        special(AD_BK_SKIP_INDEX, SaveMngSpecial_LakebedBKSkip, nullptr),
        special(AD_MORPHEEL_INDEX, nullptr, SaveMngSpecial_Morpheel),
        special(AD_STALLORD_INDEX, SaveMngSpecial_BossFlags, SaveMngSpecial_Stallord),
        special(AD_PILLAR_CLIP_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(AD_LAKEBED_1_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(AD_TOAD_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(AD_ARGOROK_INDEX, SaveMngSpecial_Argorok, nullptr),
        special(AD_PALACE_1_INDEX, SaveMngSpecial_Palace1, nullptr),
        special(AD_PALACE_2_INDEX, nullptr, SaveMngSpecial_Palace2),
        special(AD_EARLY_ELEVATOR_INDEX, SaveMngSpecial_EarlyEle, SaveMngSpecial_EarlyEleSpawn),
        special(AD_ELEVATOR_ESCAPE_INDEX, SaveMngSpecial_ElevatorEscape, SaveMngSpecial_ElevatorEscape),
        special(AD_MIST_1_INDEX, nullptr, SaveMngSpecial_MDHBridge), // last speed 25
        special(AD_FOREST_2_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(AD_DIABABA_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(AD_DARKHAMMER_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(AD_BLIZZETA_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(AD_FYRUS_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(AD_EDT_DOUBLE_LJA_INDEX, nullptr, SaveMngSpecial_CenterCamera),
        special(AD_AG_EARLY_BK_INDEX, SaveMngSpecial_AGEarlyBk, nullptr),
        special(AD_STALFOS_SKIP_INDEX, nullptr, SaveMngSpecial_CenterCamera),
        special(AD_SACRED_GROVE_INDEX, SaveMngSpecial_AGEarlyBk, nullptr),
        special(AD_TOT_INDEX, SaveMngSpecial_AGEarlyBk, nullptr),
        special(AD_BK_CLIP_INDEX, nullptr, SaveMngSpecial_CenterCamera),
        special(AD_KITTY_CLIMB_INDEX, nullptr, SaveMngSpecial_CenterCamera),
        special(AD_CGC_INDEX, nullptr, SaveMngSpecial_CenterCamera),
        special(AD_AERALFOS_INDEX, nullptr, SaveMngSpecial_Aeralfos),
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
