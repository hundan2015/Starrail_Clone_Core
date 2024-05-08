#ifndef BATTLE_CORE_H
#define BATTLE_CORE_H
#include <vector>

#include "Character.h"
#include <array>
#include <list>
#include <memory>
#include <tuple>
const int playerMaxCount = 4;
const int monsterMaxCount = 5;

enum BattleCoreState {
    BEFORE_ROUND,
    BEFORE_ATTACK,
    BEFORE_APPEND,
    BEFORE_ULTIMATE,
};

struct BattleCore {
    BattleCoreState battleCoreState;
    std::array<std::unique_ptr<CharacterBattleState>,
        playerMaxCount + monsterMaxCount>
        characters;
    void tick(CharacterId character,
        int skillNum,
        std::vector<CharacterId> targets);
};

#endif