#include "../include/JSystem/JUtility/JUTGamePad.h"
#include "../include/controller.h"
#include "../include/m_Do/m_Re_controller_pad.h"

#ifdef GCN_PLATFORM
#define mPad_ (mPadButton)
#endif
#ifdef WII_PLATFORM
#define mPad_ (mPad)
#endif

void setGamepadButtons(uint16_t buttons) {
#ifdef GCN_PLATFORM
    mPad_.mButton = buttons;
#endif

#ifdef WII_PLATFORM
    mPad.mHoldButton = buttons;
#endif
}

void setGamepadTrig(uint16_t buttons) {
#ifdef GCN_PLATFORM
    mPad_.mTrigger = buttons;
#endif

#ifdef WII_PLATFORM
    mPad.mTrigButton = buttons;
#endif
}