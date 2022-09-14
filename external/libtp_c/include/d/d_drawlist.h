#ifndef D_D_DRAWLIST_H
#define D_D_DRAWLIST_H

#include <stdint.h>
#include "../JSystem/J3DGraphBase/J3DPacket.h"

class dDlst_peekZ_c {
public:
    /* 0x0 */ uint8_t field_0x0;
    /* 0x2 */ uint16_t field_0x2;
    /* 0x4 */ uint32_t* field_0x4;
};

class dDlst_window_c {
public:
    /* 0x00 */ float mViewport;
    /* 0x04 */ float field_0x04;
    /* 0x08 */ float field_0x08;
    /* 0x0C */ float field_0x0C;
    /* 0x10 */ float field_0x10;
    /* 0x14 */ float field_0x14;
    /* 0x18 */ float mScissor;
    /* 0x1C */ float field_0x1c;
    /* 0x20 */ float field_0x20;
    /* 0x24 */ float field_0x24;
    /* 0x28 */ int8_t mCameraID;
    /* 0x29 */ int8_t mMode;
};

class dDlst_base_c {
public:
    void* vtable;
};

class dDlst_list_c {
public:
    /* 0x00000 */ uint8_t field_0x00[0x1C];
    /* 0x0001C */ J3DPacket* mpPacket;
    /* 0x00020 */ uint8_t field_0x20[0x16170];
    /* 0x16180 */ dDlst_peekZ_c dlstPeekZ;
    /* 0x16184 */ uint8_t unk_0x16194[0x1F];
};  // Size: 0x161A0

#endif /* D_D_DRAWLIST_H */
