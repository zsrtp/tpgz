#ifndef Z2STATUSMGR_H
#define Z2STATUSMGR_H

#include "../dolphin/mtx/vec.h"
#include <stdint.h>

struct Z2StatusMgr {
    void setHour(int32_t hour) { mHour = hour; }
    void setMinute(int32_t min) { mMinute = min; }
    void setWeekday(int32_t day) { mWeekday = day; }

    /* 0x00 */ uint8_t mHour;
    /* 0x01 */ uint8_t mMinute;
    /* 0x02 */ uint8_t mWeekday;
    /* 0x03 */ uint8_t field_0x03;
    /* 0x04 */ int16_t mTime;
    /* 0x08 */ void* mEventBit;
    /* 0x0C */ bool mIsMenuIn;
    /* 0x10 */ uint32_t mCameraMapInfo;
    /* 0x14 */ uint32_t field_0x14;
    /* 0x18 */ float mUnderwaterDepth;
    /* 0x1C */ float mCameraInWaterDepthRatio;
    /* 0x20 */ Vec mPolygonPosition;
    /* 0x2C */ uint8_t mDemoStatus;
    /* 0x2D */ uint8_t mHeartGaugeOn;
};  // Size = 0x30

#endif /* Z2STATUSMGR_H */