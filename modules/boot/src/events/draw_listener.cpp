#include "events/draw_listener.h"
#include "rels/include/defines.h"

KEEP_VAR DrawListener* g_drawListener = nullptr;

KEEP_FUNC DrawListener::DrawListener() : ListenerBase() {}

KEEP_FUNC DrawListener::~DrawListener() {}

KEEP_FUNC void DrawListener::dispatch(drawCallback_t* cb, void*) {
    cb();
}