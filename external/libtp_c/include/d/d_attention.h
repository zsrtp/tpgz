#ifndef D_D_ATTENTION_H
#define D_D_ATTENTION_H

#include "../SSystem/SComponent/c_angle.h"
#include "save/d_save.h"
#include "../m_Do/m_Do_ext.h"

class dAttHint_c {
public:
    u32 field_0x0;
    u32 field_0x4;
    u32 field_0x8;
};

class dAttCatch_c {
public:
    void* field_0x0;
    u32 field_0x4;
    f32 field_0x8;
    u8 field_0xc;
    u8 field_0xd;
    u8 field_0xe;
    u8 field_0xf;
    u32 field_0x10;
    u8 mChangeItem;
};  // Size = 0x14

class dAttParam_c {
public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ u8 field_0x4;
    /* 0x05 */ u8 field_0x5;
    /* 0x06 */ u16 mFlag;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xc;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1c;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ u8 field_0x38;
    /* 0x39 */ u8 field_0x39;
    /* 0x3C */ f32 field_0x3c;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ u32 field_0x44;
    /* 0x48 */ u32 field_0x48;
};  // Size = 0x4C

class dAttLook_c {
public:
    u32 field_0x0;
    u32 field_0x4;
    f32 field_0x8;
    u32 field_0xc;
};  // Size = 0x10

#pragma pack(push, 1)
class dAttList_c {
public:
    u8 field_0x0[8];
    cSAngle angle;
    u8 field_0xa[10];
};  // Size = 0x14
#pragma pack(pop)

class dAttDraw_c {
public:
    u8 field_0x0;
    u8 field_0x1;
    u8 field_0x2;
    u8 field_0x3;
    u8 field_0x4;
    u8 field_0x5;
    u8 field_0x6;
    u8 field_0x7;
    /* 0x008 */ mDoExt_bckAnm bckAnm[2];
    /* 0x040 */ mDoExt_bpkAnm bpkAnm[2];
    /* 0x070 */ mDoExt_brkAnm brkAnm[2];
    /* 0x0A0 */ mDoExt_brkAnm brkAnm2[2];
    /* 0x0D0 */ mDoExt_btkAnm btkAnm[2];
    /* 0x100 */ mDoExt_bckAnm bckAnm2;
    /* 0x11C */ mDoExt_bpkAnm bpkAnm2;
    /* 0x134 */ mDoExt_brkAnm brkAnm3;
    /* 0x14C */ mDoExt_btkAnm btkAnm2;
    /* 0x164 */ cXyz field_0x164;
    /* 0x170 */ u8 field_0x170;
    /* 0x171 */ u8 field_0x171;
    /* 0x172 */ u8 field_0x172;
    /* 0x173 */ u8 field_0x173;
    /* 0x174 */ u8 field_0x174;
    /* 0x175 */ u8 field_0x175;
};
static_assert(sizeof(dAttDraw_c) == 0x178);

class dAttDraw_CallBack_c : public mDoExt_McaMorfCallBack1_c {
public:
};
static_assert(sizeof(dAttDraw_CallBack_c) == 0x4);

// size is right but members are off, fix later
class dAttention_c {
public:
    /* 0x000 */ fopAc_ac_c* field_0x0;
    /* 0x004 */ u32 field_0x4;
    /* 0x008 */ dAttDraw_CallBack_c dattdraw_callback;
    /* 0x00C */ u32 field_0xc;
    /* 0x010 */ u32 field_0x10;
    /* 0x014 */ u8 field_0x14[4];
    /* 0x018 */ JKRSolidHeap* heap;
    /* 0x01C */ cXyz field_0x1c;
    /* 0x028 */ dAttDraw_c draw[2];
    /* 0x318 */ int field_0x318;
    /* 0x31C */ cXyz field_0x31c;
    /* 0x328 */ u8 field_0x328;
    /* 0x329 */ u8 field_0x329;
    /* 0x32A */ u8 field_0x32a;
    /* 0x32B */ u8 field_0x32b;
    /* 0x32C */ u8 field_0x32c;
    /* 0x32D */ u8 field_0x32d;
    /* 0x32E */ u8 field_0x32e;
    /* 0x32F */ u8 field_0x32f;
    /* 0x330 */ u8 field_0x330;
    /* 0x331 */ u8 field_0x331;
    /* 0x332 */ u8 field_0x332;
    /* 0x333 */ u8 field_0x333;
    /* 0x334 */ u32 mFlags;
    /* 0x338 */ dAttList_c mLockOnList[8];
    /* 0x3D8 */ int mLockonCount;
    /* 0x3DC */ int field_0x3dc;
    /* 0x3E0 */ dAttList_c mActionList[4];
    /* 0x430 */ int mActionCount;
    /* 0x434 */ int field_0x434;
    /* 0x438 */ dAttList_c attention_list3[4];
    /* 0x488 */ int mCheckObjectCount;
    /* 0x48C */ int field_0x48c;
    /* 0x490 */ dAttHint_c mZHintTarget;
    /* 0x49C */ dAttCatch_c mCatghTarget;
    /* 0x4B4 */ dAttLook_c mLookTarget;
    /* 0x4C4 */ int field_0x4c4;
    /* 0x4C8 */ u8 field_0x4c8;
    /* 0x4C9 */ u8 field_0x4c9;
    /* 0x4CA */ u8 field_0x4ca;
    /* 0x4CB */ u8 field_0x4cb;
    /* 0x4CC */ u8 field_0x4cc;
    /* 0x4CD */ u8 field_0x4cd;
    /* 0x4CE */ u8 field_0x4ce;
    /* 0x4CF */ u8 field_0x4cf;
    /* 0x4D0 */ dAttParam_c attention_param;
};  // Size = 0x51C
static_assert(sizeof(dAttention_c) == 0x51C);

#endif /* D_D_ATTENTION_H */
