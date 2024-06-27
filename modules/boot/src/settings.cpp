#include "settings.h"
#include <cstdio>
#include <algorithm>

ListMember g_font_opt[] = {"consola",   "calamity-bold",  "lib-sans",      "lib-sans-bold",
                           "lib-serif", "lib-serif-bold", "press-start-2p"};

bool g_swap_equips_flag;

tpgz::containers::deque<GZSettingEntry*> g_settings;

KEEP_FUNC void GZStng_add(GZSettingID id, void* data, size_t size) {
    auto it = g_settings.begin();
    for (; it != g_settings.end(); ++it) {
        if ((*it)->id == id) {
            break;
        }
    }
    if (it == g_settings.end()) {
        GZSettingEntry* entry = new GZSettingEntry{id, size, data};
        g_settings.push_back(entry);
    } else {
        GZSettingEntry* entry = *it;
        void* old_data = entry->data;
        delete[] (uint8_t*)old_data;
        entry->data = data;
        entry->size = size;
    }
}

KEEP_FUNC void GZStng_remove(GZSettingID id) {
    auto it = g_settings.begin();
    for (; it != g_settings.end(); ++it) {
        if ((*it)->id == id) {
            break;
        }
    }
    if (it != g_settings.end()) {
        auto* entry = *it;
        void* data = entry->data;
        delete[] (uint8_t*)data;
        g_settings.erase(it);
        delete entry;
    }
}

KEEP_FUNC GZSettingEntry* GZStng_get(GZSettingID id) {
    auto it = g_settings.begin();
    for (; it != g_settings.end(); ++it) {
        if ((*it)->id == id) {
            break;
        }
    }
    GZSettingEntry* entry = nullptr;
    if (it != g_settings.end()) {
        entry = *it;
    }
    return entry;
}

KEEP_FUNC tpgz::containers::deque<GZSettingID>* GZStng_getList() {
    auto list = new tpgz::containers::deque<GZSettingID>;
    list->resize(g_settings.size());
    std::transform(g_settings.begin(), g_settings.end(), list->begin(),
                   [](GZSettingEntry* entry) { return entry->id; });
    return list;
}

void GZ_initFont() {
    uint32_t fontType = GZStng_getData(STNG_FONT, 0);
    if (fontType >= 0 && fontType < FONT_OPTIONS_COUNT) {
        char buf[40] = {0};
        snprintf(buf, sizeof(buf), "tpgz/fonts/%s.fnt", g_font_opt[fontType].member);
        Font::loadFont(buf);
    }
}