#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/controller.h"
#include "menus/any_saves_menu.h"
#include "menus/practice_menu.h"
#include "controller.h"
#include "fifo_queue.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "utils/loading.hpp"
#include "gorge.h"
#include "rollcheck.h"
#include "save_injector.h"

#include "fs.h"
#define LINES 48

#define REQ_POS 1
#define REQ_CAM 2

static Cursor cursor = {0, 0};
static CameraMatrix camera = {{0, 0, 0}, {0, 0, 0}};
static uint16_t angle = 0;
static Vec3 position = {0, 0, 0};
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
    MenuRendering::set_menu(MN_NONE_INDEX);
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

void hugo() {
    SaveInjector::inject_default_during();
    tp_gameInfo.temp_flags.flags[14] = 128;  // midna trigger off
    tp_gameInfo.temp_flags.flags[12] = 0;    // hugo alive
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
    tp_gameInfo.temp_flags.flags[11] = 18;   // bridge turned
    tp_gameInfo.temp_flags.flags[20] = 223;  // dungeon intro cs off
}

struct {
    int idx;
    void (*cb_during)(void);
    void (*cb_after)(void);
} specials[] = {
    {HUGO_INDEX, hugo, nullptr},
    {KARG_INDEX, karg_oob, nullptr},
    {LAKEBED_BK_SKIP_INDEX, lakebed_bk_skip_during, nullptr},
    {ONEBOMB_INDEX, nullptr, morpheel},
    {STALLORD_INDEX, stallord, nullptr},
    {ARGOROK_INDEX, argorok, nullptr},
    {PALACE_2_INDEX, nullptr, palace2},
};

void load_save(uint32_t id) {
    PracticeSaveInfo saveinfo __attribute__((aligned(32)));
    loadFile("tpgz/save_files/any.bin", &saveinfo, sizeof(saveinfo), id * sizeof(saveinfo));
    char buf[80];
    sprintf(buf, "tpgz/save_files/any/%s.bin", saveinfo.filename);
    Utilities::load_save_file(buf);
    default_load();
    if (saveinfo.requirements & REQ_CAM) {
        camera.target = saveinfo.cam_target;
        camera.pos = saveinfo.cam_pos;
    }
    if (saveinfo.requirements & REQ_POS) {
        angle = saveinfo.angle;
        position = saveinfo.position;
    }
    if (saveinfo.requirements != 0) {
        practice_file.inject_options_after_load = saveinfo.requirements & REQ_CAM ? set_camera_angle_position : set_angle_position;
    }
    practice_file.inject_options_after_counter = saveinfo.counter;
}

void AnySavesMenu::render() {
    if (button_is_pressed(Controller::B)) {
		MenuRendering::set_menu(MN_PRACTICE_INDEX);
        init_once = false;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
        load_save(cursor.y);
        if (cursor.y == DARK_HAMMER_INDEX) {
            TP::set_boss_flags();
        }
        for (size_t i = 0; i < sizeof(specials) / sizeof(specials[0]); ++i) {
            if (cursor.y == specials[i].idx) {
                if (specials[i].cb_during != nullptr) {
                    practice_file.inject_options_during_load = specials[i].cb_during;
                }
                if (specials[i].cb_after != nullptr) {
                    practice_file.inject_options_after_load = specials[i].cb_after;
                }
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(lines, cursor.y, LINES);
};