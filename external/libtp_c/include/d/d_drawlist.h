#ifndef D_D_DRAWLIST_H
#define D_D_DRAWLIST_H

#include "../dolphin/types.h"
#include "../JSystem/J3DGraphBase/J3DPacket.h"

class dDlst_peekZ_c {
public:
    /* 0x0 */ u8 field_0x0;
    /* 0x2 */ u16 field_0x2;
    /* 0x4 */ u32* field_0x4;
};

class dDlst_window_c {
public:
    /* 0x00 */ f32 mViewport;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 mScissor;
    /* 0x1C */ f32 field_0x1c;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ s8 mCameraID;
    /* 0x29 */ s8 mMode;
};

class dDlst_base_c {
public:
    void* vtable;
};

class dDlst_list_c {
public:
    /* 0x00000 */ u8 field_0x00[0x1C];
    /* 0x0001C */ J3DPacket* mpPacket;
    /* 0x00020 */ u8 field_0x20[0x16170];
    /* 0x16180 */ dDlst_peekZ_c dlstPeekZ;
    /* 0x16184 */ u8 unk_0x16194[0x1F];
};  // Size: 0x161A0

#endif /* D_D_DRAWLIST_H */
