
#ifndef F_PC_PROFILE_H_
#define F_PC_PROFILE_H_

#include "f_pc_method.h"
#include <stdint.h>

struct nodedraw_method_class;

typedef struct process_profile_definition {
    int32_t mLayerID;
    uint16_t mListID;
    uint16_t mListPrio;
    int16_t mProcName;
    int16_t unkA;  // probably padding
    struct process_method_class* mpPcMtd;
    int32_t mSize;
    int32_t mSizeOther;
    int32_t mParameters;
} process_profile_definition;

#endif
