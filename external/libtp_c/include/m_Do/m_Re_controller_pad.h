#ifndef M_RE_CONTROLLER_PAD_H
#define M_RE_CONTROLLER_PAD_H

#include "../dolphin/mtx/vec.h"
#include "../dolphin/mtx/mtx.h"
#include "../dolphin/types.h"

#ifdef WII_PLATFORM
namespace CButton {
enum : uint16_t {
    DPAD_LEFT = 0x1,
    DPAD_RIGHT = 0x2,
    DPAD_DOWN = 0x4,
    DPAD_UP = 0x8,
    PLUS = 0x10,
    TWO = 0x100,
    ONE = 0x200,
    B = 0x400,
    A = 0x800,
    MINUS = 0x1000,
    Z = 0x2000,
    C = 0x4000,
    HOME = 0x8000,
};
}
#endif

struct Pointer {
    Vec2 pos;           // 8044BB84
    u8 _p1[0x20];  // 8044BB8C
    f32 scr_dist;     // 8044BBAC // Relative distance of the remote to the sensor bar
};
static_assert(sizeof(Pointer) == 0x2C);

class mReCPd {
public:
    struct Pad {
        struct Acc {
            /* 0x000 */ Vec field_0x0[120];
            /* 0x5A0 */ Vec field_0x5a0[120];
            /* 0xB40 */ u32 field_0xb40;
            /* 0xB44 */ u32 field_0xb44;
            /* 0xB48 */ f32 field_0xb48;
            /* 0xB4C */ f32 field_0xb4c;
            /* 0xB50 */ u8 field_0xb50;
            /* 0xB51 */ u8 field_0xb51;
            /* 0xB54 */ f32 field_0xb54;
            /* 0xB58 */ Vec field_0xb58;
            /* 0xB64 */ int field_0xb64;
            /* 0xB68 */ Mtx field_0xb68;
            /* 0xB98 */ f32 field_0xb98;
            /* 0xB9C */ int field_0xb9c;
            /* 0xBA0 */ f32 field_0xba0;
            /* 0xBA4 */ f32 field_0xba4;
            /* 0xBA8 */ u8 field_0xba8[4];
            /* 0xBAC */ int field_0xbac;
            /* 0xBB0 */ f32 field_0xbb0;
            /* 0xBB4 */ f32 field_0xbb4;
            /* 0xBB8 */ u8 field_0xbb8[4];
            /* 0xBBC */ int field_0xbbc;
            /* 0xBC0 */ int field_0xbc0;
        };  // Size: 0xBC4

        /* 0x0000 */ int field_0x0;
        /* 0x0004 */ u32 mHoldButton;
        /* 0x0008 */ u32 mTrigButton;
        /* 0x000C */ u32 mReleaseButton;
        /* 0x0010 */ Vec wiimote_acc;             // 8044BB70
        /* 0x001C */ f32 wiimote_acc_strength;  // 8044BB7C
        /* 0x0020 */ f32 wiimote_shake;  // 8044BB80 // Unsure of the real meaning of this, needs
                                           // more verification
        /* 0x0024 */ Pointer pointer;      // 8044BB84
        /* 0x0050 */ u8 _p4[8];       // 8044BBB0
        /* 0x0058 */ f32 horizontal;     // 8044BBB8 // Goes from 0.0 to 1.0, shows how much the
                                           // remote is horizontal
        /* 0x005C */ f32 vertical;       // 8044BBBC // Goes from -1.0 to 1.0, shows how much the
                                           // remote is vertical (up is 1.0, down is -1.0)
        /* 0x0060 */ u8 _p5[4];       // 8044BBC0
        /* 0x0064 */ Vec2 stick;           // 8044BBC4
        /* 0x006C */ Vec nunchuck_acc;     // 8044BBCC
        /* 0x0078 */ f32 nunchuck_acc_strength;  // 8044BBD8
        /* 0x007C */ f32 nunchuck_shake;  // 8044BBDC // Unsure of the real meaning of this, needs
                                            // more verification
        /* 0x0080 */ u8 field_0x80[0x554 - 0x80];
        /* 0x0554 */ int field_0x554;
        /* 0x0558 */ u8 field_0x558[0x5e0 - 0x558];
        /* 0x05E0 */ Acc field_0x5e0;
        /* 0x11A4 */ Acc field_0x11a4;
        /* 0x1D68 */ f32 field_0x1d68;
        /* 0x1D6C */ f32 field_0x1d6c;
        /* 0x1D70 */ f32 mStickAmplitude;
        /* 0x1D74 */ u16 field_0x1d74;
        /* 0x1D76 */ s16 mFSStickAngle3D;
        /* 0x1D78 */ f32 field_0x1d78;
        /* 0x1D7C */ f32 field_0x1d7c;
        /* 0x1D80 */ f32 field_0x1d80;
        /* 0x1D84 */ f32 field_0x1d84;
        /* 0x1D88 */ f32 field_0x1d88;
        /* 0x1D8C */ f32 field_0x1d8c;
        /* 0x1D90 */ f32 field_0x1d90;
        /* 0x1D94 */ f32 field_0x1d94;
        /* 0x1D98 */ f32 field_0x1d98;
        /* 0x1D9C */ f32 field_0x1d9c;
        /* 0x1DA0 */ f32 field_0x1da0;
        /* 0x1DA4 */ f32 field_0x1da4;
        /* 0x1DA8 */ f32 field_0x1da8;
        /* 0x1DAC */ f32 field_0x1dac;
        /* 0x1DB0 */ f32 field_0x1db0;
        /* 0x1DB4 */ f32 field_0x1db4;
        /* 0x1DB8 */ f32 field_0x1db8;
        /* 0x1DBC */ f32 field_0x1dbc;
        /* 0x1DC0 */ f32 field_0x1dc0;
        /* 0x1DC4 */ int field_0x1dc4;
        /* 0x1DC8 */ int field_0x1dc8;
        /* 0x1DCC */ int field_0x1dcc;
        /* 0x1DD0 */ int field_0x1dd0;
        /* 0x1DD4 */ u8 field_0x1dd4;
        /* 0x1DD8 */ int field_0x1dd8;
        /* 0x1DDC */ u8 field_0x1ddc;
        /* 0x1DDD */ u8 field_0x1ddd;
        /* 0x1DE0 */ int field_0x1de0;
        /* 0x1DE4 */ int field_0x1de4;
        /* 0x1DE8 */ u8 field_0x1de8;
        /* 0x1DEC */ int field_0x1dec;
        /* 0x1DF0 */ u8 field_0x1df0;
        /* 0x1DF4 */ int field_0x1df4;
        /* 0x1DF8 */ int field_0x1df8;
        /* 0x1DFC */ int field_0x1dfc;
        /* 0x1E00 */ int field_0x1e00;
        /* 0x1E04 */ u8 field_0x1e04;
        /* 0x1E05 */ u8 field_0x1e05;
    };  // Size: 0x1E08
};

#ifdef WII_PLATFORM
#define mPad mReCPd__m_pad
extern mReCPd::Pad mPad;
#endif

#endif /* M_RE_CONTROLLER_PAD_H */