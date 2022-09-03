
#ifndef F_PC_BASE_H_
#define F_PC_BASE_H_

#include "../SSystem/SComponent/c_tag.h"
#include "f_pc_delete_tag.h"
#include "f_pc_layer_tag.h"
#include "f_pc_line_tag.h"
#include "f_pc_priority.h"
#include "f_pc_profile.h"

struct create_request;
struct profile_method_class;

typedef struct base_process_class {
    /* 0x00 */ uint32_t mBsType;
    /* 0x04 */ uint32_t mBsPcId;
    /* 0x08 */ int16_t mProcName;
    /* 0x0A */ int8_t mUnk0;
    /* 0x0B */ uint8_t mPauseFlag;
    /* 0x0C */ int8_t mInitState;
    /* 0x0D */ uint8_t mUnk2;
    /* 0x0E */ int16_t mBsTypeId;
    /* 0x10 */ process_profile_definition* mpProf;
    /* 0x14 */ struct create_request* mpCtRq;
    /* 0x18 */ layer_management_tag_class mLyTg;
    /* 0x34 */ line_tag mLnTg;
    /* 0x4C */ delete_tag_class mDtTg;
    /* 0x68 */ process_priority_class mPi;
    /* 0xA8 */ process_method_class* mpPcMtd;
    /* 0xAC */ void* mpUserData;
    /* 0xB0 */ uint32_t mParameters;
    /* 0xB4 */ uint32_t mSubType;
} base_process_class;  // Size: 0xB8

#endif
