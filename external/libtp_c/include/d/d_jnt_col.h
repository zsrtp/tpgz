#ifndef D_D_JNT_COL_H
#define D_D_JNT_COL_H

struct J3DModel {};

class dJntColData_c {};

class dJntCol_c {
public:
    /* 0x00 */ dJntColData_c* mData;
    /* 0x04 */ J3DModel* mModel;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ int field_0xc;
};

#endif /* D_D_JNT_COL_H */
