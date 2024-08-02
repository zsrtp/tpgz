#ifndef C_PHASE_H
#define C_PHASE_H

#include "../../dolphin/types.h"

typedef int (*cPhs__Handler)(void*);

enum cPhs__Step {
    /* 0x0 */ cPhs_INIT_e,
    /* 0x1 */ cPhs_LOADING_e,
    /* 0x2 */ cPhs_NEXT_e,
    /* 0x3 */ cPhs_UNK3_e,  // appears to be an alternate error code, unsure how it differs
    /* 0x4 */ cPhs_COMPLEATE_e,
    /* 0x5 */ cPhs_ERROR_e,
};

typedef struct request_of_phase_process_class {
    cPhs__Handler* mpHandlerTable;
    int id;
} request_of_phase_process_class;

#endif