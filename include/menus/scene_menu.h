#include "menu.h"

#define SCENE_AMNT 9
namespace Scene {
    enum SceneIndex {
        DISABLE_BG_INDEX,
        DISABLE_SFX_INDEX,
        FREEZE_ACTOR_INDEX,
        FREEZE_CAMERA_INDEX,
        HIDE_ACTOR_INDEX,
        HIDE_HUD_INDEX,
		FREEZE_TIME_INDEX,
        TIME_HOURS_INDEX,
        TIME_MINUTES_INDEX
    };

    struct SceneItem {
        enum SceneIndex id;
        bool active;
    };
}  // namespace Scene
extern Scene::SceneItem SceneItems[SCENE_AMNT];

class SceneMenu : public Menu {
public:
    SceneMenu() : Menu() {}
    static void render();
};