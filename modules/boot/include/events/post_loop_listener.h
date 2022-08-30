#ifndef TPGZ_BOOT_LISTENERS_POST_LOOP_H
#define TPGZ_BOOT_LISTENERS_POST_LOOP_H

#include "events/listener_base.h"

typedef void(PostLoopCallback_t)();

class PostLoopListener : public events::ListenerBase<PostLoopCallback_t> {
public:
    PostLoopListener();
    virtual ~PostLoopListener();

protected:
    void dispatch(PostLoopCallback_t* cb, void*);
};

extern PostLoopListener* g_PostLoopListener;

#endif