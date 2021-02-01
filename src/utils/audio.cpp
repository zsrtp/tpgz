#include "utils/audio.h"
#include "libtp_c/include/tp.h"

namespace Utilities {
void enable_bg_music() {
    tp_zelAudio.bg_audio = 1.0f;
#ifndef WII_PLATFORM
    tp_zelAudio.enemy_bg_music_volume = 1.0f;
    tp_zelAudio.hyrule_castle_bg_music_volume = 1.0f;
#endif
}

void disable_bg_music() {
    tp_zelAudio.bg_audio = 0.0f;
#ifndef WII_PLATFORM
    tp_zelAudio.enemy_bg_music_volume = 0.0f;
    tp_zelAudio.hyrule_castle_bg_music_volume = 0.0f;
#endif
}

void disable_sfx() {
    tp_zelAudio.enemy_sfx_volume = 0.0f;
    tp_zelAudio.env_sfx_volume = 0.0f;
    tp_zelAudio.item_recoil_sfx_volume = 0.0f;
    tp_zelAudio.item_sfx_volume = 0.0f;
    tp_zelAudio.link_idle_sfx_volume = 0.0f;
    tp_zelAudio.link_voice_volume = 0.0f;
    tp_zelAudio.menu_sfx_volume = 0.0f;
    tp_zelAudio.midna_sfx_volume = 0.0f;
    tp_zelAudio.npc_volume = 0.0f;
    tp_zelAudio.pause_button_volume = 0.0f;
}
void enable_sfx() {
    tp_zelAudio.enemy_sfx_volume = 1.0f;
    tp_zelAudio.env_sfx_volume = 1.0f;
    tp_zelAudio.item_recoil_sfx_volume = 1.0f;
    tp_zelAudio.item_sfx_volume = 1.0f;
    tp_zelAudio.link_idle_sfx_volume = 1.0f;
    tp_zelAudio.link_voice_volume = 1.0f;
    tp_zelAudio.menu_sfx_volume = 1.0f;
    tp_zelAudio.midna_sfx_volume = 1.0f;
    tp_zelAudio.npc_volume = 1.0f;
    tp_zelAudio.pause_button_volume = 1.0f;
}
}  // namespace Utilities