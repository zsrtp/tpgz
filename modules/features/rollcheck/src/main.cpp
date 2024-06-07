#include <main.h>
#include "gz_flags.h"
#include "rollcheck.h"

namespace tpgz::modules {
void main() {
    auto* stng = GZStng_getSetting(STNG_TOOLS_ROLL);
    GZFlg_addFlag(
        new GZFlag{GZFLG_ROLL, stng ? (bool*)stng->data : nullptr, GAME_LOOP, RollIndicator::execute});
}
void exit() {
    auto* flg = GZFlg_removeFlag(GZFLG_ROLL);
    delete flg;
}

}  // namespace tpgz::modules