#ifndef D_ITEM_H
#define D_ITEM_H

#include "../dolphin/types.h"

struct daItemBase_data {
    /* 0x00 */ f32 mGravity;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xc;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 field_0x1a;
    /* 0x1C */ s16 field_0x1c;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2a;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ s16 field_0x34;
    /* 0x36 */ s16 field_0x36;
};

#ifndef WII_PLATFORM
#define daItemBase__data m_data__12daItemBase_c
#else
#define daItemBase__data daItemBase_c__m_data
#endif

extern "C" daItemBase_data daItemBase__data;

#endif /* D_ITEM_H */
