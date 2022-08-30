#ifndef TPGZ_BOOT_LISTENERS_DRAW_H
#define TPGZ_BOOT_LISTENERS_DRAW_H

#include "events/listener_base.h"

typedef void(drawCallback_t)();

class DrawListener : public events::ListenerBase<drawCallback_t> {
public:
    DrawListener();
    virtual ~DrawListener();

protected:
    void dispatch(drawCallback_t* cb, void*);
};

extern DrawListener* g_drawListener;

#endif