#include "menus/any_saves_menu.h"
#include "controller.h"
#include "fifo_queue.h"
#include "gorge.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menus/practice_menu.h"
#include "rollcheck.h"

#include "utils/cursor.h"
#include "utils/lines.h"
#include "utils/loading.h"

#include "fs.h"
#define LINES 49

static Cursor cursor = {0, 0};
bool init_once = false;

Line lines[LINES] = {
    {"ordon gate clip", ORDON_GATE_CLIP_INDEX, "Gate Clip outside Ordon Spring"},
    {"back in time", BACK_IN_TIME_INDEX, "Back In Time off the Ordon Spring bridge"},
    {"goats", GOATS_INDEX, "Goat herding 2"},
    {"sword and shield skip", HUGO_INDEX, "Hangin' with Hugo"},
    {"early master sword", EMS_INDEX, "Super Jump to early Sacred Grove"},
    {"purple mist", MIST_INDEX, "Purple mist in Faron Woods (post-EMS)"},
    {"forest bit", FRST_BIT_INDEX, "Back In Time in Forest Temple"},
    {"forest escape", FRST_ESCAPE_INDEX, "LJA over S Faron exit trigger"},
    {"gorge void", GORGE_VOID_INDEX, "1 frame jump attack into faron gorge"},
    {"rupee roll", RUPEE_ROLL_INDEX, "LJA onto fence + pick up rupee"},
    {"lanayru gate clip", LANAYRU_GATE_CLIP_INDEX, "Gate Clip outside Lake Hylia"},
    {"pillar clip", PILLAR_CLIP_INDEX, "Pillar Clip in Lake Hylia (low water)"},
    {"lakebed 1", LAKEBED_1_INDEX, "The first Lakebed Temple segment"},
    {"deku toad", TOAD_INDEX, "The miniboss of Lakebed Temple"},
    {"kargorok flight", KARG_INDEX, "Clip OoB with trumpet bird"},
    {"eldin twilight", ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
    {"lanayru twilight", LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
    {"waterfall sidehop", WATERFALL_SIDEHOP_INDEX, "Waterfall sidehop after Rutela skip"},
    {"boss bug", BOSS_BUG_INDEX, "Lanayru Twilight boss bug"},
    {"iza", IZA_INDEX, "Steal Iza's bomb bag"},
    {"norgor", NORGOR_INDEX, "Goron bomb bag without water bombs"},
    {"snowpeak messenger skip", SPR_WARP_SKIP_INDEX, "LJA to skip the Snowpeak messenger fight"},
    {"snowpeak", SPR_INDEX, "The Snowpeak Ruins dungeon segment"},
    {"dark hammer", DARK_HAMMER_INDEX, "The Snowpeak Ruins miniboss"},
    {"lakebed 2", LAKEBED_2_INDEX, "The second Lakebed Temple segment"},
    {"lakebed bk skip", LAKEBED_BK_SKIP_INDEX, "Boss key skip in Lakebed Temple main room"},
    {"morpheel", ONEBOMB_INDEX, "Morpheel fight (no Zora Armor)"},
    {"mdh tower", MDH_TOWER_INDEX, "MDH tower climb before castle rooftops"},
    {"mdh bridge", MDH_BRIDGE_INDEX, "The falling bridge on castle rooftops"},
    {"bulblin camp", BULBLIN_CAMP_INDEX, "The area before Arbiter's Grounds"},
    {"arbiter's grounds", AG_INDEX, "The Arbiter's Grounds segment"},
    {"poe 1 skip", POE_1_SKIP_INDEX, "The pillar jump in Arbiter's Grounds"},
    {"death sword", DSS_INDEX, "The Arbiter's Grounds miniboss"},
    {"stallord", STALLORD_INDEX, "The Arbiter's Grounds boss"},
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
    {"horseback ganon", HORSEBACK_GANON_INDEX, "The horseback Ganondorf fight"}};

void hugo() {
    gSaveManager.inject_default_during();
    tp_gameInfo.temp_flags.flags[14] = 128;  // midna trigger off
    tp_gameInfo.temp_flags.flags[12] = 0;    // hugo alive
}

void karg_oob() {
    gSaveManager.mPracticeFileOpts.inject_options_before_load = nullptr;
    gSaveManager.inject_default_during();
    tp_gameInfo.respawn_animation = 0xA;  // spawn on kargorok
    tp_gameInfo.link.is_wolf = false;
}

void morpheel() {
    tp_zelAudio.link_debug_ptr->current_item = 68;  // clawshot
    tp_zelAudio.link_debug_ptr->current_boots = 2;  // ib
}

void stallord() {
    gSaveManager.inject_default_during();
    tp_gameInfo.boss_room_event_flags = 48;  // turn off intro cs, start fight
    tp_gameInfo.warp.entrance.spawn = 0x01;  // spawn at in front of stally
}

void fan_tower() {
    gSaveManager.inject_default_during();
    tp_gameInfo.dungeon_temp_flags.switch_bitfield[0] = 0;  // reset city switches
}

void argorok() {
    gSaveManager.inject_default_during();
    tp_gameInfo.boss_room_event_flags = 1;
}

void palace1() {
    gSaveManager.inject_default_during();
    tp_gameInfo.dungeon_temp_flags.switch_bitfield[0] = 0;  // reset palace switches
}

void palace2() {
    tp_zelAudio.link_debug_ptr->current_item = 3;  // master sword
}

void lakebed_bk_skip_during() {
    gSaveManager.inject_default_during();
    tp_gameInfo.temp_flags.flags[11] = 18;   // bridge turned
    tp_gameInfo.temp_flags.flags[20] = 223;  // dungeon intro cs off
}

void bossflags() {
    gSaveManager.inject_default_during();
    TP::set_boss_flags();
}

void darkhammer() {
    tp_gameInfo.event_flags.flags[11] = 134;  // iza bomb bag stolen
}

void waterfall_sidehop() {
    gSaveManager.inject_default_during();
    tp_gameInfo.spawn_speed = 10.0f;  // link spawns swimming forward
}

void AnySavesMenu::render() {
    special AnySpecials[ANY_SPECIALS_AMNT] = {
        special(HUGO_INDEX, hugo, nullptr),
        special(KARG_INDEX, karg_oob, nullptr),
        special(LAKEBED_BK_SKIP_INDEX, lakebed_bk_skip_during, nullptr),
        special(ONEBOMB_INDEX, nullptr, morpheel),
        special(STALLORD_INDEX, stallord, nullptr),
        special(FRST_ESCAPE_INDEX, bossflags, nullptr),
        special(GORGE_VOID_INDEX, bossflags, nullptr),
        special(RUPEE_ROLL_INDEX, bossflags, nullptr),
        special(LANAYRU_GATE_CLIP_INDEX, bossflags, nullptr),
        special(PILLAR_CLIP_INDEX, bossflags, nullptr),
        special(LAKEBED_1_INDEX, bossflags, nullptr),
        special(WATERFALL_SIDEHOP_INDEX, waterfall_sidehop, nullptr),
        special(DARK_HAMMER_INDEX, bossflags, darkhammer),
        special(FAN_TOWER_INDEX, fan_tower, nullptr),
        special(ARGOROK_INDEX, argorok, nullptr),
        special(PALACE_1_INDEX, palace1, nullptr),
        special(PALACE_2_INDEX, nullptr, palace2)};

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
        SaveManager::load_save(cursor.y, (char*)"any", AnySpecials, ANY_SPECIALS_AMNT);
        init_once = false;
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(lines, cursor.y, LINES);
};