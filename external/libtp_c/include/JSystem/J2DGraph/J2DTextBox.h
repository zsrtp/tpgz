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

typedef void (*J2DTextBox__draw2_t)(J2DTextBox* thisx, float x, float y, float size,
                                    J2DTextBoxHBinding binding);
#define J2DTextBox__draw2 ((J2DTextBox__draw2_t)J2DTextBox__draw2_addr)

class J2DTextBox : public J2DPane {
public:
    J2DTextBox() { J2DTextBox__J2DTextBox1(this); }

    struct TFontSize {
        /* 0x0 */ float mSizeX;
        /* 0x4 */ float mSizeY;
    };

    void setFontSize(float sizeX, float sizeY) {
        float x;
        if (sizeX > 0.0f) {
            x = sizeX;
        } else {
            x = 0.0f;
        }
        field_0x11c = x;

        float y;
        if (sizeY > 0.0f) {
            y = sizeY;
        } else {
            y = 0.0f;
        }
        field_0x120 = y;
    }

    void setFontSize(TFontSize size) { setFontSize(size.mSizeX, size.mSizeY); }

    void setCharSpace(float space) { mCharSpacing = space; }

private:
    /* 0x0100 */ JUTFont* mFont;
    /* 0x0104 */ JUtility::TColor mCharColor;
    /* 0x0108 */ JUtility::TColor mGradientColor;
    /* 0x010C */ float field_0x10c;
    /* 0x0110 */ float field_0x110;
    /* 0x0114 */ float mCharSpacing;
    /* 0x0118 */ float mLineSpacing;
    /* 0x011C */ float field_0x11c;
    /* 0x0120 */ float field_0x120;
    /* 0x0124 */ char* mStringPtr;
    /* 0x0128 */ JUtility::TColor mWhiteColor;
    /* 0x012C */ JUtility::TColor mBlackColor;
    /* 0x0130 */ uint8_t mFlags;
    /* 0x0131 */ bool mTextFontOwned;
    /* 0x0132 */ int16_t mStringLength;
};

#endif /* J2DTEXTBOX_H */