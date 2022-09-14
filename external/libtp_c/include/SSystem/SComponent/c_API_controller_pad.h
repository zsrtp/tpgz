#ifndef C_API_CONTROLLER_PAD_
#define C_API_CONTROLLER_PAD_

#include <stdint.h>

struct interface_of_controller_pad {
    /* 0x00 */ float mMainStickPosX;
    /* 0x04 */ float mMainStickPosY;
    /* 0x08 */ float mMainStickValue;
    /* 0x0C */ int16_t mMainStickAngle;
    /* 0x0E */ uint8_t field_0xe;
    /* 0x0F */ uint8_t field_0xf;
    /* 0x10 */ float mCStickPosX;
    /* 0x14 */ float mCStickPosY;
    /* 0x18 */ float mCStickValue;
    /* 0x1C */ int16_t mCStickAngle;
    /* 0x1E */ uint8_t field_0x1e;
    /* 0x1F */ uint8_t field_0x1f;
    /* 0x20 */ float mAnalogA;
    /* 0x24 */ float mAnalogB;
    /* 0x28 */ float mTriggerLeft;
    /* 0x2C */ float mTriggerRight;
    /* 0x30 */ uint32_t mButtonFlags;
    /* 0x34 */ uint32_t mPressedButtonFlags;
    /* 0x38 */ int8_t mGamepadErrorFlags;
    /* 0x39 */ uint8_t mHoldLockL;
    /* 0x3A */ uint8_t mTrigLockL;
    /* 0x3B */ uint8_t mHoldLockR;
    /* 0x3C */ uint8_t mTrigLockR;
    /* 0x3D */ uint8_t field_0x3d;
    /* 0x3E */ uint8_t field_0x3e;
    /* 0x3F */ uint8_t field_0x3f;
};

#endif /* C_API_CONTROLLER_PAD_ */
