//
// Created by Symbolic on 2024/5/11.
//

#ifndef STARRAIL_CORE_UTILS_H
#define STARRAIL_CORE_UTILS_H

#include "Character.h"

#define PROPERTY_HIT_RATE(X, Y)                                       \
    template <>                                                       \
    float getPropertyHitRate<X>(CharacterBattleState * attackerState, \
                                CharacterBattleState * targetState) { \
        return attackerState->characterProperty->Y##Damage *          \
               targetState->characterProperty->Y##Resist;             \
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
    int damageResult =
        (int)(propertyRate * p * (float)targetState->characterProperty->attack);
    return {attackerState->characterLocalId, targetState->characterLocalId,
            damageResult, 0, 0};
}

#endif  // STARRAIL_CORE_UTILS_H
