#include "gcn_c/include/dvd.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Like DVDReadPrio, but allows for arbitrary sizes and offsets.
 */
int32_t dvd_read(DVDFileInfo* file_info, void* data, int32_t size, int32_t offset);

#ifdef __cplusplus
}
#endif
