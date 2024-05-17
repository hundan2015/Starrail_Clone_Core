//
// Created by Symbolic on 2024/5/12.
//

#ifndef STARRAIL_CORE_SILVERMANESOLDIER_H
#define STARRAIL_CORE_SILVERMANESOLDIER_H

#include "Character.h"

struct TirelessCharge : public Skill {
    TirelessCharge();
    HitInfo hit(
        // TODO : add energy gen
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
};

struct SilvermaneSolder : public Character {
    SilvermaneSolder();
};

#endif  // STARRAIL_CORE_SILVERMANESOLDIER_H
