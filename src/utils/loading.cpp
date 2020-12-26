#include "utils/loading.h"
#include "fifo_queue.h"
#include "fs.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menus/practice_menu.h"
#include "save_injector.h"

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
    practice_file.inject_options_before_load = SaveInjector::inject_default_before;
    practice_file.inject_options_during_load = SaveInjector::inject_default_during;
    practice_file.inject_options_after_load = SaveInjector::inject_default_after;
    inject_save_flag = true;
    fifo_visible = true;
    MenuRendering::set_menu(MN_NONE_INDEX);
}

void load_save(uint32_t id, char* category) {
    PracticeSaveInfo saveinfo __attribute__((aligned(32)));
    char buf[80];
    tp_sprintf(buf, "tpgz/save_files/%s.bin", category);
    loadFile(buf, &saveinfo, sizeof(saveinfo), id * sizeof(saveinfo));
    tp_sprintf(buf, "tpgz/save_files/%s/%s.bin", category, saveinfo.filename);
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
        practice_file.inject_options_after_load = saveinfo.requirements & REQ_CAM ?
                                                      Utilities::set_camera_angle_position :
                                                      Utilities::set_angle_position;
    }
    practice_file.inject_options_after_counter = saveinfo.counter;
    last_save_index = id;
    tp_strcpy(last_category, category);
}

void load_save_file(const char* fileName) {
    uint8_t qlog_bytes[2392] __attribute__((aligned(32)));
    loadFile(fileName, qlog_bytes, 2400, 0);
    // load file
    SaveInjector::inject_save(qlog_bytes);
}

void trigger_load() {
    if (tp_fopScnRq.isLoading == 0 && !loading_initiated) {
        if (practice_file.inject_options_before_load) {
            practice_file.inject_options_before_load();
        }
        tp_gameInfo.warp.enabled = true;
    }

    if (tp_fopScnRq.isLoading == 1) {
        if (practice_file.inject_options_during_load) {
            practice_file.inject_options_during_load();
        }
        loading_initiated = true;
    }

    if (loading_initiated == true) {
        if (tp_fopScnRq.isLoading == 0) {
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