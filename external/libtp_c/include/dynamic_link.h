#ifndef TP_DYNAMIC_LINK_H
#define TP_DYNAMIC_LINK_H

#include <cstdint>

#include "dolphin/os/OS.h"
#include "JSystem/JKernel/JKRExpHeap.h"

struct DynamicModuleControlBase_ {
    /* 0x00 */ u16 mLinkCount;
    /* 0x02 */ u16 mDoLinkCount;
    /* 0x04 */ DynamicModuleControlBase_* mPrev;
    /* 0x08 */ DynamicModuleControlBase_* mNext;
    /* 0x0C */ void* vtable;
};

class mDoDvdThd_callback_c;
struct DynamicModuleControl : DynamicModuleControlBase_ {
    /* 0x10 */ OSModuleInfo* mModule;
    /* 0x14 */ void* mBss;
    /* 0x18 */ u32 unk_24;
    /* 0x1c */ const char* mName;
    /* 0x20 */ u8 mResourceType;
    /* 0x21 */ u8 unk_33;
    /* 0x22 */ u16 mChecksum;
    /* 0x24 */ s32 mSize;
    /* 0x28 */ mDoDvdThd_callback_c* mAsyncLoadCallback;
};

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