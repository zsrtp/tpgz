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
#include "libtp_c/include/f_op/f_op_draw_tag.h"

#include "fs.h"
#define LINES 82

#define REQ_POS 1
#define REQ_CAM 2

static Cursor cursor = {0, 0};
bool init_once = false;

Line lines[LINES] = {
    {"goats 1", HND_GOATS_1_INDEX, "goat herding 1"},
    {"ordon gate clip", HND_ORDON_GATE_CLIP_INDEX, "gate clip outside ordon spring"},
    {"goats 2", HND_GOATS_2_INDEX, "goat herding 2"},
    {"faron twilight", HND_FARON_TWILIGHT_INDEX, "faron twilight tears"},
    {"early master sword", HND_EMS_INDEX, "super jump to early sacred grove"},
    {"purple mist", HND_MIST_INDEX, "purple mist in faron woods (post EMS)"},
    {"forest bit", HND_FRST_BIT_INDEX, "back in time in forest temple"},
    {"forest temple 2", HND_FRST_2_INDEX, "the forest temple segment after boomerang"},
    {"diababa", HND_OOKLESS_INDEX, "the forest temple boss"},
    {"eldin twilight", HND_ELDIN_TWILIGHT_INDEX, "eldin twilight tears"},
    {"lanayru gate clip", HND_LANAYRU_GATE_CLIP_INDEX, "gate clip outside lake hylia"},
    {"pillar clip", HND_PILLAR_CLIP_INDEX, "pillar clip in lake hylia (low water)"},
    {"lakebed 1", HND_LAKEBED_1_INDEX, "the first lakebed segment"},
    {"deku toad", HND_TOAD_INDEX, "the miniboss of lakebed temple"},
    {"kargorok flight", HND_KARG_INDEX, "clip oob with trumpet bird"},
    {"lanayru twilight", HND_LANAYRU_TWILIGHT_INDEX, "lanayru twilight tears"},
    {"boss bug", HND_BOSS_BUG_INDEX, "lanayru twilight boss bug"},
    {"king bulblin 2 skip", HND_KB_2_INDEX, "clip to skip king bulblin 2"},
    {"wagon escort", HND_ESCORT_INDEX, "telma wagon escort segment"},
    {"coro td", HND_COROTD_INDEX, "text displacement with coro"},
    {"goron mines", HND_GM_INDEX, "the goron mines segment"},
    {"dangoro", HND_DANGORO_INDEX, "the goron mines miniboss"},
    {"king bulblin 1", HND_KB_1_INDEX, "the king bulblin 1 fight"},
    {"lakebed bk skip", HND_LAKEBED_BK_SKIP_INDEX, "boss key skip in lakebed main room"},
    {"morpheel", HND_MORPHEEL_INDEX, "the lakebed temple boss"},
    {"star 1", HND_STAR_1_INDEX, "the first STAR minigame"},
    {"mdh tower", HND_MDH_TOWER_INDEX, "mdh tower climb before castle rooftops"},
    {"mdh bridge", HND_MDH_BRIDGE_INDEX, "the falling bridge on castle rooftops"},
    {"post mdh", HND_POST_MDH_INDEX, "the beginning of the first collection cycle"},
    {"mountain climb", HND_MOUNTAIN_INDEX, "the climb up snowpeak"},
    {"iza 1 skip", HND_IZA_1_SKIP_INDEX, "plumm oob clip to skip iza boat ride"},
    {"iza 2", HND_IZA_2_INDEX, "the iza minigame"},
    {"lake hylia cave", HND_LH_CAVE_INDEX, "the lake hylia dark cave"},
    {"bulblin camp", HND_BULBLIN_CAMP_INDEX, "the area before arbiter's grounds"},
    {"arbiter's grounds", HND_AG_INDEX, "the arbiter's grounds segment"},
    {"poe 1 skip", HND_POE_1_SKIP_INDEX, "the pillar jump in arbiter's grounds"},
    {"death sword", HND_DSS_INDEX, "the arbiter's grounds miniboss"},
    {"stallord", HND_STALLORD_INDEX, "the arbiter's grounds boss"},
    {"gorge arc", HND_GORGE_INDEX, "the collection cycle from gorge to snowpeak"},
    {"snowpeak", HND_SPR_INDEX, "the snowpeak dungeon segment"},
    {"darkhammer", HND_DARK_HAMMER_INDEX, "The snowpeak miniboss"},
    {"spr superjump", HND_SPR_SUPERJUMP_INDEX, "the snowpeak superjump to second floor"},
    {"spr boss key lja", HND_SPR_BK_LJA_INDEX, "the lja to get to snowpeak boss key early"},
    {"spr boss key room", HND_SPR_BK_ROOM_INDEX, "the snowpeak boss key room"},
    {"blizzeta", HND_BLIZZETA_INDEX, "the snowpeak ruins boss"},
    {"faron bomb boost", HND_BOMB_BOOST_INDEX, "the bomb boost to sacred grove"},
    {"grove 2", HND_GROVE_2_INDEX, "the second skull kid chase"},
    {"temple of time", HND_TOT_INDEX, "the temple of time segment"},
    {"tot early poe", HND_EARLY_POE_INDEX, "early first poe in temple of time"},
    {"tot statue throws", HND_STATUE_THROWS_INDEX, "temple of time statue throws"},
    {"tot early hp", HND_EARLY_HP_INDEX, "temple of time bomb boost to heart piece"},
    {"tot darknut", HND_DARKNUT_INDEX, "the temple of time miniboss"},
    {"dot skip", HND_DOT_SKIP_INDEX, "statue clip through door of time"},
    {"armogohma", HND_ARMOGOHMA_INDEX, "the temple of time boss"},
    {"post tot", HND_POST_TOT_INDEX, "the collection cycle after temple of time"},
    {"hotspring minigame", HND_HOTSPRING_INDEX, "the goron hotspring water minigame"},
    {"silver rupee", HND_BELL_INDEX, "kakariko silver rupee collection"},
    {"rupee isle", HND_FBF_INDEX, "the rupee isle collection"},
    {"ice puzzle", HND_PUZZLE_INDEX, "the ice puzzle segment"},
    {"hugo archery", HND_ARCHERY_INDEX, "the first hidden village trip"},
    {"city in the sky early", HND_CITY_EARLY_INDEX, "clip to the canon early"},
    {"city in the sky 1", HND_CITY_1_INDEX, "the first city in the sky segment"},
    {"aeralfos skip", HND_AERALFOS_INDEX, "the city in the sky miniboss"},
    {"city in the sky 2", HND_CITY_2_INDEX, "the second city in the sky segment"},
    {"early poe cycle", HND_POE_CYCLE_INDEX, "early poe cycle segment"},
    {"fan tower", HND_FAN_TOWER_INDEX, "final fan room in city before the boss"},
    {"argorok", HND_ARGOROK_INDEX, "the city in the sky boss"},
    {"star 2", HND_STAR_2_INDEX, "the second STAR minigame"},
    {"palace of twilight 1", HND_PALACE_1_INDEX, "the first palace of twilight segment"},
    {"palace of twilight 2", HND_PALACE_2_INDEX, "the second palace of twilight segment"},
    {"early platform cycle", HND_EARLY_PLATFORM_INDEX, "early platform in palace of twilight"},
    {"zant", HND_ZANT_INDEX, "the palace of twilight boss"},
    {"cave of ordeals", HND_COO_INDEX, "the cave of ordeals segment"},
    {"coo floor 10", HND_COO_10_INDEX, "cave of ordeals floor 10"},
    {"coo floor 20", HND_COO_20_INDEX, "cave of ordeals floor 20"},
    {"coo floor 30", HND_COO_30_INDEX, "cave of ordeals floor 30"},
    {"cats minigame", HND_CATS_INDEX, "hidden village cats minigame"},
    {"hyrule castle", HND_HYRULE_INDEX, "the hyrule castle segment"},
    {"darknut skip", HND_DARKNUT_SKIP_INDEX, "hyrule castle darknut skip"},
    {"final tower", HND_FINAL_TOWER_INDEX, "the tower climb before the final boss fights"},
    {"beast ganon", HND_BEAST_GANON_INDEX, "the beast ganon fight"},
    {"horseback ganon", HND_HORSEBACK_GANON_INDEX, "the horseback ganon fight"}};

void default_load() {
    gSaveManager.mPracticeFileOpts.inject_options_before_load = SaveManager::inject_default_before;
    gSaveManager.mPracticeFileOpts.inject_options_during_load = SaveManager::inject_default_during;
    gSaveManager.mPracticeFileOpts.inject_options_after_load = SaveManager::inject_default_after;
    inject_save_flag = true;
    fifo_visible = true;
    MenuRendering::set_menu(MN_NONE_INDEX);
    init_once = false;
}

void set_camera_angle_position() {
    tp_matrixInfo.matrix_info->target = gSaveManager.mPracticeSaveInfo.cam_target;
    tp_matrixInfo.matrix_info->pos = gSaveManager.mPracticeSaveInfo.cam_pos;
    dComIfGp_getPlayer()->mCollisionRot.mY = gSaveManager.mPracticeSaveInfo.angle;
    cXyz tmp(gSaveManager.mPracticeSaveInfo.position.x, gSaveManager.mPracticeSaveInfo.position.y, gSaveManager.mPracticeSaveInfo.position.z);
    dComIfGp_getPlayer()->mCurrent.mPosition = tmp;
}

void set_angle_position() {
    dComIfGp_getPlayer()->mCollisionRot.mY = gSaveManager.mPracticeSaveInfo.angle;
    cXyz tmp(gSaveManager.mPracticeSaveInfo.position.x, gSaveManager.mPracticeSaveInfo.position.y, gSaveManager.mPracticeSaveInfo.position.z);
    dComIfGp_getPlayer()->mCurrent.mPosition = tmp;
}

void goats_1() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.play.mNextStage.mLayer = 0x5;
}

void goats_2() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.play.mNextStage.mLayer = 0x4;
}

void purple_mist() {
    gSaveManager.inject_default_during();
    dComIfGs_setTransformStatus(STATUS_HUMAN);
}

void kb2_skip() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.play.mNextStage.mLayer = 0x3;
}

void escort() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.play.mNextStage.mRoomNo = 0xD;
    g_dComIfG_gameInfo.play.mNextStage.mPoint = 0x62;
    g_dComIfG_gameInfo.play.mNextStage.mLayer = 0x2;
    dComIfGs_setKeyNum(2); // give 2 keys for field gates
}

void dangoro() {
    g_dComIfG_gameInfo.mInfo.mZone[0].mBit.mSwitch[0] |= 0x200000;  // turn off intro cs, start fight
}

void morpheel() {
    dComIfGp_getPlayer()->field_0x2fdc = 68;  // clawshot
    dComIfGp_getPlayer()->onNoResetFlg0(daPy_py_c::EquipHeavyBoots);  // ib
    gSaveManager.mPracticeSaveInfo.angle = 10754;
    gSaveManager.mPracticeSaveInfo.position = {-1193.0f, -23999.0f, -770.0f};
    set_angle_position();
}

void karg_oob() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.mInfo.mRestart.mLastMode = 0xA;  // spawn on kargorok
    dComIfGs_setTransformStatus(STATUS_HUMAN);
}

void iza_1_skip() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.mInfo.mRestart.mLastMode = 0xA;                           // spawn on kargorok
    tp_strcpy((char*)g_dComIfG_gameInfo.play.mNextStage.mStage, "F_SP112");  // set stage to river
    g_dComIfG_gameInfo.play.mNextStage.mRoomNo = 0x1;
    g_dComIfG_gameInfo.play.mNextStage.mPoint = 0x0;
    g_dComIfG_gameInfo.play.mNextStage.mLayer = 0x4;
}

void stallord() {
    g_dComIfG_gameInfo.mInfo.mZone[0].mBit.mSwitch[0] |= 0x300000; // turn off intro cs, start fight
    g_dComIfG_gameInfo.play.mNextStage.mPoint = 0x01;  // spawn at in front of stally
}

void spr_bosskey() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.play.mNextStage.mRoomNo = 0xB;    // boss key room
    g_dComIfG_gameInfo.play.mNextStage.mPoint = 0x00;  // default spawn
}

void tot_early_poe() {
    gSaveManager.inject_default_during();
    gSaveManager.mPracticeSaveInfo.angle = 49299;
    gSaveManager.mPracticeSaveInfo.position = {-2462.85f, 2750.0f, -7.10f};
    set_angle_position();
}

void tot_early_hp() {
    gSaveManager.inject_default_during();
    gSaveManager.mPracticeSaveInfo.angle = 49152;
    gSaveManager.mPracticeSaveInfo.position = {-8000.50f, 5100.0f, -3226.17f};
    set_angle_position();
}

void hugo_archery() {
    gSaveManager.inject_default_during();
    // tp_gameInfo.temp_flags.flags[14] = 0xC0;  // start archery minigame
}

void cits_poe_cycle() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.play.mNextStage.mPoint = 0x0;
    gSaveManager.mPracticeSaveInfo.angle = 71;
    gSaveManager.mPracticeSaveInfo.position = {-14005.31f, 3000.0f, -15854.05f};
    set_angle_position();
}

void fan_tower() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.mInfo.mDan.mSwitch[0] = 0;
}

void argorok() {
    g_dComIfG_gameInfo.mInfo.mZone[0].mBit.mSwitch[0] |= 0x10000;
    
}

void palace1() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.mInfo.mDan.mSwitch[0] = 0;
}

void palace2() {
    dComIfGp_getPlayer()->field_0x2fdc = 3;  // master sword
    gSaveManager.inject_default_during();
    gSaveManager.mPracticeSaveInfo.angle = 32731;
    gSaveManager.mPracticeSaveInfo.position = {251.83f, -200.0f, 10993.50f};
    set_angle_position();
}

void lakebed_bk_skip_during() {
    gSaveManager.inject_default_during();
    dComIfGs_onSwitch(122, dComIfGp_getPlayer()->mOrig.mRoomNo); // dungeon intro cs off
}

void bossflags() {
    gSaveManager.inject_default_during();
    tp_bossFlags = 0xFF;
}

void cave_of_ordeals() {
    gSaveManager.inject_default_during();
    g_dComIfG_gameInfo.mInfo.mDan.mSwitch[0] = 0;
}

void HundoSavesMenu::render() {
    special HundoSpecials[HND_SPECIALS_AMNT] = {
        special(HND_GOATS_1_INDEX, goats_1, nullptr),
        special(HND_GOATS_2_INDEX, goats_2, nullptr),
        special(HND_MIST_INDEX, purple_mist, nullptr),
        special(HND_KARG_INDEX, karg_oob, nullptr),
        special(HND_KB_2_INDEX, kb2_skip, nullptr),
        special(HND_ESCORT_INDEX, escort, nullptr),
        special(HND_DANGORO_INDEX, nullptr, dangoro),
        special(HND_LAKEBED_BK_SKIP_INDEX, lakebed_bk_skip_during, nullptr),
        special(HND_MORPHEEL_INDEX, nullptr, morpheel),
        special(HND_IZA_1_SKIP_INDEX, iza_1_skip, nullptr),
        special(HND_STALLORD_INDEX, nullptr, stallord),
        special(HND_DARK_HAMMER_INDEX, bossflags, nullptr),
        special(HND_DARK_HAMMER_INDEX, bossflags, nullptr),
        special(HND_LAKEBED_1_INDEX, bossflags, nullptr),
        special(HND_SPR_BK_ROOM_INDEX, spr_bosskey, nullptr),
        special(HND_EARLY_POE_INDEX, tot_early_poe, nullptr),
        special(HND_EARLY_HP_INDEX, tot_early_hp, nullptr),
        special(HND_CITY_EARLY_INDEX, hugo_archery, nullptr),
        special(HND_POE_CYCLE_INDEX, cits_poe_cycle, nullptr),
        special(HND_FAN_TOWER_INDEX, fan_tower, nullptr),
        special(HND_ARGOROK_INDEX, nullptr, argorok),
        special(HND_PALACE_1_INDEX, palace1, nullptr),
        special(HND_PALACE_2_INDEX, nullptr, palace2),
        special(HND_COO_INDEX, cave_of_ordeals, nullptr),
        special(HND_COO_10_INDEX, cave_of_ordeals, nullptr),
        special(HND_COO_20_INDEX, cave_of_ordeals, nullptr),
        special(HND_COO_30_INDEX, cave_of_ordeals, nullptr)};

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
        SaveManager::load_save(cursor.y, (char*)"hundo", HundoSpecials, HND_SPECIALS_AMNT);
        init_once = false;
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(lines, cursor.y, LINES);
};