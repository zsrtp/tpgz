#include "memfiles.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "rels/include/defines.h"

KEEP_VAR bool g_injectMemfile;
KEEP_VAR bool set_position_data;
KEEP_VAR PositionData memfile_posdata;

bool l_dataCopied;
cXyz l_tmpPos = g_dComIfG_gameInfo.info.mRestart.mRoomPos;
uint16_t l_tmpAngle = g_dComIfG_gameInfo.info.mRestart.mRoomAngleY;

KEEP_FUNC void GZ_setLinkPosition() {
    static int8_t sLoadDelay = 10;

    if (l_fopScnRq_IsUsingOfOverlap == 1) {
        sLoadDelay--;
    }

    // respawn pos gets overwritten by default spawn, so reinject respawn info
    if (!l_dataCopied) {
        l_tmpPos = g_dComIfG_gameInfo.info.mRestart.mRoomPos;
        l_tmpAngle = g_dComIfG_gameInfo.info.mRestart.mRoomAngleY;
        l_dataCopied = true;
    }

    if (sLoadDelay == 0) {
        if (dComIfGp_getPlayer() != nullptr) {
            dComIfGp_getPlayer()->mCurrent.mPosition = memfile_posdata.link;
            matrixInfo.matrix_info->target = memfile_posdata.cam.target;
            matrixInfo.matrix_info->pos = memfile_posdata.cam.pos;
            dComIfGp_getPlayer()->mCollisionRot.mY = memfile_posdata.angle;
            g_dComIfG_gameInfo.info.mRestart.mRoomPos = l_tmpPos;
            g_dComIfG_gameInfo.info.mRestart.mRoomAngleY = l_tmpAngle;
            l_dataCopied = false;
        }
        sLoadDelay = 10;
    }
}
