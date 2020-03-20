#ifndef LIB_TP_CHEATS
#define LIB_TP_CHEATS

namespace Cheats {
    const int CHEAT_AMNT = 15;
    enum CheatId {
        Blank,
        Blank2,
        Invincible,
        InvincibleEnemies,
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
        FastBonk
    };

    struct Cheat {
        enum CheatId id;
        bool active;
    };
    
    void apply_cheats();
};  // namespace Cheats

#endif