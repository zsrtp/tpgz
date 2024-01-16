#ifndef D_EVENT_D_EVENT_H
#define D_EVENT_D_EVENT_H

#include "../d_stage.h"
#include "../save/d_save.h"

class dEvt_order_c {
public:
    /*  0x00 */ u16 mEventType;
    /*  0x02 */ u16 mFlag;
    /*  0x04 */ s16 field_0x04;
    /*  0x08 */ fopAc_ac_c* mActor1;
    /*  0x0C */ fopAc_ac_c* mActor2;
    /*  0x10 */ s16 mEventId;
    /*  0x12 */ s16 mPriority;
    /*  0x14 */ u8 mNextOrderIdx;
    /*  0x15 */ u8 mEventInfoIdx;
};  // Size = 0x18
static_assert(sizeof(dEvt_order_c) == 0x18);

typedef int (*SkipFunc)(void*, int);

class dEvt_control_c {
public:
    /* 0x000 */ u8 field_0x0[4];
    /* 0x004 */ dEvt_order_c mOrder[8];
    /* 0x0C4 */ u32 mPt1;
    /* 0x0C8 */ u32 mPt2;
    /* 0x0CC */ u32 mPtT;
    /* 0x0D0 */ u32 mPtI;
    /* 0x0D4 */ u32 mPtd;
    /* 0x0D8 */ u16 mEventFlag;
    /* 0x0DA */ u16 mFlag2;
    /* 0x0DC */ u16 mHindFlag;
    /* 0x0DE */ s16 mSpecifiedEvent;  // name maybe wrong
    /* 0x0E0 */ s16 field_0xe0;
    /* 0x0E2 */ u8 mNum;
    /* 0x0E3 */ u8 field_0xe3;
    /* 0x0E4 */ u8 mMode;
    /* 0x0E5 */ u8 mHalt;
    /* 0x0E6 */ u8 field_0xe6;
    /* 0x0E7 */ u8 field_0xe7;
    /* 0x0E8 */ u8 field_0xe8;
    /* 0x0E9 */ u8 mDebugStb;
    /* 0x0EA */ u8 field_0xea;
    /* 0x0EB */ u8 mMapToolId;
    /* 0x0EC */ u8 field_0xec;
    /* 0x0ED */ u8 field_0xed;
    /* 0x0EE */ u8 mPreItemNo;
    /* 0x0EF */ u8 mGtItm;
    /* 0x0F0 */ f32 mCullRate;
    /* 0x0F4 */ void* mStageEventDt;
    /* 0x0F8 */ void* mChangeOK;
    /* 0x0FC */ u8 field_0xfc[4];
    /* 0x100 */ SkipFunc mSkipFunc;
    /* 0x104 */ u32 field_0x104;
    /* 0x108 */ u32 field_0x108;
    /* 0x10C */ u32 field_0x10c;
    /* 0x110 */ int mSkipFade;
    /* 0x114 */ char mSkipEventName[20];
    /* 0x128 */ u8 mCompulsory;
    /* 0x129 */ bool field_0x129;
    /* 0x12C */ int field_0x12c;
#ifdef WII_PLATFORM
    /* 0x130 */ u8 field_0x130;
#endif
};

#ifdef GCN_PLATFORM
static_assert(sizeof(dEvt_control_c) == 0x130);
#endif

#endif /* D_EVENT_D_EVENT_H */
