#include <main.h>
#include "gz_flags.h"
#include "rollcheck.h"

namespace tpgz::modules {
void main() {
    GZFlg_addFlag(
        new GZFlag{GZFLG_ROLL, ACTIVE_FUNC(STNG_TOOLS_ROLL), GAME_LOOP, RollIndicator::execute});
}
void exit() {
    auto* flg = GZFlg_removeFlag(GZFLG_ROLL);
    delete flg;
}

}  // namespace tpgz::modules