#ifndef TPGZ_BOOT_LISTENERS_PRE_LOOP_H
#define TPGZ_BOOT_LISTENERS_PRE_LOOP_H

#include "events/listener_base.h"

typedef void(PreLoopCallback_t)();

class PreLoopListener : public events::ListenerBase<PreLoopCallback_t> {
public:
    PreLoopListener();
    virtual ~PreLoopListener();

protected:
    void dispatch(PreLoopCallback_t* cb, void*);
};

extern PreLoopListener* g_PreLoopListener;

#endif