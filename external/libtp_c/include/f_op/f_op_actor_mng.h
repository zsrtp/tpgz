#ifndef F_OP_ACTOR_MNG_H_
#define F_OP_ACTOR_MNG_H_

#include "f_op_actor.h"
#include "../f_pc/f_pc_manager.h"
#include "../defines.h"

struct fopAcM_prmBase_class {
    /* 0x00 */ u32 field_0x00;
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ csXyz field_0x10;
    /* 0x16 */ u16 field_0x16;
};  // Size = 0x18

struct fopAcM_prm_class {
    /* 0x00 */ u32 mParameter;  // single u32 Parameter
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ csXyz mAngle;  // rotation
    /* 0x16 */ u16 mEnemyNo;
    /* 0x18 */ u8 mScale[3];
    /* 0x1B */ u8 mGbaName;    // from WW, maybe a different parameter here
    /* 0x1C */ s32 mParentPId;  // parent process ID
    /* 0x20 */ s8 mSubtype;
    /* 0x21 */ s8 mRoomNo;
};

typedef int (*heapCallbackFunc)(fopAc_ac_c*);
typedef int (*createFunc)(void*);

struct DOUBLE_POS {
    double x, y, z;
};

inline s32 fopAcM_GetRoomNo(const fopAc_ac_c* pActor) {
    return (s8)pActor->current.roomNo;
}

inline u32 fopAcM_GetID(const void* pActor) {
    return fpcM_GetID(pActor);
}

inline s16 fopAcM_GetName(void* pActor) {
    return fpcM_GetName(pActor);
}

inline MtxP fopAcM_GetMtx(const fopAc_ac_c* pActor) {
    return pActor->mCullMtx;
}

inline u32 fopAcM_checkStatus(fopAc_ac_c* pActor, u32 status) {
    return pActor->mStatus & status;
}

inline u32 fopAcM_checkCarryNow(fopAc_ac_c* pActor) {
    return pActor->mStatus & 0x2000;
}

enum fopAcM_CARRY {
    /* 0x01 */ fopAcM_CARRY_TYPE_1 = 1,
    /* 0x02 */ fopAcM_CARRY_HEAVY = 2,
    /* 0x04 */ fopAcM_CARRY_SIDE = 4,
    /* 0x08 */ fopAcM_CARRY_TYPE_8 = 8,
    /* 0x10 */ fopAcM_CARRY_LIGHT = 16, // guess based on context
    /* 0x20 */ fopAcM_CARRY_ITEM = 32,
    /* 0x30 */ fopAcM_CARRY_UNK_30 = 0x30,
};

inline u32 fopAcM_CheckCarryType(fopAc_ac_c* actor, fopAcM_CARRY type) {
    return actor->mCarryType & type;
}

inline u32 fopAcM_checkHookCarryNow(fopAc_ac_c* pActor) {
    return fopAcM_checkStatus(pActor, 0x100000);
}

inline u32 fopAcM_GetParam(const void* pActor) {
    return fpcM_GetParam(pActor);
}

inline u32 fopAcM_GetParamBit(void* ac, u8 shift, u8 bit) {
    return (fopAcM_GetParam(ac) >> shift) & ((1 << bit) - 1);
}

inline void fopAcM_SetParam(void* p_actor, u32 param) {
    fpcM_SetParam(p_actor, param);
}

inline void fopAcM_SetJntCol(fopAc_ac_c* i_actorP, dJntCol_c* i_jntColP) {
    i_actorP->mJntCol = i_jntColP;
}

inline s16 fopAcM_GetProfName(const void* pActor) {
    return fpcM_GetProfName(pActor);
}

inline u8 fopAcM_GetGroup(const fopAc_ac_c* p_actor) {
    return p_actor->mGroup;
}

inline void fopAcM_OnStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->mStatus |= flag;
}

inline void fopAcM_OffStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->mStatus &= ~flag;
}

/* inline fopAc_ac_c* fopAcM_Search(fopAcIt_JudgeFunc func, void* param) {
    return (fopAc_ac_c*)fopAcIt_Judge(func, param);
}

inline fopAc_ac_c* fopAcM_SearchByID(unsigned int id) {
    return (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &id);
} */

inline cXyz& fopAcM_GetPosition_p(fopAc_ac_c* pActor) {
    return pActor->current.pos;
}

inline cXyz& fopAcM_GetPosition(fopAc_ac_c* pActor) {
    return pActor->current.pos;
}

inline cXyz& fopAcM_GetOldPosition_p(fopAc_ac_c* pActor) {
    return pActor->next.pos;
}

inline cXyz& fopAcM_GetSpeed_p(fopAc_ac_c* pActor) {
    return pActor->speed;
}

inline csXyz& fopAcM_GetAngle_p(fopAc_ac_c* pActor) {
    return pActor->current.angle;
}

inline csXyz& fopAcM_GetShapeAngle_p(fopAc_ac_c* pActor) {
    return pActor->shape_angle;
}

inline bool fopAcM_CheckCondition(fopAc_ac_c* p_actor, u32 flag) {
    return p_actor->mCondition & flag;
}

inline void fopAcM_OnCondition(fopAc_ac_c* p_actor, u32 flag) {
    p_actor->mCondition |= flag;
}

inline void fopAcM_OffCondition(fopAc_ac_c* p_actor, u32 flag) {
    p_actor->mCondition &= ~flag;
}

inline void fopAcM_SetRoomNo(fopAc_ac_c* actor, s8 roomNo) {
    actor->current.roomNo = roomNo;
}

inline void fopAcM_setHookCarryNow(fopAc_ac_c* actor) {
    fopAcM_OnStatus(actor, 0x100000);
}

inline void fopAcM_cancelHookCarryNow(fopAc_ac_c* actor) {
    fopAcM_OffStatus(actor, 0x100000);
}

inline s8 fopAcM_GetHomeRoomNo(const fopAc_ac_c* pActor) {
    return pActor->orig.roomNo;
}

inline void fopAcM_SetGravity(fopAc_ac_c* actor, f32 gravity) {
    actor->mGravity = gravity;
}

inline void fopAcM_SetMaxFallSpeed(fopAc_ac_c* actor, f32 speed) {
    actor->mMaxFallSpeed = speed;
}

inline void fopAcM_SetMtx(fopAc_ac_c* actor, MtxP m) {
    actor->mCullMtx = m;
}

inline void fopAcM_SetSpeed(fopAc_ac_c* actor, f32 x, f32 y, f32 z) {
    actor->speed.set(x, y, z);
}

inline void fopAcM_SetSpeedF(fopAc_ac_c* actor, f32 f) {
    actor->speedF = f;
}

inline void fopAcM_SetStatus(fopAc_ac_c* actor, u32 status) {
    actor->mStatus = status;
}

inline void fopAcM_SetModel(fopAc_ac_c* actor, J3DModel* model) {
    actor->model = model;
}

inline fopAcM_prm_class* fopAcM_GetAppend(void* actor) {
    return (fopAcM_prm_class*)fpcM_GetAppend(actor);
}

inline f32 fopAcM_GetSpeedF(const fopAc_ac_c* p_actor) {
    return p_actor->speedF;
}

inline f32 fopAcM_GetGravity(const fopAc_ac_c* p_actor) {
    return p_actor->mGravity;
}

inline f32 fopAcM_GetMaxFallSpeed(const fopAc_ac_c* p_actor) {
    return p_actor->mMaxFallSpeed;
}

inline const cXyz& fopAcM_GetSpeed_p(const fopAc_ac_c* p_actor) {
    return p_actor->speed;
}

inline const cXyz& fopAcM_GetPosition_p(const fopAc_ac_c* p_actor) {
    return p_actor->current.pos;
}

inline dJntCol_c* fopAcM_GetJntCol(fopAc_ac_c* i_actor) {
    return i_actor->mJntCol;
}

inline void fopAcM_setCullSizeFar(fopAc_ac_c* i_actor, f32 i_far) {
    i_actor->mCullSizeFar = i_far;
}

inline f32 fopAcM_getCullSizeFar(const fopAc_ac_c* i_actor) {
    return i_actor->mCullSizeFar;
}

inline void fopAcM_SetCullSize(fopAc_ac_c* i_actor, s8 i_cullsize) {
    i_actor->mCullType = i_cullsize;
}

inline int fopAcM_GetCullSize(const fopAc_ac_c* i_actor) {
    return i_actor->mCullType;
}

inline BOOL fopAcM_CULLSIZE_IS_BOX(int i_culltype) {
    return (i_culltype >= 0 && i_culltype < 14) || i_culltype == 14;
}

inline Vec fopAcM_getCullSizeSphereCenter(const fopAc_ac_c* i_actor) {
    return i_actor->mCull.mSphere.mCenter;
}

inline f32 fopAcM_getCullSizeSphereR(const fopAc_ac_c* i_actor) {
    return i_actor->mCull.mSphere.mRadius;
}

inline f32 fopAcM_searchActorDistanceY(const fopAc_ac_c* actorA, const fopAc_ac_c* actorB) {
    return actorB->current.pos.y - actorA->current.pos.y;
}

inline u16 fopAcM_GetSetId(const fopAc_ac_c* p_actor) {
    return p_actor->mSetID;
}

LIBTP_DEFINE_FUNC(fopAcM_create__FsUlPC4cXyziPC5csXyzPC4cXyzSc, fopAcM_create_short__unsigned_long__cXyz_const____int__csXyz_const____cXyz_const____signed_char_,
                  void, fopAcM_create, (s16, u32, const cXyz*, int, const csXyz*, const cXyz*, s8))

LIBTP_DEFINE_FUNC(fopAcM_delete__FP10fopAc_ac_c, fopAcM_delete_fopAc_ac_c___,
                  void, fopAcM_delete, (fopAc_ac_c*))

LIBTP_DEFINE_FUNC(fopAcM_searchActorDistance__FPC10fopAc_ac_cPC10fopAc_ac_c, fopAcM_searchActorDistance_fopAc_ac_c_const____fopAc_ac_c_const___,
                  f32, fopAcM_searchActorDistance, (const fopAc_ac_c*, const fopAc_ac_c*))

extern "C" {
extern node_list_class g_fopAcTg_Queue;
}

#endif
