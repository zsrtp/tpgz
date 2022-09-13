#ifndef JAISTREAMMGR_H
#define JAISTREAMMGR_H

#include "JAISound.h"
#include "../JSupport/JSUList.h"

class JAIStreamMgr;

struct JAIStream {};

class JAIStreamMgr {
public:
    /* 0x00 */ JAISoundActivity mActivity;
    /* 0x04 */ JAISoundParamsMove mParams;
    /* 0x54 */ int field_0x54;
    /* 0x58 */ JSUList<JAIStream> mStreamList;
    /* 0x64 */ int field_0x64;
    /* 0x68 */ int field_0x68;
    /* 0x6C */ int field_0x6c;
};  // Size: 0x70

#endif /* JAISTREAMMGR_H */