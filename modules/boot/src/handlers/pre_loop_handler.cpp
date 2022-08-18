#include "handlers/pre_loop_handler.h"
#include "rels/include/defines.h"

KEEP_VAR PreLoopHandler* g_PreLoopHandler = nullptr;

KEEP_FUNC PreLoopHandler::PreLoopHandler() : HandlerBase() {}

KEEP_FUNC PreLoopHandler::~PreLoopHandler() {}

KEEP_FUNC void PreLoopHandler::handle(PreLoopCallback_t* handler, void*) {
    handler();
}