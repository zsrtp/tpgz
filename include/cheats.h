#ifndef LIB_TP_CHEATS
#define LIB_TP_CHEATS

namespace Cheats {
    enum CheatId {
        Blank,
        Blank2,
        Invincible,
        InvincibleEnemies,
        InfiniteHearts,
        InfiniteAir,
        InfiniteOil,
        InfiniteBombs,
        InfiniteRupees,
        InfiniteArrows,
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

#endif