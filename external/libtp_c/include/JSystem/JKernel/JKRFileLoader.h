#ifndef JKRFILELOADER_H_
#define JKRFILELOADER_H_

#include "JKRDisposer.h"

class JKRFileFinder;
class JKRFileLoader : public JKRDisposer {
public:
    JKRFileLoader(void);
    virtual ~JKRFileLoader();

    bool isMounted() const { return this->mIsMounted; }
    uint32_t getVolumeType() const { return this->mVolumeType; }

protected:
    /* 0x00 */  // vtable
    /* 0x04 */  // JKRDisposer
    /* 0x18 */ JSULink<JKRFileLoader> mFileLoaderLink;
    /* 0x28 */ const char* mVolumeName;
    /* 0x2C */ uint32_t mVolumeType;
    /* 0x30 */ bool mIsMounted;
    /* 0x31 */ uint8_t field_0x31[3];
    /* 0x34 */ uint32_t mMountCount;
};

#endif