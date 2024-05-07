#ifndef BATTLE_CORE_H
#define BATTLE_CORE_H
#define CharacterId int
#include "Character.h"
#include <array>
#include <list>
#include <memory>
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
    std::array<std::shared_ptr<Character>,
        playerMaxCount + monsterMaxCount>
        characters;
    std::list<CharacterId> actionSequence;
    std::list<CharacterId> appendATK;
    void tick(CharacterId character,
        int skillNum,
        std::vector<CharacterId> targets);
};

#endif