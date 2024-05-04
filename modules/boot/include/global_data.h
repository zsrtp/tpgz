#pragma once
#include "libtp_c/include/f_op/f_op_actor_mng.h"

struct ProjectionLine {
    cXyz pos[40];
    bool got_it; // used for lja
};

extern bool g_freeCamEnabled;
extern bool g_moveLinkEnabled;
extern fopAc_ac_c* g_currentActor;
extern bool g_actorViewEnabled;
extern ProjectionLine g_ljaProjectionLine;
extern ProjectionLine g_midnaChargeProjectionLine;


