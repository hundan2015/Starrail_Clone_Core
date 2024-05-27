#include "Characters/TrailBlazerPhysic.h"

#include <cstddef>

#include "Character.h"
#include "Constants.h"
#include "utils.h"

FarewellHit::FarewellHit() {
    targetCount = 1;
    property = PHYSICAL;
    skillType = SKILL_NORMAL;
    skillGlobalId = getSkillNameId(SKILL_FAREWELL_HIT);
}
HitInfo FarewellHit::hit(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int attacker, int target) {
    return hitGeneral<PHYSICAL, 7>(percent, level, battleStates, attacker,
                                   target);
}
RipHomeRun::RipHomeRun() {
    targetCount = 3;
    property = PHYSICAL;
    skillType = SKILL_SKILL;
    skillGlobalId = getSkillNameId(SKILL_RIP_HOME_RUN);
}
HitInfo RipHomeRun::hit(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int attacker, int target) {
    return hitGeneral<PHYSICAL, 12>(percent, level, battleStates, attacker,
                                    target);
}

std::vector<int> RipHomeRun::getTargets(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int aim) {
    std::vector<int> targets{aim};
    for (int a = aim - 1; aim > playerMaxCount; aim--) {
        if (battleStates[a] != nullptr) {
            targets.push_back(a);
            break;
        }
    }
    for (int a = aim + 1; aim < battleStates.size(); aim++) {
        if (battleStates[a] != nullptr) {
            targets.push_back(a);
            break;
        }
    }
    return targets;
}

StardustAceSingle::StardustAceSingle() {
    targetCount = 1;
    property = PHYSICAL;
    skillType = SKILL_ULTIMATE;
    skillGlobalId = getSkillNameId(SKILL_STAR_DUST_ACE_SINGLE);
}
HitInfo StardustAceSingle::hit(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int attacker, int target) {
    return hitGeneral<PHYSICAL, 9>(percent, level, battleStates, attacker,
                                   target);
}
TrailBlazerPhysic::TrailBlazerPhysic() : Character() {
    characterGlobalId = getCharacterNameId(CHARACTER_TRAIL_BLAZER_DESTRUCTION);
    skills.push_back(std::make_unique<FarewellHit>());
    skills.push_back(std::make_unique<RipHomeRun>());
    skills.push_back(std::make_unique<StardustAceSingle>());

    basicCharacterProperty->hp = 163;
    basicCharacterProperty->attack = 84;
    basicCharacterProperty->defense = 62;
    basicCharacterProperty->speed = 100;
}
const std::array<float, 7> FarewellHit::percent = {0.5f, 0.6f, 0.7f, 0.8f,
                                                   0.9f, 1.0f, 1.1f};
const std::array<float, 12> RipHomeRun::percent = {
    0.625f,    0.6975f,  0.75f,     0.8125f, 0.875f,  0.9375f,
    1.015625f, 1.09375f, 1.171875f, 1.25f,   1.3125f, 1.375f};

const std::array<float, 9> StardustAceSingle::percent = {
    3.f, 3.15f, 3.3f, 3.45f, 3.6f, 3.75f, 3.937f, 4.125f, 4.312f};