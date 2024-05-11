//
// Created by Symbolic on 2024/5/11.
//

#ifndef STARRAIL_CORE_UTILS_H
#define STARRAIL_CORE_UTILS_H

#include <random>

#include "Character.h"

#define PROPERTY_HIT_RATE(X, Y)                                       \
    template <>                                                       \
    float getPropertyHitRate<X>(CharacterProperty * attackerState, \
                                CharacterProperty * targetState) { \
        return attackerState->Y##Damage *        \
               targetState->Y##Resist;           \
    }

template <Property property>
float getPropertyHitRate(CharacterProperty* attackerState,
                         CharacterProperty* targetState) {
    return 1.0f;
}

PROPERTY_HIT_RATE(PHYSICAL, physical);
PROPERTY_HIT_RATE(ICE, ice);
PROPERTY_HIT_RATE(FIRE, fire);
PROPERTY_HIT_RATE(LIGHTNING, lightning);
PROPERTY_HIT_RATE(WIND, wind);
PROPERTY_HIT_RATE(QUANTUM, quantum);
PROPERTY_HIT_RATE(IMAGINARY, imaginary);

float getRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    float random_number = dis(gen);
    return random_number;
}

template <Property property, size_t percent_size>
HitInfo hitGeneral(
    std::array<float, percent_size> percent, int level,
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int attacker, int target) {
    float p = percent[level];
    auto& attackerState = battleStates[attacker];
    auto& targetState = battleStates[target];
    auto attackerCurrentProperty = battleStates[attacker]->getCurrentProperty();
    auto targetCurrentProperty = battleStates[target]->getCurrentProperty();
    float propertyRate = getPropertyHitRate<property>(&attackerCurrentProperty,
                                                      &targetCurrentProperty);
    float random = getRandomNumber();
    float critical = 1;

    if (random < attackerCurrentProperty.criticalRate) {
        critical += attackerCurrentProperty.criticalDamage;
    }
    float damageResult =
        propertyRate * p * critical * attackerCurrentProperty.attack;
    return {attackerState->characterLocalId, targetState->characterLocalId,
            damageResult, 0, 0};
}

#endif  // STARRAIL_CORE_UTILS_H
