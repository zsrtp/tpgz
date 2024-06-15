#include <main.h>
#include "gz_flags.h"
#include "umd.h"

namespace tpgz::modules {
void main() {
    GZFlg_addFlag(new GZFlag{GZFLG_UMD, ACTIVE_FUNC(STNG_TOOLS_UMD), POST_GAME_LOOP,
                             UMDIndicator::execute});
}
void exit() {
    auto* flg = GZFlg_removeFlag(GZFLG_UMD);
    delete flg;
}

}  // namespace tpgz::modules