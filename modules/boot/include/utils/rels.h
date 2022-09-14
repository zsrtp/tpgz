#ifndef TPGZ_BOOT_UTILS_RELS_H
#define TPGZ_BOOT_UTILS_RELS_H
#include "libtp_c/include/dolphin/os/OS.h"

namespace tpgz::dyn {
class GZModule {
public:
    GZModule(const char* path);
    virtual ~GZModule();

    bool load(bool negativeAlignment);
    bool loadFixed(bool negativeAlignment);

    bool close();

    bool isLoaded();

    const char* getPath() const;

private:
    uint8_t m_loaded;
    char m_path[64];

    OSModuleInfo* m_rel;
    void* m_bss;
    uint32_t m_length;

    bool load(bool negativeAlignment, bool fixedLinking);
};
}  // namespace tpgz::dyn
#endif