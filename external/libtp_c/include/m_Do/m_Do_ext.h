#ifndef M_DO_M_DO_EXT_H
#define M_DO_M_DO_EXT_H

#include "../dolphin/types.h"
#include "../dolphin/gx/gx.h"
#include "../JSystem/J3DGraphBase/J3DPacket.h"
#include "../JSystem/J3DGraphBase/J3DSys.h"
#include "../m_Do/m_Do_mtx.h"
#include "../SSystem/SComponent/c_xyz.h"
#include "../SSystem/SComponent/c_sxyz.h"
#include "libtp_c/include/JSystem/JKernel/JKRExpHeap.h"

struct J3DAnmTransform {};

class J3DGXColorS10 {
public:
    GXColorS10 mColor;
};

#pragma pack(push, 1)
class J3DFrameCtrl {
public:
    void* vtable;
    u8 mAttribute;
    bool mState;
    s16 mStart;
    s16 mEnd;
    s16 mLoop;
    f32 mRate;
    f32 mFrame;
};
#pragma pack(pop)

#pragma pack(push, 1)
class mDoExt_baseAnm {
public:
    J3DFrameCtrl frame_control;
};
#pragma pack(pop)

#pragma pack(push, 1)
class mDoExt_btkAnm {
public:
    mDoExt_baseAnm mBaseAnm;
    u32 field_0x14;
};
#pragma pack(pop)

#pragma pack(push, 1)
class mDoExt_brkAnm {
public:
    mDoExt_baseAnm mBaseAnm;
    u32 field_0x14;
};
#pragma pack(pop)

#pragma pack(push, 1)
class mDoExt_bpkAnm {
public:
    mDoExt_baseAnm mBaseAnm;
    u32 field_0x14;
};
#pragma pack(pop)

#pragma pack(push, 1)
class mDoExt_bckAnm {
public:
    mDoExt_baseAnm mBaseAnm;
    u8 field_0x14[4];
    u32 field_0x18;
};  // Size = 0x1C
#pragma pack(pop)

class mDoExt_McaMorfCallBack1_c {
public:
    void* vtable;
};

class mDoExt_AnmRatioPack {
public:
    /* 0x0 */ f32 mRatio;
    /* 0x4 */ J3DAnmTransform* mAnmTransform;
};  // Size = 0x8

namespace m_Do_ext {
extern "C" {
extern JKRHeap* AssertHeap;
extern JKRHeap* DbPrintHeap;
extern JKRHeap* gameHeap;
extern JKRHeap* zeldaHeap;
extern JKRHeap* commandHeap;
extern JKRHeap* archiveHeap;  // Archive heap pointer
extern JKRHeap* j2dHeap;

#ifndef WII_PLATFORM
extern JKRHeap* HostIOHeap;
#endif  // WII_PLATFORM
}
}  // namespace m_Do_ext
#endif /* M_DO_M_DO_EXT_H */
