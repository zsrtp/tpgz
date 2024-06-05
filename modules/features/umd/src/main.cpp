#include <main.h>
#include "gz_flags.h"
#include "umd.h"

namespace tpgz::modules {
void main() {
    GZFlg_addFlag(new GZFlag{GZFLG_UMD, &g_tools[UMD_INDEX].active, POST_GAME_LOOP, UMDIndicator::execute});
}
void exit() {
    GZFlg_removeFlag(GZFLG_UMD);
}

}  // namespace tpgz::modules