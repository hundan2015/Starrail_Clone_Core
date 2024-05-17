#include "Characters/TrailBlazerPhysic.h"

#include "Constants.h"
#include "utils.h"

FarewellHit::FarewellHit() {
    targetCount = 1;
    property = PHYSICAL;
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
    skillGlobalId = getSkillNameId(SKILL_RIP_HOME_RUN);
}
HitInfo RipHomeRun::hit(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int attacker, int target) {
    return hitGeneral<PHYSICAL, 12>(percent, level, battleStates, attacker,
                                    target);
}
StardustAceSingle::StardustAceSingle() {
    targetCount = 1;
    property = PHYSICAL;
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
