#include "handlers/post_loop_handler.h"
#include "rels/include/defines.h"

KEEP_VAR PostLoopHandler* g_PostLoopHandler = nullptr;

KEEP_FUNC PostLoopHandler::PostLoopHandler(): HandlerBase() {}

KEEP_FUNC PostLoopHandler::~PostLoopHandler() {}

KEEP_FUNC void PostLoopHandler::handle(PostLoopCallback_t* handler, void*) {
    handler();
}