#include "features/projection_view/include/projection_view.h"
#include "libtp_c/include/d/a/d_a_alink.h"
#include "collision_view.h"
#include "projection_view.h"
#include "rels/include/defines.h"
#include "libtp_c/include/d/d_procname.h"
#include "global_data.h"
#include "settings.h"

namespace ProjectionViewer {

typedef void (*drawCallback)(fopAc_ac_c*);
void searchActorForCallback(s16 actorName, drawCallback callback) {
    node_class* node = g_fopAcTg_Queue.mpHead;
    fopAc_ac_c* actorData = NULL;

    for (int i = 0; i < g_fopAcTg_Queue.mSize; i++) {
        if (node != NULL) {
            create_tag_class* tag = (create_tag_class*)node;
            actorData = (fopAc_ac_c*)tag->mpTagData;

            // special check to run the callback on all valid actors if name is -1
            bool check_all_actors = actorName == -1;

            if (actorData != NULL && (actorData->mBase.mProcName == actorName || check_all_actors) && callback != NULL) {
                callback(actorData);
            }
        }
        node = node->mpNextNode;
    }
}

void drawMidnaChargePositionProjection(fopAc_ac_c* actor) {
    daAlink_c* alink = (daAlink_c*)actor;

    if (alink->mActionID == daAlink_c::PROC_WOLF_ROLL_ATTACK || alink->mActionID == daAlink_c::PROC_WOLF_ROLL_ATTACK_MOVE || alink->mActionID == daAlink_c::PROC_WOLF_LOCK_ATTACK || alink->mActionID == daAlink_c::PROC_WOLF_LOCK_ATTACK_TURN) {
        GXColor red = {0xFF, 0x00, 0x00, g_geometryOpacity};
        dBgS_GndChk gnd_chk;

        for (int i = 0; i < 40; i++) {
            if (i < 39) {
                if (alink->mWolfLockNum != 0)
                dDbVw_drawLineXlu(g_midnaChargeProjectionLine.pos[i], g_midnaChargeProjectionLine.pos[i+1], red, 1, 40);
            }    
        }
    }
}

void drawJumpAttackPositionProjection(fopAc_ac_c* actor) {
    daAlink_c* alink = (daAlink_c*)actor;

    if ((alink->mActionID == daAlink_c::PROC_ATN_ACTOR_WAIT || alink->mActionID == daAlink_c::PROC_CUT_JUMP) && alink->mTargetedActor) {
        GXColor red = {0xFF, 0x00, 0x00, g_geometryOpacity};
        GXColor green = {0x00, 0xFF, 0x00, g_geometryOpacity};

        for (int i = 0; i < 40; i++) {
            if (i < 39) {
                dDbVw_drawLineXlu(g_ljaProjectionLine.pos[i], g_ljaProjectionLine.pos[i+1], (g_ljaProjectionLine.got_it ? green : red), 1, 20);
            }
        }
    }
}

#include "libtp_c/include/m_Do/m_Do_printf.h"

KEEP_FUNC void execute() {
    if (GZStng_getData(STNG_SCENE_LJA_PROJECTION, false)) {
        searchActorForCallback(PROC_ALINK, drawJumpAttackPositionProjection);
    }

    if (GZStng_getData(STNG_SCENE_MIDNA_CHARGE_PROJECTION, false)) {
        searchActorForCallback(PROC_ALINK, drawMidnaChargePositionProjection);
    }
}
}  // namespace ProjectionViewer