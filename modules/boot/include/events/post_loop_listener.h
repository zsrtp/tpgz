#ifndef TPGZ_BOOT_LISTENERS_POST_LOOP_H
#define TPGZ_BOOT_LISTENERS_POST_LOOP_H

#include "events/listener_base.h"

typedef void(PostLoopCallback_t)();

typedef events::ListenerBase<PostLoopCallback_t> PostLoopListener;

extern PostLoopListener* g_PostLoopListener;

#endif