#ifndef TPGZ_BOOT_HANDLERS_PRE_LOOP_H
#define TPGZ_BOOT_HANDLERS_PRE_LOOP_H

#include "handlers/handler_base.h"

typedef void(PreLoopCallback_t)();

class PreLoopHandler : public handler::HandlerBase<PreLoopCallback_t> {
public:
    PreLoopHandler();
    virtual ~PreLoopHandler();

protected:
    void handle(PreLoopCallback_t* handler, void*);
};

extern PreLoopHandler* g_PreLoopHandler;

#endif