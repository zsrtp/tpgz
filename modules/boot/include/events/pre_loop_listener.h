#ifndef TPGZ_BOOT_LISTENERS_PRE_LOOP_H
#define TPGZ_BOOT_LISTENERS_PRE_LOOP_H

#include "events/listener_base.h"

typedef void(PreLoopCallback_t)();

typedef events::ListenerBase<PreLoopCallback_t> PreLoopListener;

extern PreLoopListener* g_PreLoopListener;

#endif