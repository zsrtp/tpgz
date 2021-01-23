#include "utils/loading.h"
#include "fifo_queue.h"
#include "fs.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menus/practice_menu.h"
#include "save_injector.h"
#include "menus/any_saves_menu.h"

bool loading_initiated = false;
int apply_after_counter = 0;
char last_category[5];
int last_save_index;

namespace Utilities {

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

void default_load() {
    //practice_file.inject_options_before_load = SaveInjector::inject_default_before;
    practice_file.inject_options_during_load = SaveInjector::inject_default_during;
    practice_file.inject_options_after_load = SaveInjector::inject_default_after;
    inject_save_flag = true;
    fifo_visible = true;
    MenuRendering::set_menu(MN_NONE_INDEX);
}

void load_save(uint32_t id, char* category, special i_specials[], int size) {

    SaveInjector::inject_default_before();
    // Load the corresponding file path and properties
    PracticeSaveInfo saveinfo __attribute__((aligned(32)));
    char buf[80];
    tp_sprintf(buf, "tpgz/save_files/%s.bin", category);
    loadFile(buf, &saveinfo, sizeof(saveinfo), id * sizeof(saveinfo));
    tp_sprintf(buf, "tpgz/save_files/%s/%s.bin", category, saveinfo.filename);

    // Load the file into memory
    Utilities::load_save_file(buf);

    if (g_area_reload_behavior == LOAD_AREA || size != 0xFF) {
        default_load();
    }

    if (saveinfo.requirements & REQ_CAM) {
        camera.target = saveinfo.cam_target;
        camera.pos = saveinfo.cam_pos;
    }

    if (saveinfo.requirements & REQ_POS) {
        angle = saveinfo.angle;
        position = saveinfo.position;
    }

    if (saveinfo.requirements != 0) {
        practice_file.inject_options_after_load = saveinfo.requirements & REQ_CAM ?
                                                      Utilities::set_camera_angle_position :
                                                      Utilities::set_angle_position;
    }

    practice_file.inject_options_after_counter = saveinfo.counter;

    tp_bossFlags = 0;

    for (int i = 0; i < size; ++i) {
        if (id == i_specials[i].idx) {
            if (i_specials[i].CallbackDuring) {
                practice_file.inject_options_during_load = i_specials[i].CallbackDuring;
            }
            if (i_specials[i].CallbackAfter) {
                practice_file.inject_options_after_load = i_specials[i].CallbackAfter;
            }
        }
    }

    // store last save file index and category in case file reload is used
    last_save_index = id;
    tp_strcpy(last_category, category);
}

void load_save_file(const char* fileName) {
    loadFile(fileName, (void*)sTmpBuf, 2400, 0);
    SaveInjector::inject_save((void*)sTmpBuf);
}

void trigger_load() {
    if (!tp_fopScnRq.isLoading && !loading_initiated) {
        if (practice_file.inject_options_before_load) {
            practice_file.inject_options_before_load();
        }
        tp_gameInfo.warp.enabled = true;
    }

    if (tp_fopScnRq.isLoading && tp_gameInfo.warp.enabled) {
        if (practice_file.inject_options_during_load) {
            practice_file.inject_options_during_load();
        }
        loading_initiated = true;
        tp_gameInfo.warp.enabled = false;
    }

    if (loading_initiated) {
        if (!tp_fopScnRq.isLoading) {
            if (practice_file.inject_options_after_load) {
                practice_file.inject_options_after_load();
            }
            if (practice_file.inject_options_after_counter == apply_after_counter) {
                apply_after_counter = 0;
                practice_file.inject_options_after_counter = 0;
                loading_initiated = false;
                inject_save_flag = false;
            } else {
                apply_after_counter++;
            }
        }
    }
}
}  // namespace Utilities