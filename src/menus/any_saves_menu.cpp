#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"
#include "fifo_queue.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "gorge.h"
#include "rollcheck.h"
#include "save_injector.h"
#include "log.h"
#include "fs.h"
#define LINES 48

static Cursor cursor = {0, 0};
static CameraMatrix camera = {0, 0, 0, 0, 0, 0, 0, 0};
static uint16_t angle = 0;
static Vec3 position = {0, 0, 0};
bool init_once = false;
bool any_saves_visible;

Line lines[LINES] = {
    {"ordon gate clip", ORDON_GATE_CLIP_INDEX, "Gate Clip outside Ordon Spring"},
    {"back in time", BACK_IN_TIME_INDEX, "Back In Time off the Ordon Spring bridge"},
    {"goats", GOATS_INDEX, "Goat herding 2"},
    {"sword and shield skip", HUGO_INDEX, "Hangin' with Hugo"},
    {"early master sword", EMS_INDEX, "Super Jump to early Sacred Grove"},
    {"purple mist", MIST_INDEX, "Purple mist in Faron Woods (post-EMS)"},
    {"forest bit", FRST_BIT_INDEX, "Back In Time in Forest Temple"},
    {"forest escape", FRST_ESCAPE_INDEX, "LJA over S Faron exit trigger"},
    {"gorge void", GORGE_VOID_INDEX, "The worst trick"},
    {"rupee roll", RUPEE_ROLL_INDEX, "LJA onto fence + pick up rupee"},
    {"lanayru gate clip", LANAYRU_GATE_CLIP_INDEX, "Gate Clip outside Lake Hylia"},
    {"pillar clip", PILLAR_CLIP_INDEX, "Pillar Clip in Lake Hylia (low water)"},
    {"lakebed 1", LAKEBED_1_INDEX, "The first Lakebed Temple segment"},
    {"deku toad", TOAD_INDEX, "The miniboss of Lakebed Temple"},
    {"kargorok flight", KARG_INDEX, "Clip OoB with trumpet bird"},
    {"eldin twilight", ELDIN_TWILIGHT_INDEX, "Eldin Twilight tears"},
    {"lanayru twilight", LANAYRU_TWILIGHT_INDEX, "Lanayru Twilight tears"},
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
    {"palace of twilight 2", PALACE_2_INDEX, "The second Palace of Twilight segment (after both Sols)"},
    {"early platform", EARLY_PLATFORM_INDEX, "Early platform in Palace of Twilight"},
    {"zant", ZANT_INDEX, "The Palace of Twilight boss"},
    {"hyrule castle", HC_INDEX, "The Hyrule Castle segment"},
    {"darknut fight", DARKNUT_INDEX, "The Darknut fight in Hyrule Castle"},
    {"final tower climb", HC_TOWER_INDEX, "The tower climb before the final boss fights"},
    {"beast ganon", BEAST_GANON_INDEX, "The Beast Ganon fight"},
    {"horseback ganon", HORSEBACK_GANON_INDEX, "The horseback Ganondorf fight"}};

void default_load() {
    practice_file.inject_options_before_load = SaveInjector::inject_default_before;
    practice_file.inject_options_during_load = SaveInjector::inject_default_during;
    practice_file.inject_options_after_load = SaveInjector::inject_default_after;
    inject_save_flag = true;
    fifo_visible = true;
    prac_visible = false;
    any_saves_visible = false;
    mm_visible = false;
    init_once = false;
}

void set_camera_angle_position() {
    tp_matrixInfo.matrix_info->target = {camera.c0, camera.c1, camera.c2};
    tp_matrixInfo.matrix_info->pos = {camera.c3, camera.c4, camera.c5};
    tp_matrixInfo.matrix_info->camera6 = camera.c6;
    tp_matrixInfo.matrix_info->camera7 = camera.c7;
    tp_zelAudio.link_debug_ptr->facing = angle;
    tp_zelAudio.link_debug_ptr->position = position;
}

void set_angle_position() {
    tp_zelAudio.link_debug_ptr->facing = angle;
    tp_zelAudio.link_debug_ptr->position = position;
}

void hugo() {
    SaveInjector::inject_default_during();
    tp_gameInfo.temp_flags.temp_flag_bit_field_19 = 128;  // midna trigger off
    tp_gameInfo.temp_flags.temp_flag_bit_field_17 = 0;    // hugo alive
}

void karg_oob() {
    SaveInjector::inject_default_during();
    tp_gameInfo.respawn_animation = 0xA;  // spawn on kargorok
    tp_gameInfo.link.is_wolf = false;
}

void morpheel() {
    tp_zelAudio.link_debug_ptr->current_item = 68;  // clawshot
    tp_zelAudio.link_debug_ptr->current_boots = 2;  // ib
    angle = 10754;
    position = {-1193.0f, -23999.0f, -770.0f};
    set_angle_position();
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

void palace2() {
    tp_zelAudio.link_debug_ptr->current_item = 3;  // master sword
}

void lakebed_bk_skip_during() {
    SaveInjector::inject_default_during();
    tp_gameInfo.temp_flags.temp_flag_bit_field_16 = 18;   // bridge turned
    tp_gameInfo.temp_flags.temp_flag_bit_field_25 = 223;  // dungeon intro cs off
}

void AnySavesMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        any_saves_visible = false;
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
            case ORDON_GATE_CLIP_INDEX: {
                loadFile("tpgz/save_files/any/ordon_gate_clip.bin");
                default_load();
                camera = {827.497559f, 329.622986f, -4532.90723f, 833.467468f, 477.604675f, -4241.97266f, 1.26012994f, 280.0f};
                angle = 498;
                position = {827.450012f, 216.490097f, -4533.90625f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 10;
                break;
            }
            case BACK_IN_TIME_INDEX: {
                loadFile("tpgz/save_files/any/ordon_gate_clip.bin");
                default_load();
                camera = {465.674622f, 421.052704f, -11651.0684f, 735.525391f, 524.418701f, -11576.4746f, 1.36201766f, 280.0f};
                angle = 52540;
                position = {466.622467f, 319.770752f, -11651.3867f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 10;
                break;
            }
            case GOATS_INDEX: {
                loadFile("tpgz/save_files/any/goats.bin");
                default_load();
                break;
            }
            case HUGO_INDEX: {
                loadFile("tpgz/save_files/any/hugo.bin");
                default_load();
                camera = {465.674622f, 421.052704f, -11651.0684f, 735.525391f, 524.418701f, -11576.4746f, 1.36201766f, 280.0f};
                angle = 63622;
                position = {701.797302f, 85.5212784f, -5299.6123f};
                practice_file.inject_options_during_load = hugo;
                practice_file.inject_options_after_load = set_camera_angle_position;
                break;
            }
            case EMS_INDEX: {
                loadFile("tpgz/save_files/any/ems.bin");
                default_load();
                break;
            }
            case MIST_INDEX: {
                loadFile("tpgz/save_files/any/purple_mist.bin");
                default_load();
                angle = 40758;
                position = {-23524.6152f, 250.0f, -16220.166f};
                practice_file.inject_options_after_load = set_angle_position;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case FRST_BIT_INDEX: {
                loadFile("tpgz/save_files/any/forest_bit.bin");
                default_load();
                break;
            }
            case FRST_ESCAPE_INDEX: {
                loadFile("tpgz/save_files/any/forest_escape.bin");
                default_load();
                camera = {-12433.2979f, -106.667023f, -17104.9512f, -12552.8252f, -53.5801048f, -16729.5313f, -5.31691198f, 280.0f};
                angle = 29553;
                position = {-12433.6016f, -235.969193f, -17103.998f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case GORGE_VOID_INDEX: {
                loadFile("tpgz/save_files/any/gorge_void.bin");
                default_load();
                angle = 54288;
                position = {-9704.47266f, -7200.0f, 58475.5195f};
                practice_file.inject_options_after_load = set_angle_position;
                break;
            }
            case RUPEE_ROLL_INDEX: {
                loadFile("tpgz/save_files/any/gorge_void.bin");
                default_load();
                camera = {-11124.4697f, -5589.99902f, 56373.5195f, -11178.1504f, -5506.71338f, 56843.1797f, 0.0f, 280.0f};
                angle = 31571;
                position = {-11130.208f, -5700.0f, 56423.1953f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 15;
                break;
            }
            case LANAYRU_GATE_CLIP_INDEX: {
                loadFile("tpgz/save_files/any/lanayru_gate_clip.bin");
                default_load();
                camera = {-63064.2148f, -8969.97656f, 71661.0781f, -62655.8125f, -8900.91309f, 71903.6328f, -1.30928958f, 280.000092f};
                angle = 44248;
                position = {-63026.2852f, -9065.92578f, 71680.3438f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 15;
                break;
            }
            case PILLAR_CLIP_INDEX: {
                loadFile("tpgz/save_files/any/pillar_clip.bin");
                default_load();
                break;
            }
            case LAKEBED_1_INDEX: {
                loadFile("tpgz/save_files/any/lakebed_1.bin");
                default_load();
                break;
            }
            case TOAD_INDEX: {
                loadFile("tpgz/save_files/any/deku_toad.bin");
                default_load();
                break;
            }
            case KARG_INDEX: {
                loadFile("tpgz/save_files/any/karg.bin");
                default_load();
                practice_file.inject_options_during_load = karg_oob;
                break;
            }
            case ELDIN_TWILIGHT_INDEX: {
                loadFile("tpgz/save_files/any/eldin_twilight.bin");
                default_load();
                camera = {482.515137f, -39.9999771f, 11558.5283f, 219.367218f, -20.1253014f, 11157.582f, -3.81633819f, 280.000092f};
                angle = 6058;
                position = {455.088379f, -150.0f, 11516.7227f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 10;
                break;
            }
            case LANAYRU_TWILIGHT_INDEX: {
                loadFile("tpgz/save_files/any/lanayru_twilight.bin");
                default_load();
                break;
            }
            case BOSS_BUG_INDEX: {
                loadFile("tpgz/save_files/any/boss_bug.bin");
                default_load();
                angle = 21504;
                position = {-89100.00f, -18811.2363f, 39410.00f};
                practice_file.inject_options_after_load = set_angle_position;
                break;
            }
            case IZA_INDEX: {
                loadFile("tpgz/save_files/any/iza.bin");
                default_load();
                angle = 10114;
                position = {5979.97217f, 150.0f, -2748.34155f};
                practice_file.inject_options_after_load = set_angle_position;
                break;
            }
            case NORGOR_INDEX: {
                loadFile("tpgz/save_files/any/norgor.bin");
                default_load();
                camera = {174.411758f, -70.5306549f, -3668.91406f, 501.768982f, -5.045784f, -3586.1145f, -1.88999606f, 280.0f};
                angle = 46568;
                position = {173.71f, -186.52f, -3633.71f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 15;
                break;
            }
            case SPR_WARP_SKIP_INDEX: {
                loadFile("tpgz/save_files/any/spr_warp.bin");
                default_load();
                camera = {-9294.2207f, 1180.0f, -11692.3945f, -9309.65137f, 1280.4469f, -12130.7695f, 1.13141331f, 450.0f};
                angle = 346;
                position = {-9294.87988f, 980.0f, -11712.3838f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 10;
                break;
            }
            case SPR_INDEX: {
                loadFile("tpgz/save_files/any/spr.bin");
                default_load();
                angle = 33768;
                position = {0.0f, -150.0f, 6000.0f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                break;
            }
            case DARK_HAMMER_INDEX: {
                loadFile("tpgz/save_files/any/darkhammer.bin");
                default_load();
                TP::set_boss_flags();
                break;
            }
            case LAKEBED_2_INDEX: {
                loadFile("tpgz/save_files/any/lakebed_2.bin");
                default_load();
                camera = {-8.74227766f, 1337.22534f, 14499.0f, -87.9447556f, 1414.24292f, 14741.0518f, 0.0f, 221.340179f};
                angle = 32768;
                position = {0.0f, 1240.29333f, 14500.0f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 15;
                break;
            }
            case LAKEBED_BK_SKIP_INDEX: {
                loadFile("tpgz/save_files/any/lakebed_bk_skip.bin");
                default_load();
                camera = {71.9835968f, 1660.0f, 2839.01587f, 71.9835968f, 1719.93542f, 2969.04565f, 0.0f, 0.5f};
                angle = 32767;
                position = {71.9835968f, 1500.00f, 2839.01587f};
                practice_file.inject_options_during_load = lakebed_bk_skip_during;
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 30;
                break;
            }
            case ONEBOMB_INDEX: {
                loadFile("tpgz/save_files/any/onebomb.bin");
                default_load();
                practice_file.inject_options_after_load = morpheel;
                break;
            }
            case MDH_TOWER_INDEX: {
                loadFile("tpgz/save_files/any/mdh_tower.bin");
                default_load();
                break;
            }
            case MDH_BRIDGE_INDEX: {
                loadFile("tpgz/save_files/any/mdh_bridge.bin");
                default_load();
                break;
            }
            case BULBLIN_CAMP_INDEX: {
                loadFile("tpgz/save_files/any/camp.bin");
                default_load();
                break;
            }
            case AG_INDEX: {
                loadFile("tpgz/save_files/any/ag.bin");
                default_load();
                break;
            }
            case POE_1_SKIP_INDEX: {
                loadFile("tpgz/save_files/any/poe_1_skip.bin");
                default_load();
                camera = {-2047.97168f, 130.16568f, -587.317139f, -1779.00293f, 213.707397f, -584.686768f, 0.0f, 280.0f};
                angle = 49030;
                position = {-2046.97168f, 0.0f, -587.304871f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 10;
                break;
            }
            case DSS_INDEX: {
                loadFile("tpgz/save_files/any/death_sword_skip.bin");
                default_load();
                break;
            }
            case STALLORD_INDEX: {
                loadFile("tpgz/save_files/any/stallord.bin");
                default_load();
                practice_file.inject_options_during_load = stallord;
                break;
            }
            case CITS_EARLY_INDEX: {
                loadFile("tpgz/save_files/any/cits_early.bin");
                default_load();
                break;
            }
            case CITS_1_INDEX: {
                loadFile("tpgz/save_files/any/cits_1.bin");
                default_load();
                camera = {1313.54285f, -234.203003f, 5545.16846f, 1027.53259f, -108.096123f, 5605.23047f, 0.0f, 318.295868f};
                angle = 16384;
                position = {1309.60645f, -240.0f, 5533.43848f};
                practice_file.inject_options_after_load = set_camera_angle_position;
                practice_file.inject_options_after_counter = 10;
                break;
            }
            case AERALFOS_SKIP_INDEX: {
                loadFile("tpgz/save_files/any/aeralfos_skip.bin");
                default_load();
                break;
            }
            case CITS_2_INDEX: {
                loadFile("tpgz/save_files/any/cits_2.bin");
                default_load();
                break;
            }
            case FAN_TOWER_INDEX: {
                loadFile("tpgz/save_files/any/fan_tower.bin");
                default_load();
                break;
            }
            case ARGOROK_INDEX: {
                loadFile("tpgz/save_files/any/argorok.bin");
                default_load();
                practice_file.inject_options_during_load = argorok;
                break;
            }
            case PALACE_1_INDEX: {
                loadFile("tpgz/save_files/any/palace_1.bin");
                default_load();
                break;
            }
            case PALACE_2_INDEX: {
                loadFile("tpgz/save_files/any/palace_2.bin");
                default_load();
                practice_file.inject_options_after_load = palace2;
                break;
            }
            case EARLY_PLATFORM_INDEX: {
                loadFile("tpgz/save_files/any/early_platform.bin");
                default_load();
                break;
            }
            case ZANT_INDEX: {
                loadFile("tpgz/save_files/any/zant.bin");
                default_load();
                break;
            }
            case HC_INDEX: {
                loadFile("tpgz/save_files/any/hc.bin");
                default_load();
                break;
            }
            case DARKNUT_INDEX: {
                loadFile("tpgz/save_files/any/darknut.bin");
                default_load();
                break;
            }
            case HC_TOWER_INDEX: {
                loadFile("tpgz/save_files/any/hc_tower.bin");
                default_load();
                break;
            }
            case BEAST_GANON_INDEX: {
                loadFile("tpgz/save_files/any/beast_ganon.bin");
                default_load();
                break;
            }
            case HORSEBACK_GANON_INDEX: {
                loadFile("tpgz/save_files/any/horseback_ganon.bin");
                default_load();
                break;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.y, LINES);
};
