#ifndef JKRDISPOSER_H_
#define JKRDISPOSER_H_

#include "../JSupport/JSUList.h"

class JKRHeap;
class JKRDisposer {
public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ JKRHeap* mHeap;
    /* 0x08 */ JSULink<JKRDisposer> mLink;
};

#endif