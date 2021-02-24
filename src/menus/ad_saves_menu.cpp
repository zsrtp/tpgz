#include "menus/ad_saves_menu.h"
#include "controller.h"
#include "fifo_queue.h"
#include "gorge.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menus/practice_menu.h"
#include "rollcheck.h"
#include "save_injector.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "utils/loading.h"

#include "fs.h"
#define LINES 50

static Cursor cursor = {0, 0};
bool init_once = false;

Line lines[LINES] = {
    {"ordon gate clip", AD_ORDON_GATE_CLIP_INDEX, "Gate Clip outside Ordon Spring"},
    {"back in time", AD_BIT_INDEX, "Back In Time off the Ordon Spring bridge"},
    {"goats", AD_GOATS_INDEX, "Goat herding 2"},
    {"sword and shield skip", AD_HUGO_INDEX, "Hangin' with Hugo"},
    {"faron twilight", AD_FARON_TWILGHT_INDEX, "Faron Twilight 1st half"},
    {"early master sword", AD_EMS_INDEX, "Super Jump to early Sacred Grove"},
    {"purple mist", AD_MIST_INDEX, "Purple mist in Faron Woods (post-EMS)"},
    {"forest bit", AD_FRST_BIT_INDEX, "Back In Time in Forest Temple"},
    {"forest escape", AD_FRST_ESCAPE_INDEX, "LJA over S Faron exit trigger"},
    {"pillar clip", AD_PILLAR_CLIP_INDEX, "Pillar Clip in Lake Hylia (low water)"},
    {"lakebed 1", AD_LAKEBED_1_INDEX, "The first Lakebed Temple segment"},
    {"deku toad", AD_TOAD_INDEX, "The miniboss of Lakebed Temple"},
    {"kargorok flight", AD_KARG_INDEX, "Clip OoB with trumpet bird"},
    {"forest temple 2", AD_FT2_INDEX, "Second half of Forest Temple"},
    {"diababa", AD_DIABABA_INDEX, "The Forest Temple boss"},
    {"eldin twilight", AD_ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
    {"lanayru twilight", AD_LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
    {"post lanayru", AD_POST_LANAYRU_INDEX, "Stealing Iza's bombs"},
    {"lakebed bk skip", AD_BK_SKIP_INDEX, "Boss key skip in Lakebed Temple main room"},
    {"morpheel", AD_MORPHEEL_INDEX, "Morpheel fight (no Zora Armor)"},
    {"mdh", AD_MDH_INDEX, "MDH segment"},
    {"mountain", AD_MOUNTAIN_INDEX, "Climbing up Snowpeak mountain"},
    {"snowpeak", AD_SPR_INDEX, "The Snowpeak Ruins dungeon segment"},
    {"dark hammer", AD_DARK_HAMMER_INDEX, "The Snowpeak Ruins miniboss"},
    {"snowpeak bomb boost", AD_SPR_BOOST_INDEX, "Bomb boost to SPR 2nd floor"},
    {"blizzeta", AD_BLIZZETA_INDEX, "The Snowpeak Ruins boss"},
    {"arbiter's grounds", AD_AG_INDEX, "The Arbiter's Grounds segment"},
    {"poe 1 skip", AD_POE_SKIP_INDEX, "The pillar jump in Arbiter's Grounds"},
    {"death sword", AD_DSS_INDEX, "The Arbiter's Grounds miniboss"},
    {"stallord", AD_STALLORD_INDEX, "The Arbiter's Grounds boss"},
    {"early elevator", AD_EARLY_ELE_INDEX, "OoB clip to DM elevator"},
    {"goron mines", AD_GM_INDEX, "The Goron Mines segment"},
    {"dangoro", AD_DANGORO_INDEX, "The Goron Mines miniboss"},
    {"silver rupee", AD_RUPEE_INDEX, "Silver Rupee collection"},
    {"city in the sky 1", AD_CITS_1_INDEX, "The first City in the Sky segment"},
    {"aeralfos skip", AD_AERALFOS_INDEX, "The City in the Sky miniboss"},
    {"city in the sky 2", AD_CITS_2_INDEX, "The second City in the Sky segment"},
    {"argorok", AD_ARGOROK_INDEX, "The City in the Sky boss"},
    {"faron bomb boost", AD_FARON_BOOST_INDEX, "Bomb boost to Sacred Grove"},
    {"grove 2", AD_GROVE_2_INDEX, "The 2nd Skullkid chase"},
    {"temple of time", AD_TOT_INDEX, "The Temple of Time segment"},
    {"darknut", AD_DARKNUT_INDEX, "The Temple of Time miniboss"},
    {"dot skip", AD_DOT_SKIP_INDEX, "Door of Time skip"},
    {"palace of twilight 1", AD_PALACE_1_INDEX, "The first Palace of Twilight segment"},
    {"palace of twilight 2", AD_PALACE_2_INDEX,
     "The second Palace of Twilight segment (after both Sols)"},
    {"early platform", AD_EARLY_PLATFORM_INDEX, "Early platform in Palace of Twilight"},
    {"zant", AD_ZANT_INDEX, "The Palace of Twilight boss"},
    {"hyrule castle", AD_HC_INDEX, "The Hyrule Castle segment"},
    {"beast ganon", AD_BEAST_GANON_INDEX, "The Beast Ganon fight"},
    {"horseback ganon", AD_HORSEBACK_INDEX, "The horseback Ganondorf fight"}};

void default_load() {
    practice_file.inject_options_before_load = SaveInjector::inject_default_before;
    practice_file.inject_options_during_load = SaveInjector::inject_default_during;
    practice_file.inject_options_after_load = SaveInjector::inject_default_after;
    inject_save_flag = true;
    fifo_visible = true;
    MenuRendering::set_menu(MN_NONE_INDEX);
    init_once = false;
}

void hugo() {
    SaveInjector::inject_default_during();
    tp_gameInfo.temp_flags.flags[14] = 128;  // midna trigger off
    tp_gameInfo.temp_flags.flags[12] = 0;    // hugo alive
}

void karg_oob() {
    practice_file.inject_options_before_load = nullptr;
    SaveInjector::inject_default_during();
    tp_gameInfo.respawn_animation = 0xA;  // spawn on kargorok
    tp_gameInfo.link.is_wolf = false;
}

void morpheel() {
    tp_zelAudio.link_debug_ptr->current_item = 68;  // clawshot
    tp_zelAudio.link_debug_ptr->current_boots = 2;  // ib
}

void stallord() {
    SaveInjector::inject_default_during();
    tp_gameInfo.boss_room_event_flags = 48;  // turn off intro cs, start fight
    tp_gameInfo.warp.entrance.spawn = 0x01;  // spawn at in front of stally
}

void argorok() {
    SaveInjector::inject_default_during();
    tp_gameInfo.boss_room_event_flags = 1;
}

void palace1() {
    SaveInjector::inject_default_during();
    tp_gameInfo.dungeon_temp_flags.switch_bitfield[0] = 0;  // reset palace switches
}

void palace2() {
    tp_zelAudio.link_debug_ptr->current_item = 3;  // master sword
}

void lakebed_bk_skip_during() {
    SaveInjector::inject_default_during();
    tp_gameInfo.temp_flags.flags[11] = 18;   // bridge turned
    tp_gameInfo.temp_flags.flags[20] = 223;  // dungeon intro cs off
}

void bossflags() {
    SaveInjector::inject_default_during();
    TP::set_boss_flags();
}

void darkhammer() {
    tp_gameInfo.event_flags.flags[11] = 134;  // iza bomb bag stolen
}

void ADSavesMenu::render() {
    special ADSpecials[AD_SPECIALS_AMNT] = {
        special(AD_HUGO_INDEX, hugo, nullptr),
        special(AD_KARG_INDEX, karg_oob, nullptr),
        special(AD_BK_SKIP_INDEX, lakebed_bk_skip_during, nullptr),
        special(AD_MORPHEEL_INDEX, nullptr, morpheel),
        special(AD_STALLORD_INDEX, stallord, nullptr),
        special(AD_FRST_ESCAPE_INDEX, bossflags, nullptr),
        special(AD_PILLAR_CLIP_INDEX, bossflags, nullptr),
        special(AD_LAKEBED_1_INDEX, bossflags, nullptr),
        special(AD_DARK_HAMMER_INDEX, bossflags, darkhammer),
        special(AD_ARGOROK_INDEX, argorok, nullptr),
        special(AD_PALACE_1_INDEX, palace1, nullptr),
        special(AD_PALACE_2_INDEX, nullptr, palace2)};

    if (button_is_pressed(BACK_BUTTON)) {
        MenuRendering::set_menu(MN_PRACTICE_INDEX);
        init_once = false;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == SELECTION_BUTTON && a_held == false) {
        Utilities::load_save(cursor.y, (char*)"ad", ADSpecials, AD_SPECIALS_AMNT);
        init_once = false;
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(lines, cursor.y, LINES);
};