#pragma once

#include "save_manager.h"

enum {
    ANY_INDEX,
#ifdef GCN_PLATFORM
    ANY_BITE_INDEX,
#endif
    HUNDO_INDEX,
    AD_INDEX,
#ifdef GCN_PLATFORM
    NOSQ_INDEX,
#endif
    GLITCHLESS_INDEX,
};

#define REQ_POS 1
#define REQ_CAM 2

extern int last_save_index;
extern char last_category[5];
extern special last_special;
extern int last_special_size;
