#include "Character.h"

void Skill::initState() {}
std::vector<int> Skill::getTargets(
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int aim) {
    return {aim};
}
CharacterProperty CharacterBattleState::getCurrentProperty() {
    auto result = *characterProperty;
    for (auto& i : buffs) {
        i->enhance(result);
    }
    return result;
}
CharacterBattleState::CharacterState CharacterBattleState::getState() const {
    return state;
}
void CharacterBattleState::applyDamage(float hpDamage, float shelledDamage,
                                       float weaknessDamage) {
    characterProperty->hp -= hpDamage;
    characterProperty->shelled -= shelledDamage;
    characterProperty->toughness -= weaknessDamage;
    if (characterProperty->hp <= 0) {
        state = DEAD;
        return;
    }
    if (characterProperty->toughness <= 0) {
        state = BROKEN;
    }
}
CharacterBattleState::CharacterBattleState(
    int localId, int globalId, CharacterProperty basicCharacterProperty)
    : characterLocalId(localId),
      characterGlobalId(globalId),
      characterProperty(
          std::make_unique<CharacterProperty>(basicCharacterProperty)),
      state(NORMAL) {}
void Buff::enhance(CharacterProperty& characterProperty) {}
void Buff::update() {}
Character::Character() {
    level = 1;
    exp = 0;
    characterGlobalId = 0;
    basicCharacterProperty =
        std::make_unique<CharacterProperty>(CharacterProperty());
    basicCharacterProperty->criticalRate = 0.5;
    basicCharacterProperty->criticalDamage = 0.5;
}
CharacterBattleState* Character::getInitCharacterBattleState() {
    CharacterProperty property = getInitProperty();

    auto result = new CharacterBattleState(-1, characterGlobalId, property);
    result->weakpoints = weakpoints;
    result->eidolonLevel = eidolonLevel;
    result->level = level;
    return result;
}
CharacterProperty Character::getInitProperty() {
    CharacterProperty property = *basicCharacterProperty;
    for (const auto& costume : costumes) {
        if (costume == nullptr) continue;
        costume->enhance(property);
    }
    if (lightCone != nullptr) lightCone->enhance(property);
    return property;
};