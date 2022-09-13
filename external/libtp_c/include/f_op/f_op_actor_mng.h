#ifndef F_OP_ACTOR_MNG_H_
#define F_OP_ACTOR_MNG_H_

#include "f_op_actor.h"
#include "../defines.h"

struct fopAcM_prmBase_class {
    /* 0x00 */ uint32_t field_0x00;
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ csXyz field_0x10;
    /* 0x16 */ uint16_t field_0x16;
};  // Size = 0x18

struct fopAcM_prm_class {
    /* 0x00 */ uint32_t mParameter;  // single uint32_t Parameter
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ csXyz mAngle;  // rotation
    /* 0x16 */ uint16_t mEnemyNo;
    /* 0x18 */ uint8_t mScale[3];
    /* 0x1B */ uint8_t mGbaName;    // from WW, maybe a different parameter here
    /* 0x1C */ int32_t mParentPId;  // parent process ID
    /* 0x20 */ int8_t mSubtype;
    /* 0x21 */ int8_t mRoomNo;
};

typedef int (*heapCallbackFunc)(fopAc_ac_c*);
typedef int (*createFunc)(void*);

inline int32_t fopAcM_GetRoomNo(const fopAc_ac_c* pActor) {
    return (int8_t)pActor->mCurrent.mRoomNo;
}

/* inline uint32_t fopAcM_GetID(const void* pActor) {
    return fpcM_GetID(pActor);
}

inline int16_t fopAcM_GetName(fopAc_ac_c* pActor) {
    return fpcM_GetName(pActor);
} */

inline uint32_t fopAcM_checkStatus(fopAc_ac_c* pActor, uint32_t status) {
    return pActor->mStatus & status;
}

inline uint32_t fopAcM_checkCarryNow(fopAc_ac_c* pActor) {
    return pActor->mStatus & 0x2000;
}

inline uint32_t fopAcM_checkHookCarryNow(fopAc_ac_c* pActor) {
    return fopAcM_checkStatus(pActor, 0x100000);
}

/* inline uint32_t fopAcM_GetParam(const void* pActor) {
    return fpcM_GetParam(pActor);
} */

inline void fopAcM_OnStatus(fopAc_ac_c* pActor, uint32_t flag) {
    pActor->mStatus |= flag;
}

inline void fopAcM_OffStatus(fopAc_ac_c* pActor, uint32_t flag) {
    pActor->mStatus &= ~flag;
}

/* inline fopAc_ac_c* fopAcM_SearchByID(unsigned int id) {
    return (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &id);
} */

inline csXyz& fopAcM_GetAngle_p(fopAc_ac_c* pActor) {
    return pActor->mCurrent.mAngle;
}

LIBTP_DEFINE_FUNC(fopAcM_create__FsUlPC4cXyziPC5csXyzPC4cXyzSc, fopAcM_create_short__unsigned_long__cXyz_const____int__csXyz_const____cXyz_const____signed_char_,
                  void, fopAcM_create, (int16_t, uint32_t, const cXyz*, int, const csXyz*, const cXyz*, int8_t))

extern "C" {
extern node_list_class g_fopAcTg_Queue;
}

#endif
