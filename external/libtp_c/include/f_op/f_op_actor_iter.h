#ifndef F_OP_ACTOR_ITER_H_
#define F_OP_ACTOR_ITER_H_

#include "f_op_actor.h"
#include "../defines.h"

typedef void* (*fopAcIt_JudgeFunc)(void*, void*);

#ifdef WII_PLATFORM
#define fpcSch_JudgeForPName fpcSch_JudgeForPName_void____void___
#else
#define fpcSch_JudgeForPName fpcSch_JudgeForPName__FPvPv
#endif
extern "C" {
void* fpcSch_JudgeForPName(void*, void*);
}

LIBTP_DEFINE_FUNC(fopAcIt_Judge__FPFPvPv_PvPv, fopAcIt_Judge_void______void____void_____void___,
                  void*, fopAcIt_Judge, (fopAcIt_JudgeFunc, void*))

extern "C" {
inline void* fopAcM_SearchByName(s16 name) {
    return fopAcIt_Judge(fpcSch_JudgeForPName, &name);
}
}

#endif
