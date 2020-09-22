#ifndef LIB_TP_CHEATS
#define LIB_TP_CHEATS

#define CHEAT_AMNT 12

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
        SuperSpinner
    };

    struct Cheat {
        enum CheatId id;
        bool active;
    };

    void apply_cheats();
};  // namespace Cheats

extern Cheats::Cheat CheatItems[CHEAT_AMNT];

//static Cheats::Cheat CheatItems[CHEAT_AMNT];

#endif