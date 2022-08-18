#include "handlers/draw_handler.h"
#include "rels/include/defines.h"

KEEP_VAR DrawHandler* g_drawHandler = nullptr;

KEEP_FUNC DrawHandler::DrawHandler() : HandlerBase() {}

KEEP_FUNC DrawHandler::~DrawHandler() {}

KEEP_FUNC void DrawHandler::handle(drawCallback_t* handler, void*) {
    handler();
}