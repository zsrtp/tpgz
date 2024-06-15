#ifndef F_F_OP_SCENE_REQ_H_
#define F_F_OP_SCENE_REQ_H_

#include "../dolphin/types.h"

struct LoadingInfo {
    u32 isLoading;  // 80450CE0
    u8 _p0[0x04];   // 80450CE4
};

#define fopScnRq isLoading
extern LoadingInfo fopScnRq;

#endif