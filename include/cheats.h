#ifndef LIB_TP_CHEATS
#define LIB_TP_CHEATS

#ifdef WII_PLATFORM
#define CHEAT_AMNT 15
#else
#define CHEAT_AMNT 14
#endif

namespace Cheats {
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
#ifdef WII_PLATFORM
    GaleLJA,
#endif
    SuperSpinner,
};

struct Cheat {
    enum CheatId id;
    bool active;
};

void apply_cheats();
};  // namespace Cheats

extern Cheats::Cheat CheatItems[CHEAT_AMNT];

// static Cheats::Cheat CheatItems[CHEAT_AMNT];

#endif