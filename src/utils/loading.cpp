#include "utils/loading.h"
#include "fifo_queue.h"
#include "fs.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menus/practice_menu.h"

#include "menus/any_saves_menu.h"
#include "save_manager.h"

namespace Utilities {

void set_camera_angle_position() {
    tp_matrixInfo.matrix_info->target = gSaveManager.mPracticeSaveInfo.cam_target;
    tp_matrixInfo.matrix_info->pos = gSaveManager.mPracticeSaveInfo.cam_pos;
    tp_zelAudio.link_debug_ptr->facing = gSaveManager.mPracticeSaveInfo.angle;
    tp_zelAudio.link_debug_ptr->position = gSaveManager.mPracticeSaveInfo.position;
    tp_osReport("%d", gSaveManager.mPracticeSaveInfo.angle);
    tp_osReport("0x%08X", &gSaveManager.mPracticeSaveInfo.angle);
}

void set_angle_position() {
    tp_zelAudio.link_debug_ptr->facing = gSaveManager.mPracticeSaveInfo.angle;
    tp_zelAudio.link_debug_ptr->position = gSaveManager.mPracticeSaveInfo.position;
}

}  // namespace Utilities