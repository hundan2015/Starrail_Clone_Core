//
// Created by Symbolic on 2024/5/11.
//

#ifndef STARRAIL_CORE_UTILS_H
#define STARRAIL_CORE_UTILS_H

#include <random>

#include "Character.h"

#define PROPERTY_HIT_RATE(X, Y)                                       \
    template <>                                                       \
    float getPropertyHitRate<X>(CharacterBattleState * attackerState, \
                                CharacterBattleState * targetState) { \
        return attackerState->getCurrentProperty().Y##Damage *        \
               targetState->getCurrentProperty().Y##Resist;           \
    }

template <Property property>
float getPropertyHitRate(CharacterBattleState* attackerState,
                         CharacterBattleState* targetState) {
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
    float propertyRate =
        getPropertyHitRate<property>(attackerState.get(), targetState.get());
    float random = getRandomNumber();
    float critical = 1;
    if (random < battleStates[attacker]->getCurrentProperty().criticalRate) {
        critical += battleStates[attacker]->getCurrentProperty().criticalDamage;
    }
    float damageResult = propertyRate * p * critical *
                             targetState->characterProperty->attack;
    return {attackerState->characterLocalId, targetState->characterLocalId,
            damageResult, 0, 0};
}

#endif  // STARRAIL_CORE_UTILS_H
