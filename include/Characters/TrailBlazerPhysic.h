#ifndef TRAIL_BLAZER_PHYSIC_H
#define TRAIL_BLAZER_PHYSIC_H
#include <array>
#include <memory>

#include "Character.h"


struct FarewellHit : public Skill {
    static constexpr std::array<float, 7> percent = {0.5f, 0.6f, 0.7f, 0.8f,
                                                     0.9f, 1.0f, 1.1f};
    FarewellHit();
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
};

struct RipHomeRun : public Skill {
    static constexpr std::array<float, 12> percent = {
        0.625f,    0.6975f,  0.75f,     0.8125f, 0.875f,  0.9375f,
        1.015625f, 1.09375f, 1.171875f, 1.25f,   1.3125f, 1.375f};
    RipHomeRun();

    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
};

struct StardustAceSingle : public Skill {
    static constexpr std::array<float, 9> percent = {
        3.f, 3.15f, 3.3f, 3.45f, 3.6f, 3.75f, 3.937f, 4.125f, 4.312f};
    StardustAceSingle();
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
};

struct TrailBlazerPhysic : public Character {
    TrailBlazerPhysic();
};

#endif