#ifndef TPGZ_BOOT_LISTENERS_DRAW_H
#define TPGZ_BOOT_LISTENERS_DRAW_H

#include "events/listener_base.h"

typedef void(drawCallback_t)();

typedef events::ListenerBase<drawCallback_t> DrawListener;

extern DrawListener* g_drawListener;

#endif