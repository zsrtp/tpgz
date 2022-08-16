#ifndef TPGZ_BOOT_HANDLERS_DRAW_H
#define TPGZ_BOOT_HANDLERS_DRAW_H

#include "handlers/handler_base.h"

typedef void (drawCallback_t)();

class DrawHandler : public handler::HandlerBase<drawCallback_t> {
public:
    DrawHandler();
    virtual ~DrawHandler();

protected:
    void handle(drawCallback_t* handler, void*);
};

extern DrawHandler* g_drawHandler;

#endif