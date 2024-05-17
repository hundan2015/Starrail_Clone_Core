//
// Created by Symbolic on 2024/5/11.
//

#ifndef STARRAIL_CORE_UTILS_H
#define STARRAIL_CORE_UTILS_H

#include <cstdlib>
#include <ctime>

#include "Character.h"

#define PROPERTY_HIT_RATE(X, Y)                                    \
    template <>                                                    \
    float getPropertyHitRate<X>(CharacterProperty * attackerState, \
                                CharacterProperty * targetState) { \
        return attackerState->Y##Damage * targetState->Y##Resist;  \
    }

inline float getRandomNumber() {
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_real_distribution<float> dis(0.0, 1.0);
    // float random_number = dis(gen);
    srand((unsigned)time(nullptr));
    float random_number = (float)rand() / RAND_MAX;
    return random_number;
}

template <Property property>
float getPropertyHitRate(CharacterProperty* attackerState,
                         CharacterProperty* targetState) {
    return 1.0f;
}

template <Property property, size_t percent_size>
HitInfo hitGeneral(
    std::array<float, percent_size> percent, int level,
    std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
    int attacker, int target) {
    float p = percent[level];
    auto attackerCurrentProperty = battleStates[attacker]->getCurrentProperty();
    auto targetCurrentProperty = battleStates[target]->getCurrentProperty();
    float propertyRate = getPropertyHitRate<property>(&attackerCurrentProperty,
                                                      &targetCurrentProperty);
    float random = getRandomNumber();
    float critical = 1;
    const auto& targetDefense = targetCurrentProperty.defense;
    float defenseRate =
        1 - targetDefense / (targetDefense + 200 +
                             10.f * (float)battleStates[attacker]->level);
    if (random < attackerCurrentProperty.criticalRate) {
        critical += attackerCurrentProperty.criticalDamage;
    }
    float damageResult = propertyRate * p * critical *
                         attackerCurrentProperty.attack * defenseRate *
                         attackerCurrentProperty.damageDecrease;
    return {attacker, target, damageResult, 0, 0, critical > 1};
}

#endif  // STARRAIL_CORE_UTILS_H
