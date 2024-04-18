#ifndef D_MENU_D_MENU_WINDOW_H
#define D_MENU_D_MENU_WINDOW_H

#include "../../addrs.h"
#include "../../defines.h"

class msg_class : public leafdraw_class {
public:
    /* 0xC0 */ int mMsgType;
    /* 0xC4 */ create_tag_class draw_tag;
    /* 0xD8 */ leafdraw_method_class* sub_method;
    /* 0xDC */ fopAc_ac_c* mpActor;
    /* 0xE0 */ cXyz mPos;
    /* 0xEC */ u32 mMsgID;
    /* 0xF0 */ u32 field_0xf0;
    /* 0xF4 */ u32 field_0xf4;
    /* 0xF8 */ u16 mMode;
    /* 0xFA */ u8 mSelectedChoiceIdx;
};  // Size: 0xFC


class dMw_c : public msg_class {
public:
    enum dMw_Status {
        /* 0x00 */ NO_MENU,
        /* 0x01 */ RING_OPEN,
        /* 0x02 */ RING_MOVE,
        /* 0x03 */ RING_CLOSE,
        /* 0x04 */ COLLECT_OPEN,
        /* 0x05 */ COLLECT_MOVE,
        /* 0x06 */ COLLECT_CLOSE,
        /* 0x07 */ FMAP_OPEN,
        /* 0x08 */ FMAP_MOVE,
        /* 0x09 */ FMAP_CLOSE,
        /* 0x0A */ DMAP_OPEN,
        /* 0x0B */ DMAP_MOVE,
        /* 0x0C */ DMAP_CLOSE,
        /* 0x0D */ SAVE_OPEN,
        /* 0x0E */ SAVE_MOVE,
        /* 0x0F */ SAVE_CLOSE,
        /* 0x10 */ OPTIONS_OPEN,
        /* 0x11 */ OPTIONS_MOVE,
        /* 0x12 */ OPTIONS_CLOSE,
        /* 0x13 */ LETTER_OPEN,
        /* 0x14 */ LETTER_MOVE,
        /* 0x15 */ LETTER_CLOSE,
        /* 0x16 */ FISHING_OPEN,
        /* 0x17 */ FISHING_MOVE,
        /* 0x18 */ FISHING_CLOSE,
        /* 0x19 */ SKILL_OPEN,
        /* 0x1A */ SKILL_MOVE,
        /* 0x1B */ SKILL_CLOSE,
        /* 0x1C */ INSECT_OPEN,
        /* 0x1D */ INSECT_MOVE,
        /* 0x1E */ INSECT_CLOSE,
        /* 0x1F */ INSECT_AGITHA_OPEN1,
        /* 0x20 */ INSECT_AGITHA_OPEN2,
        /* 0x21 */ INSECT_AGITHA_MOVE,
        /* 0x22 */ INSECT_AGITHA_CLOSE,
    };

    /* 801FA13C */ void key_wait_init(u8);

private:
    /* 0x0FC */ int field_0xfc;
    /* 0x100 */ JKRExpHeap* mpHeap;
    /* 0x104 */ u8 field_0x104[0x110 - 0x104];
    /* 0x110 */ void* mpMenuRing;
    /* 0x114 */ u8 field_0x114[0x138 - 0x114];
    /* 0x138 */ s32 mMemSize;
    /* 0x13C */ f32 field_0x13c;
    /* 0x140 */ f32 field_0x140;
    /* 0x144 */ u8 field_0x144;
    /* 0x145 */ u8 mButtons;
    /* 0x146 */ u8 mMenuStatus;
    /* 0x147 */ u8 mShowFlag;
    /* 0x148 */ s8 field_0x148;
    /* 0x149 */ u8 field_0x149;
    /* 0x14A */ u8 field_0x14A;
    /* 0x14B */ u8 field_0x14B;
    /* 0x14C */ u8 field_0x14C;
    /* 0x14D */ u8 field_0x14D;
    /* 0x14E */ u8 field_0x14E;
    /* 0x14F */ u8 field_0x14F;
    /* 0x150 */ u8 field_0x150;
    /* 0x151 */ u8 field_0x151;
    /* 0x152 */ u8 field_0x152;
    /* 0x153 */ u8 field_0x153;
    /* 0x154 */ bool mPauseWindow;
};

LIBTP_DEFINE_FUNC(fopMsgM_SearchByID__FUi, fopMsgM_SearchByID_unsigned_int_,
                    msg_class*, fopMsgM_SearchByID, (u32 id))

#endif /* D_MENU_D_MENU_WINDOW_H */
