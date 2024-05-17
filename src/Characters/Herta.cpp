#include "Characters/Herta.h"

#include <array>

#include "BattleCore.h"
#include "Constants.h"
#include "utils.h"

std::vector<int> FineIWillDoItMyself::getTargets(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int aim) {
    std::vector<int> result;
    for (int i = playerMaxCount; i < battleStates.size(); ++i) {
        if (battleStates[i] != nullptr) result.push_back(i);
    }
    return result;
}
BattleSequence FineIWillDoItMyself::getBattleSequence(
    int attacker,
    std::array<std::unique_ptr<CharacterBattleState>, 9>& states) {
    return {attacker, 3, getTargets(states, 0)};
}
bool FineIWillDoItMyself::isPerform(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& states,
    std::array<const CharacterProperty*, 9>& originalCharacterProperty) {
    bool result = false;
    for (int i = playerMaxCount; i < states.size(); ++i) {
        if (states[i] == nullptr) continue;
        if (states[i]->characterProperty->hp <=
                0.5 * originalCharacterProperty[i]->hp &&
            !isPerformed[i]) {
            isPerformed[i] = true;
            result = true;
        } else if (states[i]->characterProperty->hp >=
                   0.5 * originalCharacterProperty[i]->hp) {
            isPerformed[i] = false;
        }
    }
    return result;
}
HitInfo FineIWillDoItMyself::hit(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int attacker, int target) {
    if (battleStates[attacker]->eidolonLevel >= 1) {
        bool isHaveBuff = false;
        for (auto& i : battleStates[attacker]->buffs) {
            if (i->buffGlobalId == getBuffNameId(BUFF_KEEP_THE_BALL_ROLLING)) {
                isHaveBuff = true;
                if (i->level < 5) {
                    i->level++;
                }
            }
        }
        if (!isHaveBuff) {
            battleStates[attacker]->buffs.push_back(
                std::make_unique<KeepTheBallRolling>());
        }
    }
    if (battleStates[attacker]->eidolonLevel >= 4) {
    }
    auto result =
        hitGeneral<ICE, 15>(percent, level, battleStates, attacker, target);
    if (battleStates[attacker]->eidolonLevel >= 4) {
        result.hpDamage = result.hpDamage * 1.1f;
    }
    return result;
}
FineIWillDoItMyself::FineIWillDoItMyself() {
    targetCount = 5;
    property = ICE;
    skillGlobalId = getSkillNameId(SKILL_FINE_I_WILL_DO_IT_MYSELF);
}
Herta::Herta() : Character() {
    characterGlobalId = getCharacterNameId(CHARACTER_HERTA);
    skills.push_back(std::make_unique<WhatAreYouLookingAt>());
    skills.push_back(std::make_unique<OneTimeOffer>());
    skills.push_back(std::make_unique<ItsMagic>());
    auto appendAtk = std::make_unique<FineIWillDoItMyself>();
    appendATKSkills.push_back(appendAtk.get());
    skills.push_back(std::move(appendAtk));

    basicCharacterProperty->hp = 129;
    basicCharacterProperty->attack = 79;
    basicCharacterProperty->defense = 54;
    basicCharacterProperty->speed = 100;
}
OneTimeOffer::OneTimeOffer() {
    targetCount = 1;
    property = ICE;
    skillGlobalId = getSkillNameId(SKILL_ONE_TIME_OFFER);
}
HitInfo OneTimeOffer::hit(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int attacker, int target) {
    return hitGeneral<ICE, 15>(percent, level, battleStates, attacker, target);
}
HitInfo WhatAreYouLookingAt::hit(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int attacker, int target) {
    auto result =
        hitGeneral<ICE, 9>(percent, level, battleStates, attacker, target);
    auto& battleCore = BattleCore::getInstance();

    if (battleStates[attacker]->eidolonLevel >= 1 &&
        battleStates[target]->characterProperty->hp <
            0.5 * battleCore.originalCharacterProperty[target]->hp) {
        result.hpDamage +=
            (int)(battleStates[attacker]->characterProperty->attack * 0.4);
    }
    return result;
}
WhatAreYouLookingAt::WhatAreYouLookingAt() {
    targetCount = 1;
    property = ICE;
    skillGlobalId = getSkillNameId(SKILL_WHAT_ARE_YOU_LOOKING_AT);
}
std::vector<int> ItsMagic::getTargets(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int aim) {
    std::vector<int> result;
    for (int i = playerMaxCount; i < battleStates.size(); ++i) {
        if (battleStates[i] != nullptr) result.push_back(i);
    }
    return result;
}
HitInfo ItsMagic::hit(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int attacker, int target) {
    if (battleStates[attacker]->eidolonLevel >= 6) {
        battleStates[attacker]->buffs.push_back(
            std::make_unique<NoOneCanBetrayMe>());
    }
    return hitGeneral<ICE, 15>(percent, level, battleStates, attacker, target);
}
ItsMagic::ItsMagic() {
    targetCount = 5;
    property = ICE;
    skillGlobalId = getSkillNameId(SKILL_ITS_MAGIC);
}
void NoOneCanBetrayMe::enhance(CharacterProperty& characterProperty) {
    characterProperty.attack *= 1.25f;
};
NoOneCanBetrayMe::NoOneCanBetrayMe() {
    type = BUFF;
    buffGlobalId = getBuffNameId(BUFF_NO_ONE_CAN_BETRAY_ME);
    isLong = false;
    life = 1;
}
KeepTheBallRolling::KeepTheBallRolling() {
    type = BUFF;
    isLong = true;
    buffGlobalId = getBuffNameId(BUFF_KEEP_THE_BALL_ROLLING);
    level = 1;
}
void KeepTheBallRolling::enhance(CharacterProperty& characterProperty) {
    characterProperty.criticalRate += (float)level * 0.03f;
};
const std::array<float, 15> ItsMagic::percent{1.2f,  1.28f, 1.36f, 1.44f, 1.52f,
                                              1.6f,  1.7f,  1.8f,  1.9f,  2.0f,
                                              2.08f, 2.16f, 2.24f, 2.32f, 2.4f};

const std::array<float, 9> WhatAreYouLookingAt::percent = {
    0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f};

const std::array<float, 15> OneTimeOffer::percent = {
    0.5f,   0.55f, 0.6f,  0.65f, 0.7f,  0.75f, 0.812f, 0.875f,
    0.937f, 1.0f,  1.05f, 1.1f,  1.15f, 1.2f,  1.25f};

const std::array<float, 15> FineIWillDoItMyself::percent{
        0.25f,  0.265f, 0.28f,  0.295f, 0.31f,  0.325f, 0.343f, 0.362f,
        0.381f, 0.4f,   0.415f, 0.43f,  0.445f, 0.46f,  0.475f};