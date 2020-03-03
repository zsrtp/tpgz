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
#define LINES 21

static int cursor = 1;

Line lines[LINES] = {
    {"practice", 0, "", false},
    {"", 1, "", false},
    {"goats", GOATS_INDEX, "goat herding 2", false},
    {"sword and shield skip", HUGO_INDEX, "hangin' with hugo", false},
    {"purple mist", MIST_INDEX, "purple mist in faron woods (post EMS)", false},
    {"forest bit", FRST_BIT_INDEX, "back in time in forest temple", false},
    {"gorge void", GORGE_VOID_INDEX, "the worst trick", false},
    {"pillar clip", PILLAR_CLIP_INDEX, "pillar clip in lake hylia", false},
    {"deku toad", TOAD_INDEX, "the miniboss of lakebed temple", false},
    {"boss bug", BOSS_BUG_INDEX, "lanyru twilight boss bug", false},
    {"norgor", NORGOR_INDEX, "goron bomb bag without water bombs", false},
    {"lakebed bk skip", LAKEBED_BK_SKIP_INDEX, "boss key skip in lakebed main room", false},
    {"one bomb morpheel", ONEBOMB_INDEX, "kill morpheel with just one water bomb", false},
    {"mdh bridge", MDH_BRIDGE_INDEX, "the falling bridge on castle rooftops", false},
    {"bulblin camp", BULBLIN_CAMP_INDEX, "the area before arbiter's grounds", false},
    {"poe 1 skip", POE_1_SKIP_INDEX, "the pillar jump in arbiter's grounds", false},
    {"death sword skip", DSS_INDEX, "the arbiter's grounds miniboss", false},
    {"stallord", STALLORD_INDEX, "the arbiter's grounds boss", false},
    {"aeralfos skip", AERALFOS_SKIP_INDEX, "the city in the sky miniboss", false},
    {"fan tower", FAN_TOWER_INDEX, "final fan room in city before the boss", false},
    {"early platform", EARLY_PLATFORM_INDEX, "early platform in palace of twilight", false}};
void prep_load_with_options(Options options) {
    practice_file.inject_options = true;
    practice_file.options = options;

    //enable flags
    inject_save_flag = true;
    prac_visible = false;
    fifo_visible = true;
    cursor = 1;
}

void prep_load() {
    
    //don't inject options
    practice_file.inject_options = false;

    //enable flags
    inject_save_flag = true;
    prac_visible = false;
    fifo_visible = true;
    cursor = 1;
};

void PracticeMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        prac_visible = false;
        mm_visible = true;
        cursor = 1;
        return;
    };

    if (button_is_pressed(Controller::A)) {
        switch (cursor) {
            case GOATS_INDEX: {
                loadFile("tpgz/save_files/goats.bin");
                prep_load();
                break;
            }
            case HUGO_INDEX: {
                loadFile("tpgz/save_files/hugo.bin");
                prep_load();
                break;
            }
            case MIST_INDEX: {
                loadFile("tpgz/save_files/purple_mist.bin");
                prep_load();
                break;
            }
            case FRST_BIT_INDEX: {
                loadFile("tpgz/save_files/forest_bit.bin");
                prep_load();
                break;
            }
            case GORGE_VOID_INDEX: {
                loadFile("tpgz/save_files/gorge_void.bin");
                prep_load();
                break;
            }
            case PILLAR_CLIP_INDEX: {
                loadFile("tpgz/save_files/pillar_clip.bin");
                prep_load();
                break;
            }
            case TOAD_INDEX: {
                loadFile("tpgz/save_files/deku_toad.bin");
                prep_load();
                break;
            }
            case BOSS_BUG_INDEX: {
                Options options;
                options.angle = 21504;
                options.position = {-89100.00f,-18811.2363f,39410.00f};
                loadFile("tpgz/save_files/boss_bug.bin");
                prep_load_with_options(options);
                break;
            }
            case NORGOR_INDEX: {
                Options options;
                options.angle = 46568;
                options.position = {173.71f,-186.52f,-3633.71f};
                loadFile("tpgz/save_files/norgor.bin");
                prep_load_with_options(options);
                break;
            }
            case LAKEBED_BK_SKIP_INDEX: {
                loadFile("tpgz/save_files/lakebed_bk_skip.bin");
                prep_load();
                break;
            }
            case ONEBOMB_INDEX: {
                loadFile("tpgz/save_files/onebomb.bin");
                prep_load();
                break;
            }
            case MDH_BRIDGE_INDEX: {
                loadFile("tpgz/save_files/mdh_bridge.bin");
                prep_load();
                break;
            }
            case BULBLIN_CAMP_INDEX: {
                loadFile("tpgz/save_files/camp.bin");
                prep_load();
                break;
            }
            case POE_1_SKIP_INDEX: {
                loadFile("tpgz/save_files/poe_1_skip.bin");
                prep_load();
                break;
            }
            case DSS_INDEX: {
                loadFile("tpgz/save_files/death_sword_skip.bin");
                prep_load();
                break;
            }
            case STALLORD_INDEX: {
                loadFile("tpgz/save_files/stallord.bin");
                prep_load();
                break;
            }
            case AERALFOS_SKIP_INDEX: {
                loadFile("tpgz/save_files/aeralfos_skip.bin");
                prep_load();
                break;
            }
            case FAN_TOWER_INDEX: {
                loadFile("tpgz/save_files/fan_tower.bin");
                prep_load();
                break;
            }
            case EARLY_PLATFORM_INDEX: {
                loadFile("tpgz/save_files/early_platform.bin");
                prep_load();
                break;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor, LINES);
};