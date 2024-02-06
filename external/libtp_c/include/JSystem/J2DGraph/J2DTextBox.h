#ifndef J2DTEXTBOX_H
#define J2DTEXTBOX_H

// #include "J2DMaterial.h"
#include "J2DPane.h"
#include "../JUtility.h"

enum J2DTextBoxVBinding {
    /* 0x0 */ VBIND_CENTER,
    /* 0x1 */ VBIND_BOTTOM,
    /* 0x2 */ VBIND_TOP
};

enum J2DTextBoxHBinding {
    /* 0x0 */ HBIND_CENTER,
    /* 0x1 */ HBIND_RIGHT,
    /* 0x2 */ HBIND_LEFT
};

class JUTFont;
class J2DTextBox;

typedef JUTFont* (*mDoExt_getMesgFont_t)(void);
#define mDoExt_getMesgFont ((mDoExt_getMesgFont_t)mDoExt_getMesgFont_addr)

typedef void (*J2DTextBox__J2DTextBox1_t)(J2DTextBox* thisx);
#define J2DTextBox__J2DTextBox1 ((J2DTextBox__J2DTextBox1_t)J2DTextBox__J2DTextBox1_addr)

typedef void (*J2DTextBox__setFont_t)(J2DTextBox* thisx, JUTFont* font);
#define J2DTextBox__setFont ((J2DTextBox__setFont_t)J2DTextBox__setFont_addr)

typedef void (*J2DTextBox__setString_t)(J2DTextBox* thisx, const char* str, ...);
#define J2DTextBox__setString ((J2DTextBox__setString_t)J2DTextBox__setString_addr)

typedef void (*J2DTextBox__draw2_t)(J2DTextBox* thisx, f32 x, f32 y, f32 size,
                                    J2DTextBoxHBinding binding);
#define J2DTextBox__draw2 ((J2DTextBox__draw2_t)J2DTextBox__draw2_addr)

class J2DTextBox : public J2DPane {
public:
    J2DTextBox() { J2DTextBox__J2DTextBox1(this); }

    struct TFontSize {
        /* 0x0 */ f32 mSizeX;
        /* 0x4 */ f32 mSizeY;
    };

    void setFontSize(f32 sizeX, f32 sizeY) {
        f32 x;
        if (sizeX > 0.0f) {
            x = sizeX;
        } else {
            x = 0.0f;
        }
        field_0x11c = x;

        f32 y;
        if (sizeY > 0.0f) {
            y = sizeY;
        } else {
            y = 0.0f;
        }
        field_0x120 = y;
    }

    void setFontSize(TFontSize size) { setFontSize(size.mSizeX, size.mSizeY); }

    void setCharSpace(f32 space) { mCharSpacing = space; }

private:
    /* 0x0100 */ JUTFont* mFont;
    /* 0x0104 */ JUtility::TColor mCharColor;
    /* 0x0108 */ JUtility::TColor mGradientColor;
    /* 0x010C */ f32 field_0x10c;
    /* 0x0110 */ f32 field_0x110;
    /* 0x0114 */ f32 mCharSpacing;
    /* 0x0118 */ f32 mLineSpacing;
    /* 0x011C */ f32 field_0x11c;
    /* 0x0120 */ f32 field_0x120;
    /* 0x0124 */ char* mStringPtr;
    /* 0x0128 */ JUtility::TColor mWhiteColor;
    /* 0x012C */ JUtility::TColor mBlackColor;
    /* 0x0130 */ u8 mFlags;
    /* 0x0131 */ bool mTextFontOwned;
    /* 0x0132 */ s16 mStringLength;
};

#endif /* J2DTEXTBOX_H */