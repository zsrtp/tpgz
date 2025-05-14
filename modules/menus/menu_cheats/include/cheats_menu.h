#pragma once

#include "menus/menu.h"
#include "cheats.h"

#ifdef GCN_PLATFORM
#define CHEAT_AMNT 17
#define MOON_JUMP_TEXT "R+A"
#endif

#ifdef WII_PLATFORM
#define CHEAT_AMNT 18
#define MOON_JUMP_TEXT "Z+C+A"
#endif

enum CheatId {
    InfiniteAir,
    InfiniteArrows,
    InfiniteBombs,
    InfiniteHearts,
    InfiniteOil,
    InfiniteRupees,
    InfiniteSlingshot,
    Invincible,
    InvincibleEnemies,
    MoonJump,
    DoorStorage,
    SuperClawshot,
    UnrestrictedItems,
    TransformAnywhere,
    DisableItemTimer,
    FastIronBoots,
    FastTransform,
#ifdef WII_PLATFORM
    GaleLJA,
#endif
    SuperSpinner,
};

class CheatsMenu : public Menu {
public:
    CheatsMenu(Cursor&);
    virtual ~CheatsMenu();
    virtual void draw();

private:
    Line lines[CHEAT_AMNT];
};