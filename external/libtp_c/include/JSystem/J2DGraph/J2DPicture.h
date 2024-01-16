#ifndef J2DPICTURE_H_
#define J2DPICTURE_H_

#include "J2DPane.h"
#include "../JKernel/JKRArchive.h"
#include "../JUtility/JUTTexture.h"
#include "../JUtility.h"

class JUTPalette;
class JUTTexture;

class J2DPicture : public J2DPane {
public:
    /* 0x100 */ JUTTexture* mTexture[2];
    /* 0x108 */ u8 mTextureCount;
    /* 0x109 */ u8 field_0x109;
    /* 0x10A */ JGeometry::TVec2<short> field_0x10a[4];
    /* 0x11C */ f32 field_0x11c[4];
    /* 0x12C */ JUTPalette* field_0x12c;
    /* 0x130 */ JUtility::TColor mWhite;
    /* 0x134 */ JUtility::TColor mBlack;
    /* 0x138 */ JUtility::TColor mCornerColor[4];
    /* 0x148 */ JUtility::TColor field_0x148;
    /* 0x14C */ JUtility::TColor field_0x14c;
};

typedef void (*J2DPicture__J2DPicture4_t)(void* addr, const ResTIMG* img);
#define J2DPicture__J2DPicture4 ((J2DPicture__J2DPicture4_t)J2DPicture__J2DPicture4_addr)

typedef void (*J2DPicture__draw_t)(void* addr, f32 xpos, f32 ypos, f32 width, f32 height,
                                   bool mirrorX, bool mirrorY, bool tumble);
#define J2DPicture__draw ((J2DPicture__draw_t)J2DPicture__draw_addr)

#endif