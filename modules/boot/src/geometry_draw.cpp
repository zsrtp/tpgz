#include "collision_view.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/dolphin/gx/gx.h"
#include "libtp_c/include/JSystem/J3DGraphBase/J3DSys.h"
#include "libtp_c/include/m_Do/m_Do_mtx.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "libtp_c/include/d/bg/d_bg_s_captpoly.h"

#include <cstdio>
#include "font.h"

KEEP_VAR CollisionItem g_collisionFlags[COLLISION_FLAGS_AMNT] = {
    {VIEW_POLYGON_INDEX, false},
    {VIEW_AT_INDEX, false},
    {VIEW_TG_INDEX, false},
    {VIEW_CO_INDEX, false},
};

#define DRAW_PACKET_MAX 1000  // max amount of draw packets allowed to be drawn at a time

u32 l_drawPacketListNum;
static J3DPacket* l_drawPacketList[DRAW_PACKET_MAX];

J3DPacket* dDbVw_setDrawPacketList(J3DPacket* p_packet, int buf_type) {
    if (p_packet == NULL) {
        p_packet = NULL;
    } else {
        if (l_drawPacketListNum >= DRAW_PACKET_MAX) {
            delete p_packet;
            p_packet = NULL;
        } else {
            l_drawPacketList[l_drawPacketListNum] = p_packet;
            l_drawPacketListNum++;
            J3DDrawBuffer__entryImm(j3dSys.getDrawBuffer(buf_type), p_packet, 0);
        }
    }
    return p_packet;
}

void dDbVw_deleteDrawPacketList() {
    for (u32 i = 0; i < l_drawPacketListNum; i++) {
        if (l_drawPacketList[i] != NULL) {
            delete l_drawPacketList[i];
            l_drawPacketList[i] = NULL;
        }
    }

    l_drawPacketListNum = 0;
}

//-------------------------------------------------------
//                         CUBE
//-------------------------------------------------------

void drawCube(MtxP mtx, cXyz* array, const GXColor& color) {
    GXSetArray(GX_VA_POS, array, sizeof(cXyz));
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_CLEAR);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 14);
    GXPosition1x8(4);
    GXPosition1x8(6);
    GXPosition1x8(5);
    GXPosition1x8(7);
    GXPosition1x8(3);
    GXPosition1x8(6);
    GXPosition1x8(2);
    GXPosition1x8(4);
    GXPosition1x8(0);
    GXPosition1x8(5);
    GXPosition1x8(1);
    GXPosition1x8(3);
    GXPosition1x8(0);
    GXPosition1x8(2);
    GXEnd();
}

static J3DPacket__vtable_t mDoExt_cubePacket__vtable {
    (void*)nullptr,  // RTTI
    (void*)nullptr,  // pad
    (void*)&J3DPacket__entry,
    (void*)&mDoExt_cubePacket__draw,
    (void*)&mDoExt_cubePacket__dtor,
};

void dDbVw_drawCubeXlu(cXyz& pos, cXyz& size, csXyz& angle, const GXColor& color) {
    if (l_drawPacketListNum < DRAW_PACKET_MAX) {
        mDoExt_cubePacket* cube = new mDoExt_cubePacket(pos, size, angle, color);
        cube->base.vtable = &mDoExt_cubePacket__vtable;

        dDbVw_setDrawPacketList(&cube->base, 1);
    }
}

void mDoExt_cubePacket__dtor(mDoExt_cubePacket* i_this) {
    i_this->~mDoExt_cubePacket();
    delete i_this;
}

void mDoExt_cubePacket__draw(mDoExt_cubePacket* i_this) {
    static Vec points[8] = {
        {-1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, -1.0f},
        {-1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {-1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, 1.0f},
    };

    mDoMtx_stack_c::transS(i_this->mPosition.x, i_this-> mPosition.y, i_this->mPosition.z);
    mDoMtx_stack_c::XYZrotM(i_this->mAngle.x, i_this->mAngle.y, i_this->mAngle.z);
    mDoMtx_stack_c::scaleM(i_this->mSize.x, i_this->mSize.y, i_this->mSize.z);
    mDoMtx_stack_c::revConcat(j3dSys.getViewMtx());
    drawCube(mDoMtx_stack_c::get(), (cXyz*)points, i_this->mColor);
}

//-------------------------------------------------------
//                        SPHERE
//-------------------------------------------------------

static J3DPacket__vtable_t mDoExt_spherePacket__vtable {
    (void*)nullptr,  // RTTI
    (void*)nullptr,  // pad
    (void*)&J3DPacket__entry,
    (void*)&mDoExt_spherePacket__draw,
    (void*)&mDoExt_spherePacket__dtor,
};

void dDbVw_drawSphereXlu(cXyz& position, f32 radius, const GXColor& color, u8 param_3) {
    if (l_drawPacketListNum < DRAW_PACKET_MAX) {
        mDoExt_spherePacket* sph = new mDoExt_spherePacket(position, radius, color, param_3);
        sph->base.vtable = &mDoExt_spherePacket__vtable;

        dDbVw_setDrawPacketList(&sph->base, 1);
    }
}

void mDoExt_spherePacket__dtor(mDoExt_spherePacket* i_this) {
    i_this->~mDoExt_spherePacket();
    delete i_this;
}

void mDoExt_spherePacket__draw(mDoExt_spherePacket* i_this) {
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, i_this->mColor);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);

    if (i_this->_24) {
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    } else {
        GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    }

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_CLEAR);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);

    mDoMtx_stack_c::copy(j3dSys.getViewMtx());
    mDoMtx_stack_c::transM(i_this->mPosition.x, i_this->mPosition.y, i_this->mPosition.z);
    mDoMtx_stack_c::scaleM(i_this->mSize, i_this->mSize, i_this->mSize);

    GXLoadPosMtxImm(mDoMtx_stack_c::get(), 0);
    mDoMtx_stack_c::inverseTranspose();

    GXLoadNrmMtxImm(mDoMtx_stack_c::get(), 0);
    GXSetCurrentMtx(0);

    GXDrawSphere(8, 8);
}

//-------------------------------------------------------
//                       CYLINDER
//-------------------------------------------------------

static J3DPacket__vtable_t mDoExt_cylinderPacket__vtable {
    (void*)nullptr,  // RTTI
    (void*)nullptr,  // pad
    (void*)&J3DPacket__entry,
    (void*)&mDoExt_cylinderPacket__draw,
    (void*)&mDoExt_cylinderPacket__dtor,
};

void dDbVw_drawCylinderXlu(cXyz& position, f32 radius, f32 height, const GXColor& color, u8 param_4) {
    if (l_drawPacketListNum < DRAW_PACKET_MAX) {
        mDoExt_cylinderPacket* cyl = new mDoExt_cylinderPacket(position, radius, height, color, param_4);
        cyl->base.vtable = &mDoExt_cylinderPacket__vtable;

        dDbVw_setDrawPacketList(&cyl->base, 1);
    }
}

void mDoExt_cylinderPacket__dtor(mDoExt_cylinderPacket* i_this) {
    i_this->~mDoExt_cylinderPacket();
    delete i_this;
}

void mDoExt_cylinderPacket__draw(mDoExt_cylinderPacket* i_this) {
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, i_this->mColor);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);

    if (i_this->_28) {
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    } else {
        GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    }

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_CLEAR);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);

    f32 height = i_this->mHeight;

    mDoMtx_stack_c::copy(j3dSys.getViewMtx());
    mDoMtx_stack_c::transM(i_this->mPosition.x, i_this->mPosition.y + (height / 2), i_this->mPosition.z);
    mDoMtx_stack_c::scaleM(i_this->mRadius, i_this->mRadius + (height / 2), i_this->mRadius);
    mDoMtx_stack_c::XrotM(0x4000);

    GXLoadPosMtxImm(mDoMtx_stack_c::get(), 0);
    mDoMtx_stack_c::inverseTranspose();

    GXLoadNrmMtxImm(mDoMtx_stack_c::get(), 0);
    GXSetCurrentMtx(0);

    GXDrawCylinder(8);
}

//-------------------------------------------------------
//                     8 Point Cube
//-------------------------------------------------------

static J3DPacket__vtable_t mDoExt_cube8pPacket__vtable {
    (void*)nullptr,  // RTTI
    (void*)nullptr,  // pad
    (void*)&J3DPacket__entry,
    (void*)&mDoExt_cube8pPacket__draw,
    (void*)&mDoExt_cube8pPacket__dtor,
};

void dDbVw_drawCube8pXlu(cXyz* points, const GXColor& color) {
    if (l_drawPacketListNum < DRAW_PACKET_MAX) {
        mDoExt_cube8pPacket* cube = new mDoExt_cube8pPacket(points, color);
        cube->base.vtable = &mDoExt_cube8pPacket__vtable;

        dDbVw_setDrawPacketList(&cube->base, 1);
    }
}

void mDoExt_cube8pPacket__dtor(mDoExt_cube8pPacket* i_this) {
    i_this->~mDoExt_cube8pPacket();
    delete i_this;
}

void mDoExt_cube8pPacket__draw(mDoExt_cube8pPacket* i_this) {
    drawCube(j3dSys.getViewMtx(), i_this->mPoints, i_this->mColor);
}

//-------------------------------------------------------
//                       Triangle
//-------------------------------------------------------

static J3DPacket__vtable_t mDoExt_trianglePacket__vtable {
    (void*)nullptr,  // RTTI
    (void*)nullptr,  // pad
    (void*)&J3DPacket__entry,
    (void*)&mDoExt_trianglePacket__draw,
    (void*)&mDoExt_trianglePacket__dtor,
};

void dDbVw_drawTriangleXlu(cXyz* points, const GXColor& color, u8 param_2) {
    if (l_drawPacketListNum < DRAW_PACKET_MAX) {
        mDoExt_trianglePacket* tri = new mDoExt_trianglePacket(points, color, param_2);
        tri->base.vtable = &mDoExt_trianglePacket__vtable;

        dDbVw_setDrawPacketList(&tri->base, 1);
    }
}

void mDoExt_trianglePacket__dtor(mDoExt_trianglePacket* i_this) {
    i_this->~mDoExt_trianglePacket();
    delete i_this;
}

void mDoExt_trianglePacket__draw(mDoExt_trianglePacket* i_this) {
    J3DSys__reinitGX(&j3dSys);

    GXSetArray(GX_VA_POS, i_this->mPoints, sizeof(cXyz));
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXLoadPosMtxImm(j3dSys.getViewMtx(), 0);
    GXSetCurrentMtx(0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, i_this->mColor);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetZCompLoc(GX_ENABLE);

    if (i_this->_38) {
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    } else {
        GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    }

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_CLEAR);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);

    GXColor clearColor = {0, 0, 0, 0};
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, clearColor);
    GXSetFogRangeAdj(GX_DISABLE, 0, nullptr);
    GXSetCullMode(GX_CULL_NONE);
    GXSetDither(GX_ENABLE);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetNumIndStages(0);

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
    GXPosition1x8(0);
    GXPosition1x8(1);
    GXPosition1x8(2);
    GXEnd();

    resetVcdVatCache();
}

//-------------------------------------------------------
//                         Line
//-------------------------------------------------------

static J3DPacket__vtable_t mDoExt_linePacket__vtable {
    (void*)nullptr,  // RTTI
    (void*)nullptr,  // pad
    (void*)&J3DPacket__entry,
    (void*)&mDoExt_linePacket__draw,
    (void*)&mDoExt_linePacket__dtor,
};

void dDbVw_drawLineXlu(cXyz& pointA, cXyz& pointB, const GXColor& color, u8 param_3, u8 width) {
    if (l_drawPacketListNum < DRAW_PACKET_MAX) {
        mDoExt_linePacket* line = new mDoExt_linePacket(pointA, pointB, color, param_3, width);
        line->base.vtable = &mDoExt_linePacket__vtable;

        dDbVw_setDrawPacketList(&line->base, 1);
    }
}

void mDoExt_linePacket__dtor(mDoExt_linePacket* i_this) {
    i_this->~mDoExt_linePacket();
    delete i_this;
}

void mDoExt_linePacket__draw(mDoExt_linePacket* i_this) {
    J3DSys__reinitGX(&j3dSys);

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXLoadPosMtxImm(j3dSys.getViewMtx(), 0);
    GXSetCurrentMtx(0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, i_this->mColor);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetZCompLoc(GX_ENABLE);

    if (i_this->_2C) {
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    } else {
        GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    }

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_CLEAR);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);

    GXColor clearColor = {0, 0, 0, 0};
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, clearColor);
    GXSetFogRangeAdj(GX_DISABLE, 0, nullptr);
    GXSetCullMode(GX_CULL_NONE);
    GXSetDither(GX_ENABLE);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetNumIndStages(0);
    GXSetLineWidth(i_this->mWidth, GX_TO_ZERO);

    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXPosition3f32(i_this->mPointA.x, i_this->mPointA.y, i_this->mPointA.z);
    GXPosition3f32(i_this->mPointB.x, i_this->mPointB.y, i_this->mPointB.z);
    GXEnd();

    resetVcdVatCache();
}

#define MAX_DRAW_DIST 2000.0f

void dCcD_Cyl_Draw(dCcD_Cyl* i_this, const GXColor& i_color) {
    if (dComIfGp_getPlayer()->current.pos.abs(i_this->mCylAttr.cyl.mCenter) < MAX_DRAW_DIST) {
        dDbVw_drawCylinderXlu(i_this->mCylAttr.cyl.mCenter, i_this->mCylAttr.cyl.GetR(), i_this->mCylAttr.cyl.GetH(), i_color, 1);
    }
}

void dCcD_Sph_Draw(dCcD_Sph* i_this, const GXColor& i_color) {
    if (dComIfGp_getPlayer()->current.pos.abs(i_this->mSphAttr.sph.mCenter) < MAX_DRAW_DIST) {
        dDbVw_drawSphereXlu(i_this->mSphAttr.sph.mCenter, i_this->mSphAttr.sph.GetR(), i_color, 1);
    }
}

void dCcD_Cps_Draw(dCcD_Cps* i_this, const GXColor& i_color) {}

KEEP_FUNC void GZ_drawCc(dCcS* i_this) {
    static bool init_vtables = false;
    if (!init_vtables) {
        // we patch the original vtables with our own functions so that
        // we can replicate the debug rom functionality of each collider type
        // having their own specific virtual draw function.
        dCcD_Cyl_vtable.Draw = (cCcD_DrawFn)dCcD_Cyl_Draw;
        dCcD_Sph_vtable.Draw = (cCcD_DrawFn)dCcD_Sph_Draw;
        dCcD_Cps_vtable.Draw = (cCcD_DrawFn)dCcD_Cps_Draw;
        init_vtables = true;
    }

    daAlink_c* player = dComIfGp_getPlayer();
    if (player != NULL) {
        if (g_collisionFlags[VIEW_AT_INDEX].active) {
            //OSReport("At:%d\n", i_this->mObjAtCount);

            for (u16 i = 0; i < 0x100; i++) {
                cCcD_Obj* obj = i_this->mpObjAt[i];
                if (obj != NULL) {
                    static const GXColor at_color = {0xFF, 0x00, 0x00, 0x90};
                    obj->vtable->Draw(obj, at_color);
                }
            }
        }

        if (g_collisionFlags[VIEW_TG_INDEX].active) {
            //OSReport("Tg:%d\n", i_this->mObjTgCount);

            for (u16 i = 0; i < 0x300; i++) {
                cCcD_Obj* obj = i_this->mpObjTg[i];
                if (obj != NULL) {
                    static const GXColor tg_color = {0x00, 0xFF, 0x00, 0x90};
                    obj->vtable->Draw(obj, tg_color);
                }
            }
        }

        if (g_collisionFlags[VIEW_CO_INDEX].active) {
            //OSReport("Co:%d\n", i_this->mObjCoCount);

            for (u16 i = 0; i < 0x100; i++) {
                cCcD_Obj* obj = i_this->mpObjCo[i];
                if (obj != NULL) {
                    static const GXColor co_color = {0xFF, 0xFF, 0xFF, 0x90};
                    obj->vtable->Draw(obj, co_color);
                }
            }
        }
    }
}

//-------------------------------------------------------
//                      POLY DRAW
//-------------------------------------------------------

int poly_draw(dBgS_CaptPoly* i_captpoly, cBgD_Vtx_t* i_vtx, int i_ia, int i_ib, int i_ic, cM3dGPla* i_plane) {
    cXyz vertices[3];

    GXColor ground_col = {0xFF, 0x00, 0x00, 0x80};
    GXColor roof_col = {0x00, 0x00, 0xFF, 0x80};
    GXColor wall_col = {0x00, 0xFF, 0x00, 0x80};

    cXyz raise;
    PSVECScale(&i_plane->mNormal, &raise, 1.5f);

    vertices[0] = i_vtx[i_ia].vertex;
    vertices[1] = i_vtx[i_ib].vertex;
    vertices[2] = i_vtx[i_ic].vertex;

    PSVECAdd(&vertices[0], &raise, &vertices[0]);
    PSVECAdd(&vertices[1], &raise, &vertices[1]);
    PSVECAdd(&vertices[2], &raise, &vertices[2]);

    if (cBgW_CheckBGround(i_plane->mNormal.y)) {
        dDbVw_drawTriangleXlu(vertices, ground_col, 1);
    } else if (cBgW_CheckBRoof(i_plane->mNormal.y)) {
        dDbVw_drawTriangleXlu(vertices, roof_col, 1);
    } else {
        dDbVw_drawTriangleXlu(vertices, wall_col, 1);
    }

    return 0;
}

void CaptPoly(dBgS_CaptPoly& i_captpoly) {
    cBgS_ChkElm* poly_elm = dComIfG_Bgsp()->m_chk_element;

    for (int i = 0; i < 0x100; i++) {
        if (poly_elm->ChkUsed()) {
            poly_elm->m_bgw_base_ptr->vtable->CaptPoly(poly_elm->m_bgw_base_ptr, i_captpoly);
        }
        poly_elm++;
    }
}

KEEP_FUNC void GZ_drawPolygons() {
    if (g_collisionFlags[VIEW_POLYGON_INDEX].active) {
        daAlink_c* player = dComIfGp_getPlayer();

        if (player != NULL) {
            cM3dGAab aab;
			cXyz min;
			cXyz max;

			f32 range = 100.0f;
			min.set(player->current.pos.x - range, player->current.pos.y - range, player->current.pos.z - range);
			max.set(player->current.pos.x + range, player->current.pos.y + range, player->current.pos.z + range);
			aab.mMin = min;
			aab.mMax = max;

            dBgS_CaptPoly poly_capt;
			poly_capt.field_0x14.mGrpPassChkInfo.OnFullGrp();
			poly_capt.mAab.mMin = aab.mMin;
			poly_capt.mAab.mMax = aab.mMax;
			poly_capt.mpCallback = poly_draw;

			CaptPoly(poly_capt);
        }
    }    
}