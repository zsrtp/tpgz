#ifndef F_OP_ACTOR_MNG_H_
#define F_OP_ACTOR_MNG_H_

#include "f_op_actor.h"
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

inline s32 fopAcM_GetRoomNo(const fopAc_ac_c* pActor) {
    return (s8)pActor->mCurrent.mRoomNo;
}

/* inline u32 fopAcM_GetID(const void* pActor) {
    return fpcM_GetID(pActor);
}

inline s16 fopAcM_GetName(fopAc_ac_c* pActor) {
    return fpcM_GetName(pActor);
} */

inline u32 fopAcM_checkStatus(fopAc_ac_c* pActor, u32 status) {
    return pActor->mStatus & status;
}

inline u32 fopAcM_checkCarryNow(fopAc_ac_c* pActor) {
    return pActor->mStatus & 0x2000;
}

inline u32 fopAcM_checkHookCarryNow(fopAc_ac_c* pActor) {
    return fopAcM_checkStatus(pActor, 0x100000);
}

/* inline u32 fopAcM_GetParam(const void* pActor) {
    return fpcM_GetParam(pActor);
} */

inline void fopAcM_OnStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->mStatus |= flag;
}

inline void fopAcM_OffStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->mStatus &= ~flag;
}

/* inline fopAc_ac_c* fopAcM_SearchByID(unsigned int id) {
    return (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &id);
} */

inline csXyz& fopAcM_GetAngle_p(fopAc_ac_c* pActor) {
    return pActor->mCurrent.mAngle;
}

LIBTP_DEFINE_FUNC(fopAcM_create__FsUlPC4cXyziPC5csXyzPC4cXyzSc, fopAcM_create_short__unsigned_long__cXyz_const____int__csXyz_const____cXyz_const____signed_char_,
                  void, fopAcM_create, (s16, u32, const cXyz*, int, const csXyz*, const cXyz*, s8))

extern "C" {
extern node_list_class g_fopAcTg_Queue;
}

#endif
