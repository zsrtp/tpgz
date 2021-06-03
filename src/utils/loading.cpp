#include "utils/loading.h"
#include "fifo_queue.h"
#include "fs.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/practice_menu.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "libtp_c/include/m_Do/m_Do_audio.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "menus/any_saves_menu.h"
#include "save_manager.h"

namespace Utilities {

void set_camera_angle_position() {
    tp_matrixInfo.matrix_info->target = gSaveManager.mPracticeSaveInfo.cam_target;
    tp_matrixInfo.matrix_info->pos = gSaveManager.mPracticeSaveInfo.cam_pos;
    dComIfGp_getPlayer()->mCollisionRot.mY = gSaveManager.mPracticeSaveInfo.angle;
    cXyz tmp(gSaveManager.mPracticeSaveInfo.position.x, gSaveManager.mPracticeSaveInfo.position.y, gSaveManager.mPracticeSaveInfo.position.z);
    dComIfGp_getPlayer()->mCurrent.mPosition = tmp;
    tp_osReport("%d", gSaveManager.mPracticeSaveInfo.angle);
    tp_osReport("0x%08X", &gSaveManager.mPracticeSaveInfo.angle);
}

void set_angle_position() {
    dComIfGp_getPlayer()->mCollisionRot.mY = gSaveManager.mPracticeSaveInfo.angle;

    cXyz tmp(gSaveManager.mPracticeSaveInfo.position.x, gSaveManager.mPracticeSaveInfo.position.y, gSaveManager.mPracticeSaveInfo.position.z);
    dComIfGp_getPlayer()->mCurrent.mPosition = tmp;
}

}  // namespace Utilities