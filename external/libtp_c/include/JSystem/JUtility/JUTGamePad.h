#ifndef JUTGAMEPAD_H
#define JUTGAMEPAD_H

#include "../../dolphin/types.h"
#include "../../dolphin/mtx/vec.h"
#include "../../dolphin/pad/pad.h"
#include "../../defines.h"
#include "../JKernel/JKRDisposer.h"
#include "../../SSystem/SComponent/c_API_controller_pad.h"

typedef void (*callbackFn)(int, void*);

#ifdef GCN_PLATFORM
namespace CButton {
enum : uint16_t {
    DPAD_LEFT = 0x0001,
    DPAD_RIGHT = 0x0002,
    DPAD_DOWN = 0x0004,
    DPAD_UP = 0x0008,
    Z = 0x0010,
    R = 0x0020,
    L = 0x0040,
    A = 0x0100,
    B = 0x0200,
    X = 0x0400,
    Y = 0x0800,
    START = 0x1000,
};
}
#endif

struct JUTGamePad : public JKRDisposer {
public:
    enum EStickMode {};
    enum EWhichStick {};
    enum EPadPort {
        Port_Unknown = -1,  // used by JUTException
        Port_1,
        Port_2,
        Port_3,
        Port_4,
    };

    u32 getButton() const { return mButton.mButton; }

    u32 getTrigger() const { return mButton.mTrigger; }

    f32 getMainStickX() const { return mMainStick.mPosX; }

    f32 getMainStickY() const { return mMainStick.mPosY; }

    f32 getMainStickValue() const { return mMainStick.mValue; }

    s16 getMainStickAngle() const { return mMainStick.mAngle; }

    f32 getSubStickX() const { return mSubStick.mPosX; }

    f32 getSubStickY() const { return mSubStick.mPosY; }

    f32 getSubStickValue() const { return mSubStick.mValue; }

    s16 getSubStickAngle() const { return mSubStick.mAngle; }

    u8 getAnalogA() const { return mButton.mAnalogA; }

    u8 getAnalogB() const { return mButton.mAnalogB; }

    u8 getAnalogL() const { return mButton.mAnalogL; }

    u8 getAnalogR() const { return mButton.mAnalogR; }

    s8 getErrorStatus() const { return mErrorStatus; }

    u32 testTrigger(u32 button) const { return mButton.mTrigger & button; }

    bool isPushing3ButtonReset() const {
        bool isPushingReset = false;

        if (mPortNum != -1 && mButtonReset.mReset != false) {
            isPushingReset = true;
        }
        return isPushingReset;
    }

    struct CButton {
        /* 0x00 */ u32 mButton;
        /* 0x04 */ u32 mTrigger;  // Pressed Buttons
        /* 0x08 */ u32 mRelease;  // Released Buttons
        /* 0x0C */ u8 mAnalogA;
        /* 0x0D */ u8 mAnalogB;
        /* 0x0E */ u8 mAnalogL;
        /* 0x0F */ u8 mAnalogR;
        /* 0x10 */ f32 mAnalogLf;
        /* 0x14 */ f32 mAnalogRf;
        /* 0x18 */ u32 mRepeat;
        /* 0x1C */ u32 field_0x1c;
        /* 0x20 */ u32 field_0x20;
        /* 0x24 */ u32 field_0x24;
        /* 0x28 */ u32 field_0x28;
        /* 0x2C */ u32 field_0x2c;
    };  // Size: 0x30

    struct C3ButtonReset {
        /* 0x0 */ bool mReset;
    };  // Size: 0x4

    struct CStick {
        /* 0x0 */ f32 mPosX;
        /* 0x4 */ f32 mPosY;
        /* 0x8 */ f32 mValue;
        /* 0xC */ s16 mAngle;
        /* 0xE */ s8 field_0xe;
        /* 0xF */ s8 field_0xf;
    };  // Size: 0x10

    struct CRumble {
        enum ERumble {
            VAL_0 = 0,
            VAL_1 = 1,
            VAL_2 = 2,
        };

        /* 0x00 */ u32 field_0x0;
        /* 0x04 */ u32 field_0x4;
        /* 0x08 */ u8* field_0x8;
        /* 0x0C */ u32 field_0xc;
        /* 0x10 */ u8* field_0x10;
    };  // Size: 0x14

    /* 0x18 */ CButton mButton;
    /* 0x48 */ CStick mMainStick;
    /* 0x58 */ CStick mSubStick;
    /* 0x68 */ CRumble mRumble;
    /* 0x7C */ s16 mPortNum;
    /* 0x7E */ s8 mErrorStatus;
    /* 0x80 */ JSULink<JUTGamePad> mLink;
    /* 0x90 */ u32 mPadRecord;
    /* 0x94 */ u32 mPadReplay;
    /* 0x98 */ C3ButtonReset mButtonReset;
    /* 0x9C */ u8 field_0x9c[4];
    /* 0xA0 */ int64_t mResetTime;
    /* 0xA8 */ u8 field_0xa8;
};

#ifdef WII_PLATFORM
#define mPadStatus JUTGamePad__mPadStatus
#define mPadButton JUTGamePad__mPadButton
#define mPadMStick JUTGamePad__mPadMStick
#define mPadSStick JUTGamePad__mPadSStick
#define cPadInfo mDoCPd_c__m_cpadInfo
#else
#define mPadStatus mPadStatus__10JUTGamePad
#define mPadButton mPadButton__10JUTGamePad
#define mPadMStick mPadMStick__10JUTGamePad
#define mPadSStick mPadSStick__10JUTGamePad
#define cPadInfo m_cpadInfo__8mDoCPd_c
#endif
extern PADStatus mPadStatus;
extern JUTGamePad::CButton mPadButton;
extern JUTGamePad::CStick mPadMStick;
extern JUTGamePad::CStick mPadSStick;
extern interface_of_controller_pad cPadInfo[4];

LIBTP_DEFINE_FUNC(read__10JUTGamePadFv, JUTGamePad__read_void_,
                  void, JUTGamePadRead, (void))

#endif /* JUTGAMEPAD_H */
