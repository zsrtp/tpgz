#ifndef LIB_TP_CHEATS
#define LIB_TP_CHEATS

#define CHEAT_AMNT 16

namespace Cheats {
    enum CheatId {
        Invincible,
        InvincibleEnemies,
        InfiniteHearts,
        InfiniteAir,
        InfiniteOil,
        InfiniteBombs,
        InfiniteRupees,
        InfiniteArrows,
        InfiniteSlingshot,
        MoonJump,
        Teleport,
        SandHeightLoss,
        ReloadArea,
        FastMovement,
        FastBonk,
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