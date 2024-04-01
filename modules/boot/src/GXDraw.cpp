/**
 * This is decompiled dolphin SDK code from dolsdk decomp (https://github.com/doldecomp/dolsdk2001)
 * These functions were stripped from retail tp, so we have to manually add them
 */

#include "libtp_c/include/dolphin/gx/gx.h"
#include "libtp_c/include/dolphin/os/OS.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"

extern "C" {

float sinf(float);
float cosf(float);

static GXVtxDescList vcd[27];
static GXVtxAttrFmtList vat[27];

static void GetVertState(void) {
    // TODO: these cause the game to crash lol
    // geometry still seems to draw fine though? are these necessary?
    //GXGetVtxDescv(vcd);
    //GXGetVtxAttrFmtv(GX_VTXFMT3, vat);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
}

static void RestoreVertState(void) {
    GXSetVtxDescv(vcd);
    GXSetVtxAttrFmtv(GX_VTXFMT3, vat);
}

#define GET_REG_FIELD(reg, size, shift) ((int)((reg) >> (shift)) & ((1 << (size)) - 1))

KEEP_FUNC void GXGetVtxDesc(GXAttr attr, GXAttrType* type) {
    u32 cpType;

    switch (attr) {
    case GX_VA_PNMTXIDX:
        cpType = GET_REG_FIELD(gx->vcdLo, 1, 0);
        break;
    case GX_VA_TEX0MTXIDX:
        cpType = GET_REG_FIELD(gx->vcdLo, 1, 1);
        break;
    case GX_VA_TEX1MTXIDX:
        cpType = GET_REG_FIELD(gx->vcdLo, 1, 2);
        break;
    case GX_VA_TEX2MTXIDX:
        cpType = GET_REG_FIELD(gx->vcdLo, 1, 3);
        break;
    case GX_VA_TEX3MTXIDX:
        cpType = GET_REG_FIELD(gx->vcdLo, 1, 4);
        break;
    case GX_VA_TEX4MTXIDX:
        cpType = GET_REG_FIELD(gx->vcdLo, 1, 5);
        break;
    case GX_VA_TEX5MTXIDX:
        cpType = GET_REG_FIELD(gx->vcdLo, 1, 6);
        break;
    case GX_VA_TEX6MTXIDX:
        cpType = GET_REG_FIELD(gx->vcdLo, 1, 7);
        break;
    case GX_VA_TEX7MTXIDX:
        cpType = GET_REG_FIELD(gx->vcdLo, 1, 8);
        break;
    case GX_VA_POS:
        cpType = GET_REG_FIELD(gx->vcdLo, 2, 9);
        break;
    case GX_VA_NRM:
        cpType = gx->hasNrms ? GET_REG_FIELD(gx->vcdLo, 2, 11) : 0;
        break;
    case GX_VA_NBT:
        cpType = gx->hasBiNrms ? GET_REG_FIELD(gx->vcdLo, 2, 11) : 0;
        break;
    case GX_VA_CLR0:
        cpType = GET_REG_FIELD(gx->vcdLo, 2, 13);
        break;
    case GX_VA_CLR1:
        cpType = GET_REG_FIELD(gx->vcdLo, 2, 15);
        break;
    case GX_VA_TEX0:
        cpType = GET_REG_FIELD(gx->vcdHi, 2, 0);
        break;
    case GX_VA_TEX1:
        cpType = GET_REG_FIELD(gx->vcdHi, 2, 2);
        break;
    case GX_VA_TEX2:
        cpType = GET_REG_FIELD(gx->vcdHi, 2, 4);
        break;
    case GX_VA_TEX3:
        cpType = GET_REG_FIELD(gx->vcdHi, 2, 6);
        break;
    case GX_VA_TEX4:
        cpType = GET_REG_FIELD(gx->vcdHi, 2, 8);
        break;
    case GX_VA_TEX5:
        cpType = GET_REG_FIELD(gx->vcdHi, 2, 10);
        break;
    case GX_VA_TEX6:
        cpType = GET_REG_FIELD(gx->vcdHi, 2, 12);
        break;
    case GX_VA_TEX7:
        cpType = GET_REG_FIELD(gx->vcdHi, 2, 14);
        break;
    default:
        cpType = 0;
        break;
    }

    // OSReport("GXGetVtxDesc ERROR: %d\n", error);
    *type = (GXAttrType)cpType;
}

void GXGetVtxDescv(GXVtxDescList* vcd) {
    int attr;

    for (attr = 0; attr < GX_VA_MAX_ATTR; attr++) {
        vcd[attr].attr = (GXAttr)attr;
        GXGetVtxDesc((GXAttr)attr, &vcd[attr].type);
    }
    vcd[attr].attr = (GXAttr)0xFF;
}

void GXGetVtxAttrFmt(GXVtxFmt fmt, GXAttr attr, GXCompCnt* cnt, GXCompType* type, u8* frac) {
    u32* va;
    u32* vb;
    u32* vc;

    va = &gx->vatA[fmt];
    vb = &gx->vatB[fmt];
    vc = &gx->vatC[fmt];
    switch (attr) {
    case GX_VA_POS:
        *cnt = (GXCompCnt)GET_REG_FIELD(*va, 1, 0);
        *type = (GXCompType)GET_REG_FIELD(*va, 3, 1);
        *frac = (u8)(*va >> 4) & 0x1F;  // GET_REG_FIELD(*va, 5, 4)
        return;
    case GX_VA_NRM:
    case GX_VA_NBT:
        *cnt = (GXCompCnt)GET_REG_FIELD(*va, 1, 9);
        if (*cnt == GX_TEX_ST && (u8)(*va >> 0x1F) != 0) {
            *cnt = GX_NRM_NBT3;
        }
        *type = (GXCompType)GET_REG_FIELD(*va, 3, 10);
        *frac = 0;
        return;
    case GX_VA_CLR0:
        *cnt = (GXCompCnt)GET_REG_FIELD(*va, 1, 13);
        *type = (GXCompType)GET_REG_FIELD(*va, 3, 14);
        *frac = 0;
        return;
    case GX_VA_CLR1:
        *cnt = (GXCompCnt)GET_REG_FIELD(*va, 1, 17);
        *type = (GXCompType)GET_REG_FIELD(*va, 3, 18);
        *frac = 0;
        return;
    case GX_VA_TEX0:
        *cnt = (GXCompCnt)GET_REG_FIELD(*va, 1, 21);
        *type = (GXCompType)GET_REG_FIELD(*va, 3, 22);
        *frac = (u8)(*va >> 0x19U) & 0x1F;
        return;
    case GX_VA_TEX1:
        *cnt = (GXCompCnt)GET_REG_FIELD(*vb, 1, 0);
        *type = (GXCompType)GET_REG_FIELD(*vb, 3, 1);
        *frac = (u8)(*vb >> 4U) & 0x1F;
        return;
    case GX_VA_TEX2:
        *cnt = (GXCompCnt)GET_REG_FIELD(*vb, 1, 9);
        *type = (GXCompType)GET_REG_FIELD(*vb, 3, 10);
        *frac = (u8)(*vb >> 0xDU) & 0x1F;
        return;
    case GX_VA_TEX3:
        *cnt = (GXCompCnt)GET_REG_FIELD(*vb, 1, 18);
        *type = (GXCompType)GET_REG_FIELD(*vb, 3, 19);
        *frac = (u8)(*vb >> 0x16U) & 0x1F;
        return;
    case GX_VA_TEX4:
        *cnt = (GXCompCnt)GET_REG_FIELD(*vb, 1, 27);
        *type = (GXCompType)GET_REG_FIELD(*vb, 3, 28);
        *frac = GET_REG_FIELD(*vc, 5, 0);
        return;
    case GX_VA_TEX5:
        *cnt = (GXCompCnt)GET_REG_FIELD(*vc, 1, 5);
        *type = (GXCompType)GET_REG_FIELD(*vc, 3, 6);
        *frac = (u8)(*vc >> 9U) & 0x1F;
        return;
    case GX_VA_TEX6:
        *cnt = (GXCompCnt)GET_REG_FIELD(*vc, 1, 14);
        *type = (GXCompType)GET_REG_FIELD(*vc, 3, 15);
        *frac = (u8)(*vc >> 0x12) & 0x1F;
        return;
    case GX_VA_TEX7:
        *cnt = (GXCompCnt)GET_REG_FIELD(*vc, 1, 23);
        *type = (GXCompType)GET_REG_FIELD(*vc, 3, 24);
        *frac = (int)(*vc >> 0x1BU);
        return;
    default:
        *cnt = GX_TEX_ST;
        *type = GX_RGB565;
        *frac = 0;
        return;
    }
}

void GXGetVtxAttrFmtv(GXVtxFmt fmt, GXVtxAttrFmtList* vat) {
    int attr;

    for (attr = GX_VA_POS; attr < GX_VA_MAX_ATTR; attr++) {
        vat->attr = (GXAttr)attr;
        GXGetVtxAttrFmt(fmt, (GXAttr)attr, &vat->cnt, &vat->type, &vat->frac);
        vat++;
    }
    vat->attr = GX_VA_NULL;
}

void GXDrawSphere(u8 numMajor, u8 numMinor) {
    GXAttrType ttype = GX_DIRECT;
    f32 radius = 1.0f;
    f32 majorStep = 3.1415927f / numMajor;
    f32 minorStep = 6.2831855f / numMinor;
    s32 i, j;
    f32 a, b;
    f32 r0, r1;
    f32 z0, z1;
    f32 c;
    f32 x, y;

    //GXGetVtxDesc(GX_VA_TEX0, &ttype);
    GetVertState();
    if (ttype != GX_NONE) {
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0U);
    }
    for (i = 0; i < numMajor; i++) {
        a = i * majorStep;
        b = a + majorStep;
        r0 = radius * sinf(a);
        r1 = radius * sinf(b);
        z0 = radius * cosf(a);
        z1 = radius * cosf(b);
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT3, (numMinor + 1) * 2);
        for (j = 0; j <= numMinor; j++) {
            c = j * minorStep;
            x = cosf(c);
            y = sinf(c);
            GXPosition3f32(x * r1, y * r1, z1);
            GXNormal3f32((x * r1) / radius, (y * r1) / radius, z1 / radius);
            if (ttype != GX_NONE) {
                GXTexCoord2f32((f32)j / (f32)numMinor, (f32)(i + 1) / (f32)numMajor);
            }
            GXPosition3f32(x * r0, y * r0, z0);
            GXNormal3f32((x * r0) / radius, (y * r0) / radius, z0 / radius);
            if (ttype != GX_NONE) {
                GXTexCoord2f32((f32)j / (f32)numMinor, (f32)i / (f32)numMajor);
            }
        }
        GXEnd();
    }
    RestoreVertState();
}

void GXDrawCylinder(u8 numEdges) {
    s32 i;
    f32 top;
    f32 bottom;
    f32 x[100];
    f32 y[100];
    f32 angle;

    top = 1.0f;
    bottom = -top;

    GetVertState();

    for (i = 0; i <= numEdges; i++) {
        angle = (3.1415927f * (2.0f * i)) / numEdges;
        x[i] = cosf(angle);
        y[i] = sinf(angle);
    }

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT3, (numEdges + 1) * 2);
    for (i = 0; i <= numEdges; i++) {
        GXPosition3f32(x[i], y[i], bottom);
        GXNormal3f32(x[i], y[i], 0.0f);
        GXPosition3f32(x[i], y[i], top);
        GXNormal3f32(x[i], y[i], 0.0f);
    }
    GXEnd();

    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT3, numEdges + 2);
    GXPosition3f32(0.0f, 0.0f, top);
    GXNormal3f32(0.0f, 0.0f, 1.0f);
    for (i = 0; i <= numEdges; i++) {
        GXPosition3f32(x[i], -y[i], top);
        GXNormal3f32(0.0f, 0.0f, 1.0f);
    }
    GXEnd();

    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT3, numEdges + 2);
    GXPosition3f32(0.0f, 0.0f, bottom);
    GXNormal3f32(0.0f, 0.0f, -1.0f);
    for (i = 0; i <= numEdges; i++) {
        GXPosition3f32(x[i], y[i], bottom);
        GXNormal3f32(0.0f, 0.0f, -1.0f);
    }
    GXEnd();

    RestoreVertState();
}
}