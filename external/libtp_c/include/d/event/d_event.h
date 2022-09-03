#ifndef D_EVENT_D_EVENT_H
#define D_EVENT_D_EVENT_H

#include "../d_stage.h"
#include "../save/d_save.h"

class dEvt_order_c {
public:
    /*  0x00 */ uint16_t mEventType;
    /*  0x02 */ uint16_t mFlag;
    /*  0x04 */ int16_t field_0x04;
    /*  0x08 */ fopAc_ac_c* mActor1;
    /*  0x0C */ fopAc_ac_c* mActor2;
    /*  0x10 */ int16_t mEventId;
    /*  0x12 */ int16_t mPriority;
    /*  0x14 */ uint8_t mNextOrderIdx;
    /*  0x15 */ uint8_t mEventInfoIdx;
};  // Size = 0x18
static_assert(sizeof(dEvt_order_c) == 0x18);

typedef int (*SkipFunc)(void*, int);

class dEvt_control_c {
public:
    /* 0x000 */ uint8_t field_0x0[4];
    /* 0x004 */ dEvt_order_c mOrder[8];
    /* 0x0C4 */ uint32_t mPt1;
    /* 0x0C8 */ uint32_t mPt2;
    /* 0x0CC */ uint32_t mPtT;
    /* 0x0D0 */ uint32_t mPtI;
    /* 0x0D4 */ uint32_t mPtd;
    /* 0x0D8 */ uint16_t mEventFlag;
    /* 0x0DA */ uint16_t mFlag2;
    /* 0x0DC */ uint16_t mHindFlag;
    /* 0x0DE */ int16_t mSpecifiedEvent;  // name maybe wrong
    /* 0x0E0 */ int16_t field_0xe0;
    /* 0x0E2 */ uint8_t mNum;
    /* 0x0E3 */ uint8_t field_0xe3;
    /* 0x0E4 */ uint8_t mMode;
    /* 0x0E5 */ uint8_t mHalt;
    /* 0x0E6 */ uint8_t field_0xe6;
    /* 0x0E7 */ uint8_t field_0xe7;
    /* 0x0E8 */ uint8_t field_0xe8;
    /* 0x0E9 */ uint8_t mDebugStb;
    /* 0x0EA */ uint8_t field_0xea;
    /* 0x0EB */ uint8_t mMapToolId;
    /* 0x0EC */ uint8_t field_0xec;
    /* 0x0ED */ uint8_t field_0xed;
    /* 0x0EE */ uint8_t mPreItemNo;
    /* 0x0EF */ uint8_t mGtItm;
    /* 0x0F0 */ float mCullRate;
    /* 0x0F4 */ void* mStageEventDt;
    /* 0x0F8 */ void* mChangeOK;
    /* 0x0FC */ uint8_t field_0xfc[4];
    /* 0x100 */ SkipFunc mSkipFunc;
    /* 0x104 */ uint32_t field_0x104;
    /* 0x108 */ uint32_t field_0x108;
    /* 0x10C */ uint32_t field_0x10c;
    /* 0x110 */ int mSkipFade;
    /* 0x114 */ char mSkipEventName[20];
    /* 0x128 */ uint8_t mCompulsory;
    /* 0x129 */ bool field_0x129;
    /* 0x12C */ int field_0x12c;
#ifdef WII_PLATFORM
    /* 0x130 */ uint8_t field_0x130;
#endif
};

#ifdef GCN_PLATFORM
static_assert(sizeof(dEvt_control_c) == 0x130);
#endif

#endif /* D_EVENT_D_EVENT_H */
