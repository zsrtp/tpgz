#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"
#include "fifo_queue.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "utils/loading.hpp"
#include "gorge.h"
#include "rollcheck.h"
#include "save_injector.h"

#include "fs.h"
#define LINES 82

static Cursor cursor = {0, 0};
static CameraMatrix camera = {{0, 0, 0}, {0, 0, 0}};
static uint16_t angle = 0;
static Vec3 position = {0, 0, 0};
bool init_once = false;
bool hundo_saves_visible;

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
    practice_file.inject_options_before_load = SaveInjector::inject_default_before;
    practice_file.inject_options_during_load = SaveInjector::inject_default_during;
    practice_file.inject_options_after_load = SaveInjector::inject_default_after;
    inject_save_flag = true;
    fifo_visible = true;
    prac_visible = false;
    hundo_saves_visible = false;
    mm_visible = false;
    init_once = false;
}

void set_camera_angle_position() {
    tp_matrixInfo.matrix_info->target = camera.target;
    tp_matrixInfo.matrix_info->pos = camera.pos;
    tp_zelAudio.link_debug_ptr->facing = angle;
    tp_zelAudio.link_debug_ptr->position = position;
}

void set_angle_position() {
    tp_zelAudio.link_debug_ptr->facing = angle;
    tp_zelAudio.link_debug_ptr->position = position;
}

void goats_1() {
    SaveInjector::inject_default_during();
    tp_gameInfo.warp.entrance.state = 0x5;
}

void goats_2() {
    SaveInjector::inject_default_during();
    tp_gameInfo.warp.entrance.state = 0x4;
}

void purple_mist() {
    SaveInjector::inject_default_during();
    tp_gameInfo.link.is_wolf = false;
}

void kb2_skip() {
    SaveInjector::inject_default_during();
    tp_gameInfo.epona_debug_ptr->position = {-92098.1797, -5563.54883, 22599.9102};  // spawn near clip spot
    tp_gameInfo.warp.entrance.state = 0x3;  
}

void escort() {
    SaveInjector::inject_default_during();
    tp_gameInfo.warp.entrance.room = 0xD;
    tp_gameInfo.warp.entrance.spawn = 0x62;
    tp_gameInfo.warp.entrance.state = 0x2;
    tp_gameInfo.temp_flags.flags[28] = 2;  // give 2 keys for field gates
}

void dangoro() {
    SaveInjector::inject_default_during();
    tp_gameInfo.boss_room_event_flags = 32;  // turn off intro cs, start fight
}

void morpheel() {
    tp_zelAudio.link_debug_ptr->current_item = 68;  // clawshot
    tp_zelAudio.link_debug_ptr->current_boots = 2;  // ib
    angle = 10754;
    position = {-1193.0f, -23999.0f, -770.0f};
    set_angle_position();
}

void karg_oob() {
    SaveInjector::inject_default_during();
    tp_gameInfo.respawn_animation = 0xA;  // spawn on kargorok
    tp_gameInfo.link.is_wolf = false;
}

void iza_1_skip() {
    SaveInjector::inject_default_during();
    tp_gameInfo.respawn_animation = 0xA;                        // spawn on kargorok
    strcpy((char*)tp_gameInfo.warp.entrance.stage, "F_SP112");  // set stage to river
    tp_gameInfo.warp.entrance.room = 0x1;
    tp_gameInfo.warp.entrance.spawn = 0x0;
    tp_gameInfo.warp.entrance.state = 0x4;
}

void stallord() {
    SaveInjector::inject_default_during();
    tp_gameInfo.boss_room_event_flags = 48;  // turn off intro cs, start fight
    tp_gameInfo.warp.entrance.spawn = 0x01;  // spawn at in front of stally
}

void spr_bosskey() {
    SaveInjector::inject_default_during();
    tp_gameInfo.warp.entrance.room = 0xB;    // boss key room
    tp_gameInfo.warp.entrance.spawn = 0x00;  // default spawn
}

void tot_early_poe() {
    SaveInjector::inject_default_during();
    angle = 49299;
    position = {-2462.85f, 2750.0f, -7.10f};
    set_angle_position();
}

void tot_early_hp() {
    SaveInjector::inject_default_during();
    angle = 49152;
    position = {-8000.50f, 5100.0f, -3226.17f};
    set_angle_position();
}

void hugo_archery() {
    SaveInjector::inject_default_during();
    tp_gameInfo.temp_flags.flags[14] = 0xC0;  // start archery minigame
}

void cits_poe_cycle() {
    SaveInjector::inject_default_during();
    tp_gameInfo.warp.entrance.spawn = 0x0;
    angle = 71;
    position = {-14005.31f, 3000.0f, -15854.05f};
    set_angle_position();
}

void argorok() {
    SaveInjector::inject_default_during();
    tp_gameInfo.boss_room_event_flags = 1;
}

void palace2() {
    tp_zelAudio.link_debug_ptr->current_item = 3;  // master sword
    SaveInjector::inject_default_during();
    angle = 32731;
    position = {251.83f, -200.0f, 10993.50f};
    set_angle_position();
}

void lakebed_bk_skip_during() {
    SaveInjector::inject_default_during();
    tp_gameInfo.temp_flags.flags[20] = 223;  // dungeon intro cs off
}

void cave_of_ordeals() {
    SaveInjector::inject_default_during();
    tp_gameInfo.floors.floor_01_08 = 0;  // reset all CoO doors on load
    tp_gameInfo.floors.floor_09_17 = 0;
    tp_gameInfo.floors.floor_18_26 = 0;
    tp_gameInfo.floors.floor_27_34 = 0;
}

void HundoSavesMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        hundo_saves_visible = false;
        prac_visible = true;
        mm_visible = false;
        init_once = false;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
        switch (cursor.y) {
            case HND_GOATS_1_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/goats.bin");
                default_load();
                practice_file.inject_options_during_load = goats_1;
                break;
            }

            case HND_ORDON_GATE_CLIP_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/ordon_gate_clip.bin");
                default_load();
                camera.target = {827.497559f, 329.622986f, -4532.90723f};
                camera.pos = {833.467468f, 477.604675f, -4241.97266f};
                angle = 498;
                position = {827.450012f, 216.490097f, -4533.90625f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 10;
                break;
            }

            case HND_GOATS_2_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/goats_2.bin");
                default_load();
                practice_file.inject_options_during_load = goats_2;
                break;
            }

            case HND_FARON_TWILIGHT_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/faron_twilight.bin");
                default_load();
                break;
            }

            case HND_EMS_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/ems.bin");
                default_load();
                break;
            }
            case HND_MIST_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/purple_mist.bin");
                default_load();
                angle = 40758;
                position = {-23524.6152f, 250.0f, -16220.166f};
                practice_file.inject_options_after_load = set_angle_position;
                practice_file.inject_options_during_load = purple_mist;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case HND_FRST_BIT_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/forest_bit.bin");
                default_load();
                break;
            }

            case HND_FRST_2_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/forest_2.bin");
                default_load();
                break;
            }

            case HND_OOKLESS_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/ookless.bin");
                default_load();
                break;
            }

            case HND_ELDIN_TWILIGHT_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/eldin_twilight.bin");
                default_load();
                break;
            }

            case HND_LANAYRU_GATE_CLIP_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/lanayru_gate_clip.bin");
                default_load();
                camera.target = {-63064.2148f, -8969.97656f, 71661.0781f};
                camera.pos = {-62655.8125f, -8900.91309f, 71903.6328f};
                angle = 44248;
                position = {-63026.2852f, -9065.92578f, 71680.3438f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 15;
                break;
            }
            case HND_PILLAR_CLIP_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/pillar_clip.bin");
                default_load();
                break;
            }
            case HND_LAKEBED_1_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/lakebed_1.bin");
                default_load();
                break;
            }
            case HND_TOAD_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/deku_toad.bin");
                default_load();
                break;
            }
            case HND_KARG_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/karg.bin");
                default_load();
                practice_file.inject_options_during_load = karg_oob;
                break;
            }
            case HND_LANAYRU_TWILIGHT_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/lanayru_twilight.bin");
                default_load();
                break;
            }
            case HND_BOSS_BUG_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/boss_bug.bin");
                default_load();
                angle = 21504;
                position = {-89100.00f, -18811.2363f, 39410.00f};
                practice_file.inject_options_after_load = set_angle_position;
                break;
            }
            case HND_KB_2_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/kb2.bin");
                default_load();
                camera.target = {-92098.1797f, -5398.54883f, 22599.9102f};
                camera.pos = {-92795.1328f, -5302.87988f, 22505.3359f};
                angle = 14957;
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_during_load = kb2_skip;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case HND_ESCORT_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/kb2.bin");
                default_load();
                practice_file.inject_options_during_load = escort;
                break;
            }
            case HND_COROTD_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/corotd.bin");
                default_load();
                /*angle = 27714;
                position = {-13715.0712f, 0.00f, -14238.0654f};
                practice_file.inject_options_after_load = set_angle_position;
                practice_file.inject_options_after_counter = 60;*/ // temporary disable since it crashes often for some reason
                break;
            }
            case HND_GM_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/gm.bin");
                default_load();
                break;
            }
            case HND_DANGORO_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/dangoro.bin");
                default_load();
                practice_file.inject_options_during_load = dangoro;
                break;
            }
            case HND_KB_1_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/kb1.bin");
                default_load();
                break;
            }
            case HND_LAKEBED_BK_SKIP_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/lakebed_bk_skip.bin");
                default_load();
                camera.target = {71.9835968f, 1660.0f, 2839.01587f};
                camera.pos = {71.9835968f, 1719.93542f, 2969.04565f};
                angle = 32767;
                position = {71.9835968f, 1500.00f, 2839.01587f};
                practice_file.inject_options_during_load = lakebed_bk_skip_during;
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case HND_MORPHEEL_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/morpheel.bin");
                default_load();
                practice_file.inject_options_after_load = morpheel;
                break;
            }
            case HND_STAR_1_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/star_1.bin");
                default_load();
                break;
            }
            case HND_MDH_TOWER_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/mdh_tower.bin");
                default_load();
                camera.target = {25256.7285f, -2919.95215f, 2839.01587f};
                camera.pos = {10193.6064f, 25254.7852f, -2874.2627f};
                angle = 32025;
                position = {25254.6875f, -3031.50854f, 10222.1445f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 15;
                break;
            }
            case HND_MDH_BRIDGE_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/mdh_bridge.bin");
                default_load();
                break;
            }
            case HND_POST_MDH_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/post_mdh.bin");
                default_load();
                break;
            }
            case HND_MOUNTAIN_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/mountain.bin");
                default_load();
                break;
            }
            case HND_IZA_1_SKIP_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/iza_1_skip.bin");
                default_load();
                practice_file.inject_options_during_load = iza_1_skip;
                break;
            }
            case HND_IZA_2_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/iza_2.bin");
                default_load();
                break;
            }
            case HND_LH_CAVE_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/lh_cave.bin");
                default_load();
                break;
            }
            case HND_BULBLIN_CAMP_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/camp.bin");
                default_load();
                break;
            }
            case HND_AG_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/ag.bin");
                default_load();
                break;
            }
            case HND_POE_1_SKIP_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/poe_1_skip.bin");
                default_load();
                camera.target = {-2047.97168f, 130.16568f, -587.317139f};
                camera.pos = {-1779.00293f, 213.707397f, -584.686768f};
                angle = 49030;
                position = {-2046.97168f, 0.0f, -587.304871f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 10;
                break;
            }
            case HND_DSS_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/death_sword_skip.bin");
                default_load();
                break;
            }
            case HND_STALLORD_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/stallord.bin");
                default_load();
                practice_file.inject_options_during_load = stallord;
                break;
            }
            case HND_GORGE_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/gorge_arc.bin");
                default_load();
                break;
            }
            case HND_SPR_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/spr.bin");
                default_load();
                break;
            }
            case HND_DARK_HAMMER_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/darkhammer.bin");
                default_load();
                //figure out how to disable armor sets then load in with boss flag for instant fight
                break;
            }
            case HND_SPR_SUPERJUMP_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/spr_superjump.bin");
                default_load();
                camera.target = {1529.35425f, 466.16306f, 3684.08252f};
                camera.pos = {1765.20581f, 691.830688f, 3662.42749f};
                angle = 50120;
                position = {1530.35f, 359.56f, 3683.99f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case HND_SPR_BK_LJA_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/spr_bk_lja.bin");
                default_load();
                angle = 32887;
                position = {-2171.19f, 973.96f, -2384.89f};
                practice_file.inject_options_after_load = set_angle_position;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case HND_SPR_BK_ROOM_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/spr_bk_lja.bin");
                default_load();
                practice_file.inject_options_during_load = spr_bosskey;
                break;
            }
            case HND_BLIZZETA_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/blizzeta.bin");
                default_load();
                break;
            }
            case HND_BOMB_BOOST_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/nf_bomb_boost.bin");
                default_load();
                break;
            }
            case HND_GROVE_2_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/grove_2.bin");
                default_load();
                break;
            }
            case HND_TOT_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/tot.bin");
                default_load();
                break;
            }
            case HND_EARLY_POE_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/tot_early_poe.bin");
                default_load();
                practice_file.inject_options_during_load = tot_early_poe;
                break;
            }
            case HND_STATUE_THROWS_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/tot_statue_throws.bin");
                default_load();
                break;
            }
            case HND_EARLY_HP_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/tot_early_hp.bin");
                default_load();
                practice_file.inject_options_during_load = tot_early_hp;
                break;
            }
            case HND_DARKNUT_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/tot_darknut.bin");
                default_load();
                break;
            }
            case HND_DOT_SKIP_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/dot_skip.bin");
                default_load();
                camera.target = {1361.59766f, -33.1954155f, -1090.47632f};
                camera.pos = {1396.36316f, 9.51973343f, -719.644531f};
                angle = 33673;
                position = {1361.68408f, -143.56076f, -1089.4801f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 30;
                //find statue pointer so can auto place statue in corner
                break;
            }
            case HND_ARMOGOHMA_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/armogohma.bin");
                default_load();
                break;
            }
            case HND_POST_TOT_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/post_tot.bin");
                default_load();
                break;
            }
            case HND_HOTSPRING_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/hotspring.bin");
                default_load();
                break;
            }
            case HND_BELL_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/silver_rupee.bin");
                default_load();
                camera.target = {961.308044f, 203.885788f, 4184.82471f};
                camera.pos = {1220.0835f, 320.043884f, 4269.48779f};
                angle = 45836;
                position = {962.257813f, 100.0f, 4185.1377f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case HND_FBF_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/fbf.bin");
                default_load();
                break;
            }
            case HND_PUZZLE_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/ice_puzzle.bin");
                default_load();
                break;
            }
            case HND_ARCHERY_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/hv_archery.bin");
                default_load();
                angle = 64520;
                position = {3125.57f, -62.16f, -9360.22f};
                practice_file.inject_options_after_load = set_angle_position;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case HND_CITY_EARLY_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/cits_early.bin");
                default_load();
                angle = 21207;
                position = {220.75f, -769.96f, -3299.14f};
                practice_file.inject_options_during_load = hugo_archery;
                practice_file.inject_options_after_load = set_angle_position;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case HND_CITY_1_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/cits_1.bin");
                default_load();
                camera.target = {1313.54285f, -234.203003f, 5545.16846f};
                camera.pos = {1027.53259f, -108.096123f, 5605.23047f};
                angle = 16384;
                position = {1309.60645f, -240.0f, 5533.43848f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 10;
                break;
            }
            case HND_AERALFOS_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/aeralfos_skip.bin");
                default_load();
                break;
            }
            case HND_CITY_2_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/cits_2.bin");
                default_load();
                break;
            }
            case HND_POE_CYCLE_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/cits_poe_cycle.bin");
                default_load();
                practice_file.inject_options_during_load = cits_poe_cycle;
                break;
            }
            case HND_FAN_TOWER_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/fan_tower.bin");
                default_load();
                break;
            }
            case HND_ARGOROK_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/argorok.bin");
                default_load();
                practice_file.inject_options_during_load = argorok;
                break;
            }
            case HND_STAR_2_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/star_2.bin");
                default_load();
                break;
            }
            case HND_PALACE_1_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/palace_1.bin");
                default_load();
                break;
            }
            case HND_PALACE_2_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/palace_2.bin");
                default_load();
                practice_file.inject_options_after_load = palace2;
                break;
            }
            case HND_EARLY_PLATFORM_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/early_platform.bin");
                default_load();
                break;
            }
            case HND_ZANT_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/zant.bin");
                default_load();
                break;
            }
            case HND_COO_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/coo.bin");
                default_load();
                practice_file.inject_options_during_load = cave_of_ordeals;
                break;
            }
            case HND_COO_10_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/coo_10.bin");
                default_load();
                practice_file.inject_options_during_load = cave_of_ordeals;
                break;
            }
            case HND_COO_20_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/coo_20.bin");
                default_load();
                practice_file.inject_options_during_load = cave_of_ordeals;
                break;
            }
            case HND_COO_30_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/coo_30.bin");
                default_load();
                practice_file.inject_options_during_load = cave_of_ordeals;
                break;
            }
            case HND_CATS_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/cats.bin");
                default_load();
                camera.target = {5309.32373f, 160.1f, -3581.83423f};
                camera.pos = {4893.25391f, 160.117676f, -3524.51245f};
                angle = 17282;
                position = {5238.59f, 0.00f, -3575.74f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case HND_HYRULE_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/hc.bin");
                default_load();
                break;
            }
            case HND_DARKNUT_SKIP_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/hc_darknut.bin");
                default_load();
                break;
            }
            case HND_FINAL_TOWER_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/hc_tower.bin");
                default_load();
                break;
            }
            case HND_BEAST_GANON_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/beast_ganon.bin");
                default_load();
                break;
            }
            case HND_HORSEBACK_GANON_INDEX: {
                Utilities::load_save_file("tpgz/save_files/hundo/horseback_ganon.bin");
                default_load();
                break;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.y, LINES);
};