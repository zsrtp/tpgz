#include "events/post_loop_listener.h"
#include "rels/include/defines.h"

KEEP_VAR PostLoopListener* g_PostLoopListener = nullptr;

KEEP_FUNC PostLoopListener::PostLoopListener() : ListenerBase() {}

KEEP_FUNC PostLoopListener::~PostLoopListener() {}

KEEP_FUNC void PostLoopListener::dispatch(PostLoopCallback_t* cb, void*) {
    cb();
}