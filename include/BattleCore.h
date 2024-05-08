#ifndef BATTLE_CORE_H
#define BATTLE_CORE_H
#include <array>
#include <list>
#include <map>
#include <memory>
#include <tuple>
#include <vector>

#include "Character.h"
const int playerMaxCount = 4;
const int monsterMaxCount = 5;

enum BattleCoreState {
    BEFORE_ROUND,
    BEFORE_ATTACK,
    BEFORE_APPEND,
    BEFORE_ULTIMATE,
};

struct BattleCore {
    BattleCoreState battleCoreState = BEFORE_ATTACK;
    std::array<std::unique_ptr<CharacterBattleState>,
               playerMaxCount + monsterMaxCount>
        characterBattleStates;
    std::array<const Character*, playerMaxCount + monsterMaxCount> characters = {};
    std::list<BattleSequence> appendATKs;
    void tick(CharacterId attacker, int skillNum,
              const std::vector<CharacterId>& targets);
    const std::vector<HitInfo>& getHitInfoInTick();
    void resetHitInfoInTick();

   private:
    std::vector<HitInfo> hitInfoInTick;
    void doAttack(int attacker, int skillNum, const std::vector<int>& targets);
};

#endif