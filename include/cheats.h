#ifndef LIB_TP_CHEATS
#define LIB_TP_CHEATS

namespace Cheats {
    const int CHEAT_AMNT = 11;
    enum CheatId {
        Invincible,
        InvincibleEnemies,
        InfiniteAir,
        InfiniteOil,
        InfiniteBombs,
        InfiniteRupees,
        InfiniteArrows,
        MoonJump,
        Teleport,
        ReloadArea,
        FastRolling
    };

    struct Cheat {
        enum CheatId id;
        bool active;
    };
    
    void apply_cheats();
};  // namespace Cheats

#endif