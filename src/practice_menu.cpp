#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"
#include "fifo_queue.h"
#include "utils.h"
#include "gorge.h"
#include "rollcheck.h"
#include "save_injector.h"
#include "log.h"
#include "fs.h"
#define LINES 50

static int cursor = 1;
static CameraMatrix camera = {0, 0, 0, 0, 0, 0, 0, 0};
static uint16_t angle = 0;
static Vec3 position = {0, 0, 0};
bool g_load_happened;

Line lines[LINES] = {
    {"practice", 0, ""},
    {"", 1, ""},
    {"ordon gate clip", ORDON_GATE_CLIP_INDEX, "gate clip outside ordon spring"},
    {"back in time", BACK_IN_TIME_INDEX, "back in time off the ordon spring bridge"},
    {"goats", GOATS_INDEX, "goat herding 2"},
    {"sword and shield skip", HUGO_INDEX, "hangin' with hugo"},
    {"early master sword", EMS_INDEX, "super jump to early sacred grove"},
    {"purple mist", MIST_INDEX, "purple mist in faron woods (post EMS)"},
    {"forest bit", FRST_BIT_INDEX, "back in time in forest temple"},
    {"forest escape", FRST_ESCAPE_INDEX, "lja over s. faron exit trigger"},
    {"gorge void", GORGE_VOID_INDEX, "the worst trick"},
    {"rupee roll", RUPEE_ROLL_INDEX, "lja onto fence + pickup rupee"},
    {"lanayru gate clip", LANAYRU_GATE_CLIP_INDEX, "gate clip outside lake hylia"},
    {"pillar clip", PILLAR_CLIP_INDEX, "pillar clip in lake hylia (low water)"},
    {"lakebed 1", LAKEBED_1_INDEX, "the first lakebed segment"},
    {"deku toad", TOAD_INDEX, "the miniboss of lakebed temple"},
    {"kargorok flight", KARG_INDEX, "clip oob with trumpet bird"},
    {"eldin twilight", ELDIN_TWILIGHT_INDEX, "eldin twilight tears"},
    {"lanayru twilight", LANAYRU_TWILIGHT_INDEX, "lanayru twilight tears"},
    {"boss bug", BOSS_BUG_INDEX, "lanyru twilight boss bug"},
    {"iza", IZA_INDEX, "steal iza's bomb bag"},
    {"norgor", NORGOR_INDEX, "goron bomb bag without water bombs"},
    {"snowpeak messenger skip", SPR_WARP_SKIP_INDEX, "lja to skip the spr messenger fight"},
    {"snowpeak", SPR_INDEX, "the snowpeak dungeon segment"},
    {"dark hammer", DARK_HAMMER_INDEX, "the snowpeak miniboss"},
    {"lakebed 2", LAKEBED_2_INDEX, "the second lakebed segment"},
    {"lakebed bk skip", LAKEBED_BK_SKIP_INDEX, "boss key skip in lakebed main room"},
    {"morpheel", ONEBOMB_INDEX, "morpheel fight (no zora armor)"},
    {"mdh tower", MDH_TOWER_INDEX, "mdh tower climb before castle rooftops"},
    {"mdh bridge", MDH_BRIDGE_INDEX, "the falling bridge on castle rooftops"},
    {"bulblin camp", BULBLIN_CAMP_INDEX, "the area before arbiter's grounds"},
    {"arbiter's grounds", AG_INDEX, "the arbiter's grounds segment"},
    {"poe 1 skip", POE_1_SKIP_INDEX, "the pillar jump in arbiter's grounds"},  // fix
    {"death sword", DSS_INDEX, "the arbiter's grounds miniboss"},
    {"stallord", STALLORD_INDEX, "the arbiter's grounds boss"},  // fix
    {"city in the sky early", CITS_EARLY_INDEX, "clip to the canon early"},
    {"city in the sky 1", CITS_1_INDEX, "the first city in the sky segment"},
    {"aeralfos skip", AERALFOS_SKIP_INDEX, "the city in the sky miniboss"},
    {"city in the sky 2", CITS_2_INDEX, "the second city in the sky segment"},
    {"fan tower", FAN_TOWER_INDEX, "final fan room in city before the boss"},
    {"argorok", ARGOROK_INDEX, "the city in the sky boss"},
    {"palace of twilight 1", PALACE_1_INDEX, "the first palace of twilight segment"},
    {"palace of twilight 2", PALACE_2_INDEX, "the second palace of twilight segment"},
    {"early platform", EARLY_PLATFORM_INDEX, "early platform in palace of twilight"},
    {"hyrule castle", HC_INDEX, "the hyrule castle segment"},
    {"darknut fight", DARKNUT_INDEX, "the darknut fight in hyrule castle"},
    {"final tower climb", HC_TOWER_INDEX, "the tower climb before the final boss fights"},
    {"beast ganon", BEAST_GANON_INDEX, "the beast ganon fight"},
    {"horseback ganon", HORSEBACK_GANON_INDEX, "the horseback ganon fight"}};

namespace PracticeMenu {
    void default_load() {
        practice_file.inject_options_before_load = SaveInjector::inject_default_before;
        practice_file.inject_options_during_load = SaveInjector::inject_default_during;
        practice_file.inject_options_after_load = SaveInjector::inject_default_after;
        inject_save_flag = true;
        fifo_visible = true;
        prac_visible = false;
        mm_visible = false;
        cursor = 1;
    }

    void set_camera_angle_position() {
        tp_matrixInfo.matrix_info->camera0 = camera.c0;
        tp_matrixInfo.matrix_info->camera1 = camera.c1;
        tp_matrixInfo.matrix_info->camera2 = camera.c2;
        tp_matrixInfo.matrix_info->camera3 = camera.c3;
        tp_matrixInfo.matrix_info->camera4 = camera.c4;
        tp_matrixInfo.matrix_info->camera5 = camera.c5;
        tp_matrixInfo.matrix_info->camera6 = camera.c6;
        tp_matrixInfo.matrix_info->camera7 = camera.c7;
        tp_zelAudio.link_debug_ptr->facing = angle;
        tp_zelAudio.link_debug_ptr->position = position;
    }

    void set_angle_position() {
        tp_zelAudio.link_debug_ptr->facing = angle;
        tp_zelAudio.link_debug_ptr->position = position;
    }

    void norgor() {
        tp_matrixInfo.matrix_info->camera0 = 174.411758f;
        tp_matrixInfo.matrix_info->camera1 = -70.5306549f;
        tp_matrixInfo.matrix_info->camera2 = -3668.91406f;
        tp_matrixInfo.matrix_info->camera3 = 501.768982f;
        tp_matrixInfo.matrix_info->camera4 = -5.045784f;
        tp_matrixInfo.matrix_info->camera5 = -3586.1145f;
        tp_matrixInfo.matrix_info->camera6 = -1.88999606f;
        tp_matrixInfo.matrix_info->camera7 = 280.0f;
        tp_zelAudio.link_debug_ptr->facing = 46568;
        tp_zelAudio.link_debug_ptr->position = {173.71f, -186.52f, -3633.71f};
    }

    void hugo() {
        SaveInjector::inject_default_during();
        tp_gameInfo.temp_flags.temp_flag_bit_field_19 = 128;  // midna trigger off
        tp_gameInfo.temp_flags.temp_flag_bit_field_17 = 0;    // hugo alive
    }

    void morpheel() {
        tp_zelAudio.link_debug_ptr->current_item = 68;  // clawshot
        tp_zelAudio.link_debug_ptr->current_boots = 2;  // ib
        angle = 10754;
        position = {-1193.0f, -23999.0f, -770.0f};
        set_angle_position();
    }

    void lakebed_bk_skip_during() {
        SaveInjector::inject_default_during();
        tp_gameInfo.temp_flags.temp_flag_bit_field_16 = 18;   // bridge turned
        tp_gameInfo.temp_flags.temp_flag_bit_field_25 = 223;  // dungeon intro cs off
    }

    void PracticeMenu::render(Font& font) {
        if (button_is_pressed(Controller::B)) {
            prac_visible = false;
            mm_visible = true;
            cursor = 1;
            return;
        };

        if (button_is_pressed(Controller::A)) {
            switch (cursor) {
                case ORDON_GATE_CLIP_INDEX: {
                    loadFile("tpgz/save_files/ordon_gate_clip.bin");
                    default_load();
                    camera = {827.497559f, 329.622986f, -4532.90723f, 833.467468f, 477.604675f, -4241.97266f, 1.26012994f, 280.0f};
                    angle = 498;
                    position = {827.450012f, 216.490097f, -4533.90625f};
                    practice_file.inject_options_after_load = set_camera_angle_position;
                    practice_file.inject_options_after_counter = 10;
                    break;
                }
                case BACK_IN_TIME_INDEX: {
                    loadFile("tpgz/save_files/ordon_gate_clip.bin");
                    default_load();
                    camera = {465.674622f, 421.052704f, -11651.0684f, 735.525391f, 524.418701f, -11576.4746f, 1.36201766f, 280.0f};
                    angle = 52540;
                    position = {466.622467f, 319.770752f, -11651.3867f};
                    practice_file.inject_options_after_load = set_camera_angle_position;
                    practice_file.inject_options_after_counter = 10;
                    break;
                }
                case GOATS_INDEX: {
                    loadFile("tpgz/save_files/goats.bin");
                    default_load();
                    break;
                }
                case HUGO_INDEX: {
                    loadFile("tpgz/save_files/hugo.bin");
                    default_load();
                    camera = {465.674622f, 421.052704f, -11651.0684f, 735.525391f, 524.418701f, -11576.4746f, 1.36201766f, 280.0f};
                    angle = 63622;
                    position = {701.797302f, 85.5212784f, -5299.6123f};
                    practice_file.inject_options_during_load = hugo;
                    practice_file.inject_options_after_load = set_camera_angle_position;
                    break;
                }
                case EMS_INDEX: {
                    loadFile("tpgz/save_files/ems.bin");
                    default_load();
                    break;
                }
                case MIST_INDEX: {
                    loadFile("tpgz/save_files/purple_mist.bin");
                    default_load();
                    angle = 40758;
                    position = {-23524.6152f, 250.0f, -16220.166f};
                    practice_file.inject_options_after_load = set_angle_position;
                    practice_file.inject_options_after_counter = 30;
                    break;
                }
                case FRST_BIT_INDEX: {
                    loadFile("tpgz/save_files/forest_bit.bin");
                    default_load();
                    break;
                }
                case FRST_ESCAPE_INDEX: {
                    loadFile("tpgz/save_files/forest_escape.bin");
                    default_load();
                    camera = {-12433.2979f, -106.667023f, -17104.9512f, -12552.8252f, -53.5801048f, -16729.5313f, -5.31691198f, 280.0f};
                    angle = 29553;
                    position = {-12433.6016f, -235.969193f, -17103.998f};
                    practice_file.inject_options_after_load = set_camera_angle_position;
                    practice_file.inject_options_after_counter = 30;
                    break;
                }
                case GORGE_VOID_INDEX: {
                    loadFile("tpgz/save_files/gorge_void.bin");
                    default_load();
                    angle = 54288;
                    position = {-9704.47266f, -7200.0f, 58475.5195f};
                    practice_file.inject_options_after_load = set_angle_position;
                    break;
                }
                case RUPEE_ROLL_INDEX: {
                    loadFile("tpgz/save_files/rupee_roll.bin");
                    default_load();
                    camera = {-11802.0088f, -5607.06787f, 56613.2188f, -11934.2266f, -5517.06885f, 56735.3594f, 0.0f, 0.5f};
                    angle = 24169;
                    position = {-11850.834f, -5700.0f, 56658.3672f};
                    practice_file.inject_options_after_load = set_camera_angle_position;
                    practice_file.inject_options_after_counter = 15;
                    break;
                }
                case LANAYRU_GATE_CLIP_INDEX: {
                    loadFile("tpgz/save_files/lanayru_gate_clip.bin");
                    default_load();
                    camera = {-63064.2148f, -8969.97656f, 71661.0781f, -62655.8125f, -8900.91309f, 71903.6328f, -1.30928958f, 280.000092f};
                    angle = 44248;
                    position = {-63026.2852f, -9065.92578f, 71680.3438f};
                    practice_file.inject_options_after_load = set_camera_angle_position;
                    practice_file.inject_options_after_counter = 15;
                    break;
                }
                case PILLAR_CLIP_INDEX: {
                    loadFile("tpgz/save_files/pillar_clip.bin");
                    default_load();
                    break;
                }
                case LAKEBED_1_INDEX: {
                    loadFile("tpgz/save_files/lakebed_1.bin");
                    default_load();
                    break;
                }
                case TOAD_INDEX: {
                    loadFile("tpgz/save_files/deku_toad.bin");
                    default_load();
                    break;
                }
                case KARG_INDEX: {
                    loadFile("tpgz/save_files/karg.bin");
                    default_load();
                    angle = 0;
                    position = {-43655.6133f, -20923.0078f, 31594.4121f};
                    practice_file.inject_options_after_load = set_camera_angle_position;
                    break;
                }
                case ELDIN_TWILIGHT_INDEX: {
                    loadFile("tpgz/save_files/eldin_twilight.bin");
                    default_load();
                    camera = {482.515137f,-39.9999771f,11558.5283f,219.367218f,-20.1253014f,11157.582f,-3.81633819f,280.000092f};
                    angle = 6058;
                    position = {455.088379f,-150.0f,11516.7227f};
                    practice_file.inject_options_after_load = set_camera_angle_position;
                    practice_file.inject_options_after_counter = 10;
                    break;
                }
                case LANAYRU_TWILIGHT_INDEX: {

                    break;
                }
                case BOSS_BUG_INDEX: {
                    loadFile("tpgz/save_files/boss_bug.bin");
                    default_load();
                    angle = 21504;
                    position = {-89100.00f, -18811.2363f, 39410.00f};
                    practice_file.inject_options_after_load = set_angle_position;
                    break;
                }
                case IZA_INDEX: {
                    loadFile("tpgz/save_files/iza.bin");
                    default_load();
                    angle = 10114;
                    position = {5979.97217f,150.0f,-2748.34155f};
                    practice_file.inject_options_after_load = set_angle_position;
                    break;
                }
                case NORGOR_INDEX: {
                    loadFile("tpgz/save_files/norgor.bin");
                    default_load();
                    practice_file.inject_options_after_load = norgor;
                    practice_file.inject_options_after_counter = 15;
                    break;
                }
                case SPR_WARP_SKIP_INDEX: {
                    loadFile("tpgz/save_files/spr_warp.bin");
                    default_load();
                    camera = {-9294.2207f,1180.0f,-11692.3945f,-9309.65137f,1280.4469f,-12130.7695f,1.13141331f,450.0f};
                    angle = 346;
                    position = {-9294.87988f,980.0f,-11712.3838f};
                    practice_file.inject_options_after_load = set_camera_angle_position;
                    practice_file.inject_options_after_counter = 10;
                    break;
                }
                case SPR_INDEX: {
                    loadFile("tpgz/save_files/spr.bin");
                    default_load();
                    angle = 33768;
                    position = {0.0f,-150.0f,6000.0f};
                    practice_file.inject_options_after_load = set_camera_angle_position;
                    break;
                }
                case DARK_HAMMER_INDEX: {
                    loadFile("tpgz/save_files/darkhammer.bin");
                    default_load();
                    TP::set_boss_flags();
                    break;
                }
                case LAKEBED_2_INDEX: {
                    loadFile("tpgz/save_files/lakebed_2.bin");
                    default_load();
                    camera = {-8.74227766f, 1337.22534f, 14499.0f, -87.9447556f, 1414.24292f, 14741.0518f, 0.0f, 221.340179f};
                    angle = 32768;
                    position = {0.0f, 1240.29333f, 14500.0f};
                    practice_file.inject_options_after_load = set_camera_angle_position;
                    practice_file.inject_options_after_counter = 15;
                    break;
                    break;
                }
                case LAKEBED_BK_SKIP_INDEX: {
                    loadFile("tpgz/save_files/lakebed_bk_skip.bin");
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
                    loadFile("tpgz/save_files/onebomb.bin");
                    default_load();
                    practice_file.inject_options_after_load = morpheel;
                    break;
                }
                case MDH_TOWER_INDEX: {
                    break;
                }
                case MDH_BRIDGE_INDEX: {
                    loadFile("tpgz/save_files/mdh_bridge.bin");
                    default_load();
                    break;
                }
                case BULBLIN_CAMP_INDEX: {
                    loadFile("tpgz/save_files/camp.bin");
                    default_load();
                    break;
                }
                case AG_INDEX: {
                    break;
                }
                case POE_1_SKIP_INDEX: {
                    loadFile("tpgz/save_files/poe_1_skip.bin");
                    default_load();
                    break;
                }
                case DSS_INDEX: {
                    loadFile("tpgz/save_files/death_sword_skip.bin");
                    default_load();
                    break;
                }
                case STALLORD_INDEX: {
                    loadFile("tpgz/save_files/stallord.bin");
                    default_load();
                    break;
                }
                case CITS_EARLY_INDEX: {
                    break;
                }
                case CITS_1_INDEX: {
                    break;
                }
                case AERALFOS_SKIP_INDEX: {
                    loadFile("tpgz/save_files/aeralfos_skip.bin");
                    default_load();
                    break;
                }
                case CITS_2_INDEX: {
                    break;
                }
                case FAN_TOWER_INDEX: {
                    loadFile("tpgz/save_files/fan_tower.bin");
                    default_load();
                    break;
                }
                case ARGOROK_INDEX: {
                    break;
                }
                case EARLY_PLATFORM_INDEX: {
                    loadFile("tpgz/save_files/early_platform.bin");
                    default_load();
                    break;
                }
                case HC_INDEX: {
                    break;
                }
                case DARKNUT_INDEX: {
                    break;
                }
                case HC_TOWER_INDEX: {
                    break;
                }
                case BEAST_GANON_INDEX: {
                    break;
                }
                case HORSEBACK_GANON_INDEX: {
                    break;
                }
            }
        }

        Utilities::move_cursor(cursor, LINES);
        Utilities::render_lines(font, lines, cursor, LINES);
    };
};  // namespace PracticeMenu