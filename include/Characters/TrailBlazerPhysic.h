#ifndef TRAIL_BLAZER_PHYSIC_H
#define TRAIL_BLAZER_PHYSIC_H
#include <array>
#include <memory>

#include "Character.h"
#include "Constants.h"

struct FarewellHit : public Skill {
    std::array<float, 7> percent = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1};
    FarewellHit() {
        targetCount = 1;
        skillGlobalId = getSkillNameId("再见安打");
    }
    HitInfo hit(CharacterBattleState* attackerState,
                CharacterBattleState* attackedState) override {
        float p = percent[level];

        return {(int)(p * attackedState->characterProperty->attack), 0, 0};
    }
};

struct RipHomeRun : public Skill {
    std::array<float, 12> percent = {0.625,    0.6975, 0.75,     0.8125,
                                     0.875,    0.9375, 1.015625, 1.09375,
                                     1.171875, 1.25,   1.3125,   1.375};
    RipHomeRun() {
        targetCount = 3;
        skillGlobalId = getSkillNameId("安息全垒打");
    }

    HitInfo hit(CharacterBattleState* attackerState,
                CharacterBattleState* attackedState) override {
        float p = percent[level];
        return {(int)(p * attackedState->characterProperty->attack), 0, 0};
    }
};

struct TrailBlazerPhysic : public Character {
    TrailBlazerPhysic() : Character() {
        characterGlobalId = getCharacterNameId("开拓者");
        skills.push_back(std::make_unique<FarewellHit>());
        skills.push_back(std::make_unique<RipHomeRun>());
    }
};

#endif