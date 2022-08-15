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

private:
    uint8_t m_loaded;
    const char* m_path;

    OSModuleInfo* m_rel;
    void* m_bss;
    uint32_t m_length;

    bool load(bool negativeAlignment, bool fixedLinking);
};
}  // namespace tpgz::dyn
#endif