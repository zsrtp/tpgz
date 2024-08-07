
#ifndef F_PC_PROFILE_H_
#define F_PC_PROFILE_H_

#include "f_pc_method.h"
#include "../dolphin/types.h"

struct nodedraw_method_class;

typedef struct process_profile_definition {
    s32 mLayerID;
    u16 mListID;
    u16 mListPrio;
    s16 mProcName;
    s16 unkA;  // probably padding
    struct process_method_class* mpPcMtd;
    s32 mSize;
    s32 mSizeOther;
    s32 mParameters;
} process_profile_definition;

#endif
