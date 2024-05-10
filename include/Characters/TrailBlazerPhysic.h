#ifndef TRAIL_BLAZER_PHYSIC_H
#define TRAIL_BLAZER_PHYSIC_H
#include <array>
#include <memory>

#include "Character.h"
#include "Constants.h"

struct FarewellHit : public Skill {
    std::array<float, 7> percent = {0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f};
    FarewellHit() {
        targetCount = 1;
        property = PHYSICAL;
        skillGlobalId = getSkillNameId(SKILL_FAREWELL_HIT);
    }
    HitInfo hit(CharacterBattleState* attackerState,
                CharacterBattleState* attackedState) override {
        float p = percent[level];

        return {attackerState->characterLocalId,
                attackedState->characterLocalId,
                (int)(p * attackedState->characterProperty->attack), 0, 0};
    }
};

struct RipHomeRun : public Skill {
    std::array<float, 12> percent = {0.625f,    0.6975f, 0.75f,     0.8125f,
                                     0.875f,    0.9375f, 1.015625f, 1.09375f,
                                     1.171875f, 1.25f,   1.3125f,   1.375f};
    RipHomeRun() {
        targetCount = 3;
        property = PHYSICAL;
        skillGlobalId = getSkillNameId(SKILL_RIP_HOME_RUN);
    }

    HitInfo hit(CharacterBattleState* attackerState,
                CharacterBattleState* attackedState) override {
        float p = percent[level];
        return {attackerState->characterLocalId,
                attackedState->characterLocalId,
                (int)(p * attackedState->characterProperty->attack), 0, 0};
    }
};

struct TrailBlazerPhysic : public Character {
    TrailBlazerPhysic() : Character() {
        characterGlobalId = getCharacterNameId(CHARACTER_TRAIL_BLAZER);
        skills.push_back(std::make_unique<FarewellHit>());
        skills.push_back(std::make_unique<RipHomeRun>());
    }
};

#endif