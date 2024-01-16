#ifndef D_EVENT_D_EVENT_DATA_H
#define D_EVENT_D_EVENT_DATA_H

#include "../d_stage.h"
#include "../save/d_save.h"

struct dEvDtStaff_c {};

struct dEvDtEvent_c {};

struct dEvDtData_c {};

class dEvDtFlag_c {
public:
    u32 mFlags[320];
};  // Size = 0x500

struct event_binary_data_header {};

class dEvDtCut_c {};

class dEvDtBase_c {
public:
    /* 0x00 */ event_binary_data_header* mHeaderP;
    /* 0x04 */ dEvDtEvent_c* mEventP;
    /* 0x08 */ dEvDtStaff_c* mStaffP;
    /* 0x0C */ dEvDtCut_c* mCutP;
    /* 0x10 */ dEvDtData_c* mDataP;
    /* 0x14 */ f32* mFDataP;
    /* 0x18 */ s32* mIDataP;
    /* 0x1C */ char* mSDataP;
    /* 0x20 */ s32 mRoomNo;
};  // Size = 0x24

#endif /* D_EVENT_D_EVENT_DATA_H */
