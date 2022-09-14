#ifndef M_DO_M_DO_CONTROLLER_PAD_H
#define M_DO_M_DO_CONTROLLER_PAD_H

#include "../JSystem/JUtility/JUTGamePad.h"
#include "../addrs.h"

#define mDoCPd_c__m_gamePad ((JUTGamePad**)mDoCPd_c__m_gamePad_addr)

class mDoCPd_c {
public:
    // Controller Ports 1 - 4
    enum { PAD_0, PAD_1, PAD_2, PAD_3 };

    static interface_of_controller_pad& getCpadInfo(uint32_t pad) { return cPadInfo[pad]; }
    static JUTGamePad* getGamePad(uint32_t pad) { return mDoCPd_c__m_gamePad[pad]; }
    static uint32_t getTrig(uint32_t pad) { return getCpadInfo(pad).mPressedButtonFlags; }
    static uint32_t getTrigLockL(uint32_t pad) { return getCpadInfo(pad).mTrigLockL; }
    static uint32_t getTrigLockR(uint32_t pad) { return getCpadInfo(pad).mTrigLockR; }
    static uint32_t getTrigUp(uint32_t pad) { return getTrig(pad) & CButton::DPAD_UP; }
    static uint32_t getTrigDown(uint32_t pad) { return getTrig(pad) & CButton::DPAD_DOWN; }
    static uint32_t getTrigLeft(uint32_t pad) { return getTrig(pad) & CButton::DPAD_LEFT; }
    static uint32_t getTrigRight(uint32_t pad) { return getTrig(pad) & CButton::DPAD_RIGHT; }
    static uint32_t getTrigL(uint32_t pad) { return getTrig(pad) & CButton::L; }
    static uint32_t getTrigR(uint32_t pad) { return getTrig(pad) & CButton::R; }
    static uint32_t getTrigA(uint32_t pad) { return getTrig(pad) & CButton::A; }
    static uint32_t getTrigB(uint32_t pad) { return getTrig(pad) & CButton::B; }
    static uint32_t getTrigZ(uint32_t pad) { return getTrig(pad) & CButton::Z; }
    static uint32_t getTrigY(uint32_t pad) { return getTrig(pad) & CButton::Y; }
    static uint32_t getTrigX(uint32_t pad) { return getTrig(pad) & CButton::X; }
    static uint32_t getTrigStart(uint32_t pad) { return getTrig(pad) & CButton::START; }
    static uint32_t getHold(uint32_t pad) { return getCpadInfo(pad).mButtonFlags; }
    static uint32_t getHoldLockL(uint32_t pad) { return getCpadInfo(pad).mHoldLockL; }
    static uint32_t getHoldLockR(uint32_t pad) { return getCpadInfo(pad).mHoldLockR; }
    static uint32_t getHoldUp(uint32_t pad) { return getHold(pad) & CButton::DPAD_UP; }
    static uint32_t getHoldDown(uint32_t pad) { return getHold(pad) & CButton::DPAD_DOWN; }
    static uint32_t getHoldLeft(uint32_t pad) { return getHold(pad) & CButton::DPAD_LEFT; }
    static uint32_t getHoldRight(uint32_t pad) { return getHold(pad) & CButton::DPAD_RIGHT; }
    static uint32_t getHoldL(uint32_t pad) { return getHold(pad) & CButton::L; }
    static uint32_t getHoldR(uint32_t pad) { return getHold(pad) & CButton::R; }
    static uint32_t getHoldA(uint32_t pad) { return getHold(pad) & CButton::A; }
    static uint32_t getHoldB(uint32_t pad) { return getHold(pad) & CButton::B; }
    static uint32_t getHoldZ(uint32_t pad) { return getHold(pad) & CButton::Z; }
    static uint32_t getHoldY(uint32_t pad) { return getHold(pad) & CButton::Y; }
    static uint32_t getHoldX(uint32_t pad) { return getHold(pad) & CButton::X; }
    static float getStickX(uint32_t pad) { return getCpadInfo(pad).mMainStickPosX; }
    static float getStickY(uint32_t pad) { return getCpadInfo(pad).mMainStickPosY; }
    static float getStickValue(uint32_t pad) { return getCpadInfo(pad).mMainStickValue; }
    static int16_t getStickAngle(uint32_t pad) { return getCpadInfo(pad).mMainStickAngle; }
    static float getSubStickX(uint32_t pad) { return getCpadInfo(pad).mCStickPosX; }
    static float getSubStickY(uint32_t pad) { return getCpadInfo(pad).mCStickPosY; }
    static float getSubStickValue(uint32_t pad) { return getCpadInfo(pad).mCStickValue; }
    static int16_t getSubStickAngle(uint32_t pad) { return getCpadInfo(pad).mCStickAngle; }
    static float getAnalogR(uint32_t pad) { return getCpadInfo(pad).mTriggerRight; }
    static float getAnalogL(uint32_t pad) { return getCpadInfo(pad).mTriggerLeft; }
    // static int isConnect(uint32_t pad) { return JUTGamePad::getPortStatus(pad) == 0; }
    // static void stopMotorWaveHard(uint32_t pad) { return
    // mDoCPd_c__m_gamePad[pad]->stopMotorWaveHard(); }
};

inline void mDoCPd_ANALOG_CONV(uint8_t analog, float& param_1) {
    param_1 = analog * (1.0f / 15.0f);
    if (param_1 > 1.0f) {
        param_1 = 1.0f;
    }
}

inline void mDoCPd_TRIGGER_CONV(uint8_t analog, float& param_1) {
    param_1 = analog * 0.0071428571827709675f;
    if (param_1 > 1.0f) {
        param_1 = 1.0f;
    }
}

#endif /* M_DO_M_DO_CONTROLLER_PAD_H */