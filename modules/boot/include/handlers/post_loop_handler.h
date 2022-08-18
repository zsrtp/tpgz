#ifndef TPGZ_BOOT_HANDLERS_POST_LOOP_H
#define TPGZ_BOOT_HANDLERS_POST_LOOP_H

#include "handlers/handler_base.h"

typedef void(PostLoopCallback_t)();

class PostLoopHandler : public handler::HandlerBase<PostLoopCallback_t> {
public:
    PostLoopHandler();
    virtual ~PostLoopHandler();

protected:
    void handle(PostLoopCallback_t* handler, void*);
};

extern PostLoopHandler* g_PostLoopHandler;

#endif