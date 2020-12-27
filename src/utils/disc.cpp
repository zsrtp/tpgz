#include "utils/disc.h"
#include "libtp_c/include/math.h"
#include "libtp_c/include/system.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t dvd_read(DVDFileInfo* file_info, void* data, int32_t size, int32_t offset) {
    constexpr const uint32_t buf_size = 0x20;
    uint8_t* buf = (uint8_t*)tp_memalign(-32, buf_size);
    int32_t read_bytes = 0;

    while (size > 0) {
        int32_t result = DVDReadPrio(file_info, buf, buf_size, (offset & ~(buf_size - 1)), 2);
        if (result <= 0) {
            break;
        }
        int32_t rem_size = buf_size - (offset & (buf_size - 1));
        tp_memcpy((void*)((uint32_t)data + read_bytes), buf + (offset & (buf_size - 1)),
                  MIN(rem_size, size));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    tp_free(buf);
    return read_bytes;
}

#ifdef __cplusplus
}
#endif
