#include <main.h>
#include "gz_flags.h"
#include "ebmb_checker.h"

namespace tpgz::modules {
void main() {
    GZFlg_addFlag(
        new GZFlag{GZFLG_EBMB, ACTIVE_FUNC(STNG_TOOLS_EBMB), GAME_LOOP, EBMBChecker::execute});
}
void exit() {
    auto* flg = GZFlg_removeFlag(GZFLG_EBMB);
    delete flg;
}

}  // namespace tpgz::modules