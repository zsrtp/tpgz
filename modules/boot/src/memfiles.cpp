#include "memfiles.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "rels/include/defines.h"

KEEP_VAR PositionData memfile_posdata;

KEEP_FUNC void GZ_setLinkPosition() {
    dComIfGp_getPlayer()->mCurrent.mPosition = memfile_posdata.link;
    matrixInfo.matrix_info->target = memfile_posdata.cam.target;
    matrixInfo.matrix_info->pos = memfile_posdata.cam.pos;
    dComIfGp_getPlayer()->mCollisionRot.mY = memfile_posdata.angle;
}
