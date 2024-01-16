/**	@file dynamic_link.h
 *	@brief DynamicModuleControl field
 *
 *  @author Zephiles
 *	@bug No known bugs.
 */
#ifndef TP_DYNAMIC_LINK_H
#define TP_DYNAMIC_LINK_H

#include <cstdint>

#include "dolphin/os/OS.h"
#include "JSystem/JKernel/JKRExpHeap.h"

// Should try to fill in the variables at some point
struct DynamicModuleControl {
    u8 unk_0[0x10];
    OSModuleInfo* moduleInfo;
    u8 unk_10[0x18];
} __attribute__((__packed__));

// This size may not be correct
static_assert(sizeof(DynamicModuleControl) == 0x2C);

extern "C" {
bool do_link(DynamicModuleControl* dmc);
bool do_unlink(DynamicModuleControl* dmc);
}

namespace DynamicModuleControlBase {
extern "C" {
extern JKRHeap* m_heap;
}
}  // namespace DynamicModuleControlBase
#endif