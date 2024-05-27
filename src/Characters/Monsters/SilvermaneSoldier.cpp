#include "Characters/Monsters/SilvermaneSoldier.h"
#include "Character.h"
#include "Constants.h"
#include "commonBuffs.h"
#include "utils.h"

TirelessCharge::TirelessCharge() {
    targetCount = 1;
    property = PHYSICAL;
    skillType = SKILL_NORMAL;
    skillGlobalId = getSkillNameId(SKILL_TIRELESS_CHARGE);
}
HitInfo TirelessCharge::hit(
    // TODO : add energy gen
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int attacker, int target) {
    auto result =
        hitGeneral<PHYSICAL, 1>({1}, 0, battleStates, attacker, target);
    result.targetBuffs.push_back(DefenseDecrease(2, 0.5));
    return result;
}
SilvermaneSolder::SilvermaneSolder() : Character() {
    characterGlobalId = getCharacterNameId(CHARACTER_MOB_SILVERMANE_SOLDIER);

    skills.push_back(std::make_unique<TirelessCharge>());

    basicCharacterProperty->criticalRate = 0;

    basicCharacterProperty->hp = 97;
    basicCharacterProperty->attack = 12;
    basicCharacterProperty->defense = 210;
    basicCharacterProperty->speed = 83;

    basicCharacterProperty->physicalResist = 0.2f;
    basicCharacterProperty->fireResist = 0.2f;
    basicCharacterProperty->iceResist = 0.4f;
    basicCharacterProperty->lightningResist = 0.2f;
    basicCharacterProperty->windResist = 0.0f;
    basicCharacterProperty->quantumResist = 0.0f;
    basicCharacterProperty->imaginaryResist = 0.2f;

    basicCharacterProperty->effectResist = 0.1f;
}
