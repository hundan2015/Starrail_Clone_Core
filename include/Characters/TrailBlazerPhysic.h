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
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override {
        return hitGeneral<PHYSICAL, 7>(percent, level, battleStates, attacker,
                                   target);
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

    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override {
        return hitGeneral<PHYSICAL, 12>(percent, level, battleStates, attacker,
                                   target);
    }
};

struct StardustAceSingle : public Skill {
    std::array<float, 9> percent = {3.f,   3.15f,  3.3f,   3.45f, 3.6f,
                                    3.75f, 3.937f, 4.125f, 4.312f};
    StardustAceSingle() {
        targetCount = 1;
        property = PHYSICAL;
        skillGlobalId = getSkillNameId(SKILL_STAR_DUST_ACE_SINGLE);
    }
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override {
        return hitGeneral<PHYSICAL, 9>(percent, level, battleStates, attacker,
                                   target);
    }
};

struct TrailBlazerPhysic : public Character {
    TrailBlazerPhysic() : Character() {
        characterGlobalId =
            getCharacterNameId(CHARACTER_TRAIL_BLAZER_DESTRUCTION);
        skills.push_back(std::make_unique<FarewellHit>());
        skills.push_back(std::make_unique<RipHomeRun>());
        skills.push_back(std::make_unique<StardustAceSingle>());

        basicCharacterProperty->hp = 163;
        basicCharacterProperty->attack = 84;
        basicCharacterProperty->defense = 62;
        basicCharacterProperty->speed = 100;
    }
};

#endif