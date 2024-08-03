#include <main.h>
#include "gz_flags.h"
#include "lfc_checker.h"

namespace tpgz::modules {
void main() {
    GZFlg_addFlag(
        new GZFlag{GZFLG_LFC, ACTIVE_FUNC(STNG_TOOLS_LFC), GAME_LOOP, LFCChecker::execute});
}
void exit() {
    auto* flg = GZFlg_removeFlag(GZFLG_LFC);
    delete flg;
}

}  // namespace tpgz::modules