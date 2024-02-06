#ifndef D_EVENT_D_EVENT_MANAGER_H
#define D_EVENT_D_EVENT_MANAGER_H

#include "d_event_data.h"

class dEvent_exception_c {
public:
    u32 mEventInfoIdx;
    u8 field_0x4;
    u8 field_0x5;
    u8 field_0x6;
    u8 field_0x7;
    u32 mState;
};
static_assert(sizeof(dEvent_exception_c) == 0xC);

class dEvent_manager_c {
public:
    /* 0x0000 */ dEvDtBase_c mEventList[11];
    /* 0x018C */ s32 mCameraPlay;
    /* 0x0190 */ dEvent_exception_c mEventException;
    /* 0x019C */ cXyz mGoal;
    /* 0x01A8 */ u8 field_0x1a8[2];
    /* 0x01AA */ u16 field_0x1aa;
    /* 0x01AC */ u8 field_0x1ac[4];
    /* 0x01B0 */ u32 field_0x1b0;
    /* 0x01B4 */ u32 field_0x1b4;
    /* 0x01B8 */ u32 field_0x1b8;
    /* 0x01BC */ dEvDtFlag_c mFlags;
    /* 0x06BC */ bool mDataLoaded;
};
static_assert(sizeof(dEvent_manager_c) == 0x6C0);

#endif /* D_EVENT_D_EVENT_MANAGER_H */
