#include "events/pre_loop_listener.h"
#include "rels/include/defines.h"

KEEP_VAR PreLoopListener* g_PreLoopListener = nullptr;

KEEP_FUNC PreLoopListener::PreLoopListener() : ListenerBase() {}

KEEP_FUNC PreLoopListener::~PreLoopListener() {}

KEEP_FUNC void PreLoopListener::dispatch(PreLoopCallback_t* cb, void*) {
    cb();
}