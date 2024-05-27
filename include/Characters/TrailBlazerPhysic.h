#ifndef TRAIL_BLAZER_PHYSIC_H
#define TRAIL_BLAZER_PHYSIC_H
#include <array>
#include <memory>

#include "Character.h"

struct FarewellHit : public Skill {
    static const std::array<float, 7> percent;
    FarewellHit();
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
};

struct RipHomeRun : public Skill {
    static const std::array<float, 12> percent;
    RipHomeRun();

    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
    std::vector<int> getTargets(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int aim) override;
};

struct StardustAceSingle : public Skill {
    static const std::array<float, 9> percent;
    StardustAceSingle();
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
};

struct TrailBlazerPhysic : public Character {
    TrailBlazerPhysic();
};

#endif