#include "features/trigger_view/include/trigger_view.h"
#include "collision_view.h"
#include "trigger_view.h"
#include "libtp_c/include/msl_c/math.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "libtp_c/include/d/d_procname.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "libtp_c/include/JSystem/JMath.h"
#include "rels/include/defines.h"

namespace TriggerViewer {

typedef void (*drawCallback)(fopAc_ac_c*);
void searchActorForCallback(s16 actorName, drawCallback callback) {
    node_class* node = g_fopAcTg_Queue.mpHead;
    fopAc_ac_c* actorData = NULL;

    for (int i = 0; i < g_fopAcTg_Queue.mSize; i++) {
        if (node != NULL) {
            create_tag_class* tag = (create_tag_class*)node;
            actorData = (fopAc_ac_c*)tag->mpTagData;

            if (actorData != NULL && actorData->mBase.mProcName == actorName && callback != NULL) {
                callback(actorData);
            }
        }
        node = node->mpNextNode;
    }
}

void drawSceneExit(fopAc_ac_c* actor) {
    struct daScex_c : public fopAc_ac_c {
        /* 0x568 */ Mtx mMatrix;
    };
    daScex_c* scex = (daScex_c*)actor;

    cXyz points[8];
    points[0].set(-actor->mScale.x, actor->mScale.y, -actor->mScale.z);
    points[1].set(actor->mScale.x, actor->mScale.y, -actor->mScale.z);
    points[2].set(-actor->mScale.x, actor->mScale.y, actor->mScale.z);
    points[3].set(actor->mScale.x, actor->mScale.y, actor->mScale.z);
    points[4].set(-actor->mScale.x, 0.0f, -actor->mScale.z);
    points[5].set(actor->mScale.x, 0.0f, -actor->mScale.z);
    points[6].set(-actor->mScale.x, 0.0f, actor->mScale.z);
    points[7].set(actor->mScale.x, 0.0f, actor->mScale.z);

    mDoMtx_inverse(scex->mMatrix, mDoMtx_stack_c::get());
    mDoMtx_multVecArray(mDoMtx_stack_c::get(), points, points, 8);

    GXColor color = {0xFF, 0x00, 0xFF, g_geometryOpacity};
    dDbVw_drawCube8pXlu(points, color);
}

// this one could probably be made more accurate
void drawMidnaStop(fopAc_ac_c* actor) {
    struct daMidnaStop_c : public fopAc_ac_c {
        /* 0x568 */ u8 data[0x5C0 - 0x568];
        /* 0x5C0 */ f32 mRangeXZ;
        /* 0x5C4 */ f32 mRangeY;
    };
    daMidnaStop_c* mstop = (daMidnaStop_c*)actor;

    GXColor color = {0x4A, 0x36, 0xBA, g_geometryOpacity};
    dDbVw_drawCylinderXlu(mstop->current.pos, mstop->mScale.x * 100.0f, mstop->mScale.y, color, 1);
}

// this one might need to be improved? it matches the debug rom tho so idk
void drawSwitchArea(fopAc_ac_c* actor) {
    struct daSwc00_c : public fopAc_ac_c {
        /* 0x568 */ cXyz mStart;
        /* 0x574 */ cXyz mEnd;
        /* 0x580 */ u16 mEventID;
        /* 0x582 */ u8 mAction;
    };
    daSwc00_c* swc = (daSwc00_c*)actor;
    int shape_type = (fopAcM_GetParam(actor) >> 0x12) & 3;

    GXColor color = {0x00, 0x00, 0xFF, g_geometryOpacity};
    if (shape_type == 3) {
        dDbVw_drawCylinderXlu(swc->current.pos, JMAFastSqrt(swc->mScale.x) - 30.0f, swc->mScale.y,
                              color, 1);
    } else if (shape_type == 0) {
        cXyz size = swc->mEnd - swc->mStart;  // diameter
        size *= 0.5f;                         // radius

        cXyz pos = swc->mStart + size;  // base + radius = center point
        csXyz angle(swc->current.angle.x, swc->current.angle.y, swc->current.angle.z);
        dDbVw_drawCubeXlu(pos, size, angle, color);
    }
}

void drawEventArea(fopAc_ac_c* actor) {
    struct daTag_EvtArea_c : public fopAc_ac_c {
        /* 0x568 */ void* vtable;
        /* 0x56C */ u8 field_0x56c;
    };

    u8 type = (actor->shape_angle.z & 0xFF);
    if (type == 0xFF) {
        type = 0;
    }

    if (type == 15 || type == 16) {
        GXColor color = {0xFF, 0xFF, 0x00, g_geometryOpacity};
        cXyz points[8];
        points[0].set(-actor->mScale.x, actor->mScale.y, -actor->mScale.z);
        points[1].set(actor->mScale.x, actor->mScale.y, -actor->mScale.z);
        points[2].set(-actor->mScale.x, actor->mScale.y, actor->mScale.z);
        points[3].set(actor->mScale.x, actor->mScale.y, actor->mScale.z);
        points[4].set(-actor->mScale.x, 0.0f, -actor->mScale.z);
        points[5].set(actor->mScale.x, 0.0f, -actor->mScale.z);
        points[6].set(-actor->mScale.x, 0.0f, actor->mScale.z);
        points[7].set(actor->mScale.x, 0.0f, actor->mScale.z);

        mDoMtx_stack_c::transS(actor->orig.pos.x, actor->orig.pos.y, actor->orig.pos.z);
        mDoMtx_stack_c::YrotS(actor->current.angle.y);
        mDoMtx_multVecArray(mDoMtx_stack_c::get(), points, points, 8);

        dDbVw_drawCube8pXlu(points, color);
    } else {
        GXColor outer_color = {0xFF, 0x00, 0x00, g_geometryOpacity};
        GXColor inner_color = {0x00, 0xFF, 0x00, g_geometryOpacity};
        cXyz pos = actor->current.pos;
        // no good way to draw on the ground, so just keep height around player level
        if (pos.y < dComIfGp_getPlayer()->mLinkAcch.mGroundH) {
            pos.y = dComIfGp_getPlayer()->mLinkAcch.mGroundH + 100.0f;
        }

        // idk the exact way the inner check is handled, so this is a rough approximation
        f32 inner_scale = 0.83f;
#ifdef WII_PLATFORM
        inner_scale = 0.98f;
#endif

        dDbVw_drawCircleXlu(pos, actor->mScale.x * inner_scale, inner_color, 1, 20);
        dDbVw_drawCircleXlu(pos, actor->mScale.x, outer_color, 1, 20);
    }
}

void drawEventTag(fopAc_ac_c* actor) {
    GXColor color = {0x00, 0xC8, 0xFF, g_geometryOpacity};
    u16 area_type = actor->orig.angle.x & 0x8000;

    if (area_type == -0x8000) {
        cXyz points[8];

        cXyz start(actor->current.pos.x - (actor->mScale.x * 0.5f), actor->current.pos.y,
                   actor->current.pos.z - (actor->mScale.z * 0.5f));

        cXyz end(actor->current.pos.x + (actor->mScale.x * 0.5f),
                 actor->current.pos.y + actor->mScale.y,
                 actor->current.pos.z + (actor->mScale.z * 0.5f));

        points[0].set(start.x, start.y, start.z);
        points[1].set(start.x, start.y, end.z);
        points[2].set(end.x, start.y, end.z);
        points[3].set(end.x, start.y, start.z);
        points[4].set(start.x, end.y, start.z);
        points[5].set(start.x, end.y, end.z);
        points[6].set(end.x, end.y, end.z);
        points[7].set(end.x, end.y, start.z);

        dDbVw_drawCube8pXlu(points, color);
    } else {
        cXyz pos = actor->current.pos;
        pos.y -= actor->mScale.y;

        dDbVw_drawCylinderXlu(pos, actor->mScale.x, actor->mScale.y * 2, color, 1);
    }
}

void drawTWGate(fopAc_ac_c* actor) {
    GXColor color = {0xFF, 0xFF, 0xFF, g_geometryOpacity};
    dDbVw_drawCylinderXlu(actor->current.pos, actor->mScale.x * 100.0f, actor->mScale.y * 100.0f,
                          color, 1);
}

static uint8_t pathColorIndex = 0;

void drawPaths(dStage_dPath_c* paths) {
    static const GXColor colors[8] = {
        {0xFF, 0xFF, 0xFF}, {0x00, 0x00, 0x00}, {0xFF, 0x00, 0x00}, {0x00, 0xFF, 0x00},
        {0x00, 0x00, 0xFF}, {0xFF, 0xFF, 0x00}, {0xFF, 0x00, 0xFF}, {0x00, 0xFF, 0xFF},
    };

    cXyz cubeSize = {30.0f, 30.0f, 30.0f};
    csXyz cubeAngle = {0, 0, 0};

    for (int i = 0; i < paths->m_num; i++) {
        dPath* path = &paths->m_path[i];
        GXColor color = colors[(pathColorIndex++) & 7];
        color.a = g_geometryOpacity;
        cXyz a, b;

        // Draw a line back to the beginning if the path loops
        if (dPath_ChkClose(path) && path->m_num > 2) {
            a = path->m_points[0].m_position;
            b = path->m_points[path->m_num - 1].m_position;
            dDbVw_drawLineXlu(a, b, color, 1, 10);
        }

        // Iterate over all of the points of the path
        for (int j = 0; j < path->m_num - 1; j++) {
            a = path->m_points[j].m_position;
            b = path->m_points[j + 1].m_position;
            dDbVw_drawLineXlu(a, b, color, 1, 10);  // Param 3 is if z is enabled or not
            dDbVw_drawCubeXlu(a, cubeSize, cubeAngle, color);
        }
        dDbVw_drawCubeXlu(b, cubeSize, cubeAngle, color);  // Draw the cube for the end of the path
    }
}

void drawStagePaths() {
    dStage_dPath_c* stagePaths = g_dComIfG_gameInfo.play.mStageData.mPath2Info;
    if (stagePaths) {
        drawPaths(stagePaths);
    }
}

void drawCurrentRoomPaths() {
    daAlink_c* player = dComIfGp_getPlayer();
    if (player == NULL) {
        return;
    }

    s32 roomNo = fopAcM_GetRoomNo(player);
    if (roomNo < 0 || roomNo >= 64) {
        return;
    }

    dStage_dPath_c* roomPaths = dStage_roomControl_c__mStatus[roomNo].mPath2Info;
    if (roomPaths) {
        drawPaths(roomPaths);
    }
}

KEEP_FUNC void execute() {
    if (g_triggerViewFlags[VIEW_LOAD_ZONES].active) {
        searchActorForCallback(PROC_SCENE_EXIT, drawSceneExit);
    }

    if (g_triggerViewFlags[VIEW_MIDNA_STOPS].active) {
        searchActorForCallback(PROC_Tag_Mstop, drawMidnaStop);
    }

    if (g_triggerViewFlags[VIEW_SWITCH_AREAS].active) {
        searchActorForCallback(PROC_SWC00, drawSwitchArea);
    }

    if (g_triggerViewFlags[VIEW_EVENT_AREAS].active) {
        searchActorForCallback(PROC_TAG_EVENT, drawEventTag);
        searchActorForCallback(PROC_TAG_EVTAREA, drawEventArea);
    }

    if (g_triggerViewFlags[VIEW_TW_GATES].active) {
        searchActorForCallback(PROC_Tag_TWGate, drawTWGate);
    }

    if (g_triggerViewFlags[VIEW_PATHS].active) {
        pathColorIndex = 0;
        drawStagePaths();
        drawCurrentRoomPaths();
    }
}
}  // namespace TriggerViewer