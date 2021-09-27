#include "menus/any_saves_menu.h"
#include "controller.h"
#include "fifo_queue.h"
#include "gorge.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/practice_menu.h"
#include "rollcheck.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "utils/loading.h"
#include "libtp_c/include/utils.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "libtp_c/include/rel/d/a/b/d_a_b_ds.h"
#include "libtp_c/include/rel/d/a/obj/d_a_obj_lv4sand.h"
#include "libtp_c/include/f_op/f_op_actor_iter.h"

#include "fs.h"
#define LINES 50

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
    {"stallord 2", STALLORD2_INDEX, "Stallord 2nd phase"},
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
    dComIfGs_onSwitch(47, 0);   // midna trigger off
    dComIfGs_offSwitch(63, 0);  // hugo alive
}

void spawn_hugo() {
    gSaveManager.setSaveAngle(40166);
    gSaveManager.setSavePosition(2.9385, 396.9580, -18150.087);
    gSaveManager.setLinkInfo();

    cXyz position(-289.9785, 401.5400, -18533.078);
    fopAcM_create(468, 0x0000F100, &position, dComIfGp_getPlayer()->mCurrent.mRoomNo,
                  &dComIfGp_getPlayer()->mCurrent.mAngle, nullptr, 0xFF);
}

void karg_oob() {
    gSaveManager.mPracticeFileOpts.inject_options_before_load = nullptr;
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0xA;  // spawn on kargorok
    dComIfGs_setTransformStatus(STATUS_HUMAN);
}

void morpheel() {
    dComIfGp_getPlayer()->mHeldItem = HOOKSHOT;                       // clawshot
    dComIfGp_getPlayer()->onNoResetFlg0(daPy_py_c::EquipHeavyBoots);  // ib
}

void stallord_2() {
    gSaveManager.mPracticeFileOpts.inject_options_after_counter = 20;

    daB_DS_c* stallord = (daB_DS_c*)fopAcM_SearchByName(246);          // stallord proc name
    daObjLv4Sand_c* sand = (daObjLv4Sand_c*)fopAcM_SearchByName(189);  // sand proc name

    if (stallord != NULL) {
        stallord->mBase.mParameters |= 0x2;   // make actor phase 2 version
        stallord->mAttentionInfo.mFlags = 4;  // makes stallord targetable when hit down
        stallord->mActionMode1 = 1;           // make stallord head active
        stallord->mGravity = 0.0f;            // change gravity to 0
        g_env_light.mWeatherPalette = 2;      // set arena light
        sand->mSpeed.y = 1000.0f;             // move sand out of the way

        dComIfGs_onOneZoneSwitch(6, stallord->mCurrent.mRoomNo);
        dComIfGs_onZoneSwitch(7, stallord->mCurrent.mRoomNo);  // sets arena to raised

        stallord->mCurrent.mPosition.x = -2097.20f;  //-2397.22f;
        stallord->mCurrent.mPosition.y = 1022.21f;   // 1697.20f;
        stallord->mCurrent.mPosition.z = -1246.87f;  // 1131.33f;

        dComIfGp_getPlayer()->mCurrent.mPosition.x = 644.91f;
        dComIfGp_getPlayer()->mCurrent.mPosition.y = 300.3158f;
        dComIfGp_getPlayer()->mCurrent.mPosition.z = 2195.0237f;
        dComIfGp_getPlayer()->mCollisionRot.mY = 39350;
        // tp_matrixInfo.matrix_info->target = {865.203f, -1414.390f, 2496.8774f};
        // tp_matrixInfo.matrix_info->pos = {644.438f, -1480.324f, 2194.693f};
    }
}

void stallord2_init() {
    gSaveManager.repeat_during = true;
    gSaveManager.repeat_count = 120;

    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
}

void stallord() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
}

void fan_tower() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] = 0;  // reset city switches
}

void argorok() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x10000;
}

void palace1() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] = 0;  // reset palace switches
}

void palace2() {
    dComIfGp_getPlayer()->mHeldItem = 3;  // master sword
}

void lakebed_bk_skip_during() {
    gSaveManager.inject_default_during();
    dComIfGs_onSwitch(2, 0);    // bridge turned
    dComIfGs_onSwitch(122, 0);  // dungeon intro cs off
}

void bossflags() {
    gSaveManager.inject_default_during();
    tp_bossFlags = 0xFF;
}

void darkhammer() {
    dComIfGs_onEventBit(0x0B02);
    dComIfGs_onEventBit(0x0B04);  // iza bomb bag stolen
}

void waterfall_sidehop() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 10.0f;  // link spawns swimming forward
}

void AnySavesMenu::render() {
    special AnySpecials[ANY_SPECIALS_AMNT] = {
        special(HUGO_INDEX, hugo, spawn_hugo),
        special(KARG_INDEX, karg_oob, nullptr),
        special(LAKEBED_BK_SKIP_INDEX, lakebed_bk_skip_during, nullptr),
        special(ONEBOMB_INDEX, nullptr, morpheel),
        special(STALLORD_INDEX, stallord, nullptr),
        special(STALLORD2_INDEX, stallord2_init, stallord_2),
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