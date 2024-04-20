#include "menus/menu_hundo_saves/include/hundo_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC HundoSavesMenu::HundoSavesMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"goats 1", HND_GOATS_1_INDEX, "Goat herding 1"},
          {"ordon gate clip", HND_ORDON_GATE_CLIP_INDEX, "Gate clip outside Ordon Spring"},
          {"goats 2", HND_GOATS_2_INDEX, "Goat herding 2"},
          {"faron twilight", HND_FARON_TWILIGHT_INDEX, "Faron Twilight tears"},
          {"early master sword", HND_EMS_INDEX, "Super Jump to Sacred Grove"},
          {"purple mist", HND_MIST_INDEX, "Purple mist in Faron Woods (post-EMS)"},
          {"forest bit", HND_FRST_BIT_INDEX, "Back in Time in Forest Temple"},
          {"forest temple 2", HND_FRST_2_INDEX, "The Forest Temple segment after boomerang"},
          {"diababa", HND_OOKLESS_INDEX, "Forest Temple boss"},
          {"eldin twilight", HND_ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
          {"bomb house skip", HND_BOMB_HOUSE_SKIP_INDEX, "Kakariko Bomb House Skip"},
          {"lanayru gate clip", HND_LANAYRU_GATE_CLIP_INDEX, "Gate Clip to Lanayru"},
          {"pillar clip", HND_PILLAR_CLIP_INDEX, "Pillar Clip in Lake Hylia (low water)"},
          {"lakebed 1", HND_LAKEBED_1_INDEX, "The 1st Lakebed Temple segment"},
          {"deku toad", HND_TOAD_INDEX, "Lakebed Temple miniboss"},
          {"kargorok flight", HND_KARG_INDEX, "Clip OoB with trumpet bird"},
          {"lanayru twilight", HND_LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
          {"boss bug", HND_BOSS_BUG_INDEX, "Lanayru Twilight boss bug"},
          {"kb2 skip", HND_KB_2_INDEX, "Clip to skip King Bulblin 2"},
          {"wagon escort", HND_ESCORT_INDEX, "Telma wagon escort"},
          {"coro td", HND_COROTD_INDEX, "Text Displacement with Coro"},
          {"goron mines", HND_GM_INDEX, "The Goron Mines segment"},
          {"dangoro", HND_DANGORO_INDEX, "Goron Mines miniboss"},
          {"post gm", HND_POST_GM_INDEX, "The segment after Goron Mines"},
          {"lakebed bk skip", HND_LAKEBED_BK_SKIP_INDEX, "Boss Key skip in Lakebed Temple"},
          {"morpheel", HND_MORPHEEL_INDEX, "Lakebed Temple boss"},
          {"mdh tower", HND_MDH_TOWER_INDEX, "MDH tower climb"},
          {"mdh bridge", HND_MDH_BRIDGE_INDEX, "MDH castle rooftops"},
          {"post mdh", HND_POST_MDH_INDEX, "Collection cycle after MDH"},
          {"star 1", HND_STAR_1_INDEX, "The 1st STAR minigame"},
          {"kb1", HND_KB1_INDEX, "King Bulblin 1 fight"},
          {"iza 1 skip", HND_IZA_1_SKIP_INDEX, "Plumm OoB to skip iza 1"},
          {"lake hylia cave", HND_LH_CAVE_INDEX, "Lake Hylia dark cave"},
          {"bulblin camp", HND_BULBLIN_CAMP_INDEX, "The camp before Arbiter's Grounds"},
          {"arbiter's grounds", HND_AG_INDEX, "The Arbiter's Grounds segment"},
          {"poe 1 skip", HND_POE_1_SKIP_INDEX, "The pillar jump in Arbiter's Grounds"},
          {"death sword", HND_DSS_INDEX, "Arbiter's Grounds miniboss"},
          {"stallord", HND_STALLORD_INDEX, "Arbiter's Grounds boss"},
          {"post ag", HND_POST_AG_INDEX, "Collection cycle after Arbiter's"},
          {"snowpeak", HND_SPR_INDEX, "The Snowpeak Ruins segment"},
          {"darkhammer", HND_DARK_HAMMER_INDEX, "Snowpeak Ruins miniboss"},
          {"spr superjump", HND_SPR_SUPERJUMP_INDEX, "SPR Super Jump to 2nd floor"},
          {"spr bk lja", HND_SPR_BK_LJA_INDEX, "LJA to Snowpeak Boss Key room"},
          {"spr bk room", HND_SPR_BK_ROOM_INDEX, "Snowpeak Boss Key room"},
          {"blizzeta", HND_BLIZZETA_INDEX, "Snowpeak Ruins boss"},
          {"faron boost", HND_FARON_BOOST_INDEX, "Bomb boost to Sacred Grove"},
          {"grove skip", HND_GROVE_SKIP_INDEX, "Grove 2 skip w/ Moon Boots"},
          {"grove boost", HND_GROVE_BOOST_INDEX, "Boost to upper floor of Grove"},
          {"temple of time", HND_TOT_INDEX, "The Temple of Time segment"},
          {"tot early poe", HND_EARLY_POE_INDEX, "Early poe 1 in Temple of Time"},
          {"tot statue throws", HND_STATUE_THROWS_INDEX, "Temple of Time statue throws"},
          {"tot early hp", HND_EARLY_HP_INDEX, "Boost to heart piece in Temple of Time"},
          {"tot darknut", HND_DARKNUT_INDEX, "Temple of Time miniboss"},
          {"dot skip", HND_DOT_SKIP_INDEX, "Door of Time skip"},
          {"post tot", HND_POST_TOT_INDEX, "Collection cycle after Temple of Time"},
          {"hotspring minigame", HND_HOTSPRING_INDEX, "Goron hotspring water minigame"},
          {"gorge arc", HND_GORGE_ARC_INDEX, "Gorge / South Faron collection"},
          {"ice puzzle", HND_PUZZLE_INDEX, "The Ice Puzzle segment"},
          {"hugo archery", HND_ARCHERY_INDEX, "Archery in Hidden Village"},
          {"city 1", HND_CITY_1_INDEX, "The 1st City in the Sky segment"},
          {"aeralfos skip", HND_AERALFOS_INDEX, "the city in the sky miniboss"},
          {"city 2", HND_CITY_2_INDEX, "The 2nd City in the Sky segment"},
          {"early poe cycle", HND_POE_CYCLE_INDEX, "City early poe cycle segment"},
          {"fan tower", HND_FAN_TOWER_INDEX, "Final fan room in City"},
          {"argorok", HND_ARGOROK_INDEX, "City in the Sky boss"},
          {"star 2", HND_STAR_2_INDEX, "The 2nd STAR minigame"},
          {"palace 1", HND_PALACE_1_INDEX, "The 1st Palace of Twilight segment"},
          {"palace 2", HND_PALACE_2_INDEX, "The 2nd Palace of Twilight segment"},
          {"early platform cycle", HND_EARLY_PLATFORM_INDEX,
           "Early platform in Palace of Twilight"},
          {"zant", HND_ZANT_INDEX, "Palace of Twilight boss"},
          {"cave of ordeals", HND_COO_INDEX, "The Cave of Ordeals segment"},
          {"coo floor 10", HND_COO_10_INDEX, "Cave of Ordeals floor 10"},
          {"coo floor 20", HND_COO_20_INDEX, "Cave of Ordeals floor 20"},
          {"coo floor 30", HND_COO_30_INDEX, "Cave of Ordeals floor 30"},
          {"coo floor 40", HND_COO_40_INDEX, "Cave of Ordeals floor 40"},
          {"cats minigame", HND_CATS_INDEX, "Hidden Village cats minigame"},
          {"hyrule castle", HND_HYRULE_INDEX, "The Hyrule Castle segment"},
          {"darknut skip", HND_DARKNUT_SKIP_INDEX, "Hyrule Castle 1st Darknut skip"},
          {"final tower", HND_FINAL_TOWER_INDEX, "The tower climb before Ganondorf"},
          {"beast ganon", HND_BEAST_GANON_INDEX, "The Beast Ganon fight"},
          {"horseback ganon", HND_HORSEBACK_GANON_INDEX, "The Horseback Ganondorf fight"},
      } {}

HundoSavesMenu::~HundoSavesMenu() {}

void HundoSavesMenu::draw() {
    special HundoSpecials[HND_SPECIALS_AMNT] = {
        special(HND_GOATS_1_INDEX, SaveMngSpecial_Goats1, nullptr),
        special(HND_MIST_INDEX, SaveMngSpecial_PurpleMist, nullptr),
        special(HND_KARG_INDEX, SaveMngSpecial_KargOoB, nullptr),
        special(HND_KB_2_INDEX, SaveMngSpecial_KB2Skip, nullptr),
        special(HND_ESCORT_INDEX, SaveMngSpecial_Escort, SaveMngSpecial_EscortKeys),
        special(HND_DANGORO_INDEX, nullptr, SaveMngSpecial_Dangoro),
        special(HND_LAKEBED_BK_SKIP_INDEX, SaveMngSpecial_LakebedBKSkip, nullptr),
        special(HND_MORPHEEL_INDEX, nullptr, SaveMngSpecial_Morpheel),
        special(HND_IZA_1_SKIP_INDEX, SaveMngSpecial_Iza1Skip, nullptr),
        special(HND_STALLORD_INDEX, nullptr, SaveMngSpecial_Stallord),
        special(HND_DARK_HAMMER_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(HND_LAKEBED_1_INDEX, SaveMngSpecial_BossFlags, nullptr),
        special(HND_SPR_BK_ROOM_INDEX, SaveMngSpecial_SPRBossKey, nullptr),
        special(HND_EARLY_POE_INDEX, nullptr, SaveMngSpecial_ToTEarlyPoe),
        special(HND_EARLY_HP_INDEX, nullptr, SaveMngSpecial_ToTEarlyHP),
        special(HND_POE_CYCLE_INDEX, nullptr, SaveMngSpecial_CityPoeCycle),
        special(HND_FAN_TOWER_INDEX, SaveMngSpecial_FanTower, nullptr),
        special(HND_ARGOROK_INDEX, nullptr, SaveMngSpecial_Argorok),
        special(HND_PALACE_1_INDEX, SaveMngSpecial_Palace1, nullptr),
        special(HND_PALACE_2_INDEX, nullptr, SaveMngSpecial_Palace2),
        special(HND_COO_INDEX, SaveMngSpecial_CaveOfOrdeals, nullptr),
        special(HND_COO_10_INDEX, SaveMngSpecial_CaveOfOrdeals, nullptr),
        special(HND_COO_20_INDEX, SaveMngSpecial_CaveOfOrdeals, nullptr),
        special(HND_COO_30_INDEX, SaveMngSpecial_CaveOfOrdeals, nullptr),
        special(HND_COO_40_INDEX, SaveMngSpecial_CaveOfOrdeals, nullptr),
    };

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        SaveManager::triggerLoad(cursor.y, "hundo", HundoSpecials, HND_SPECIALS_AMNT);
        g_menuMgr->hide();
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}