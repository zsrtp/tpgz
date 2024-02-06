#ifndef C_M3D_G_CIR_H
#define C_M3D_G_CIR_H

class cM2dGCir {
public:
    f32 mPosX;
    f32 mPosY;
    f32 mRadius;
    virtual ~cM2dGCir() {}
};

class cM3dGCir : public cM2dGCir {
    f32 mPosZ;

public:
    virtual ~cM3dGCir(void);
};

#endif /* C_M3D_G_CIR_H */
