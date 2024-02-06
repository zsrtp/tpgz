#ifndef F_PC_MANAGER_H_
#define F_PC_MANAGER_H_

#include "f_pc_leaf.h"

enum {
    fpcM_ERROR_PROCESS_ID_e = -1,
};

typedef int (*FastCreateReqFunc)(void*);
typedef void (*fpcM_ManagementFunc)(void);
typedef int (*fpcM_DrawIteraterFunc)(void*, void*);

inline u32 fpcM_GetID(const void* pProc) {
    return pProc != NULL ? ((base_process_class*)pProc)->mBsPcId : 0xFFFFFFFF;
}
inline s16 fpcM_GetName(const void* pActor) {
    return ((base_process_class*)pActor)->mProcName;
}
inline u32 fpcM_GetParam(const void* pActor) {
    return ((base_process_class*)pActor)->mParameters;
}

inline void fpcM_SetParam(void* p_actor, u32 param) {
    ((base_process_class*)p_actor)->mParameters = param;
}

inline s16 fpcM_GetProfName(const void* pActor) {
    return ((base_process_class*)pActor)->mBsTypeId;
}

inline bool fpcM_IsFirstCreating(void* proc) {
    return ((base_process_class*)proc)->mInitState == 0;
}

inline void* fpcM_GetAppend(const void* proc) {
    return ((base_process_class*)proc)->mpUserData;
}

#endif
