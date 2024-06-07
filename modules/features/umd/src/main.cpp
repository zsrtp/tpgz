#include <main.h>
#include "gz_flags.h"
#include "umd.h"

namespace tpgz::modules {
void main() {
    auto* stng = GZStng_getSetting(STNG_TOOLS_UMD);
    GZFlg_addFlag(new GZFlag{GZFLG_UMD, stng ? (bool*)stng->data : nullptr, POST_GAME_LOOP,
                             UMDIndicator::execute});
}
void exit() {
    auto* flg = GZFlg_removeFlag(GZFLG_UMD);
    delete flg;
}

}  // namespace tpgz::modules