#ifndef C_M3D_G_CIR_H
#define C_M3D_G_CIR_H

class cM2dGCir {
public:
    float mPosX;
    float mPosY;
    float mRadius;
    virtual ~cM2dGCir() {}
};

class cM3dGCir : public cM2dGCir {
    float mPosZ;

public:
    virtual ~cM3dGCir(void);
};

#endif /* C_M3D_G_CIR_H */
