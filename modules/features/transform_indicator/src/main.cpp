#include <main.h>
#include "transform_indicator.h"
#include "rels/include/cxx.h"
#include "events/draw_listener.h"
#include "utils/texture.h"

namespace tpgz::modules {
void main() {
    if (TransformIndicator::l_humanTex.loadCode == TexCode::TEX_UNLOADED) {
        load_texture("/tpgz/tex/hand.tex", &TransformIndicator::l_humanTex);
    }
    if (TransformIndicator::l_wolfTex.loadCode == TexCode::TEX_UNLOADED) {
        load_texture("/tpgz/tex/wolf.tex", &TransformIndicator::l_wolfTex);
    }

    g_drawListener->addListener(TransformIndicator::draw);
}
void exit() {
    g_drawListener->removeListener(TransformIndicator::draw);

    if (TransformIndicator::l_humanTex.loadCode == TexCode::TEX_OK) {
        free_texture(&TransformIndicator::l_humanTex);
    }
    if (TransformIndicator::l_wolfTex.loadCode == TexCode::TEX_OK) {
        free_texture(&TransformIndicator::l_wolfTex);
    }
}

}  // namespace tpgz::modules