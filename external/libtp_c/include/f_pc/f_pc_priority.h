
#ifndef F_PC_PRIORITY_H_
#define F_PC_PRIORITY_H_

#include "../SSystem/SComponent/c_tag.h"
#include "f_pc_method_tag.h"

typedef struct process_priority_queue_info {
    u32 mLayer;
    u16 mListID;
    u16 mListPrio;
} process_priority_queue_info;

typedef struct process_priority_class {
    /* 0x00 */ create_tag_class mBase;
    /* 0x14 */ process_method_tag_class mMtdTag;
    /* 0x30 */ process_priority_queue_info mInfoQ;
    /* 0x38 */ process_priority_queue_info mInfoCurr;
} process_priority_class;

#endif
