#ifndef BATTLE_CORE_H
#define BATTLE_CORE_H
#include <array>
#include <list>
#include <map>
#include <memory>
#include <tuple>
#include <vector>

#include "Character.h"

enum BattleCoreState {
    BEFORE_ROUND,
    BEFORE_ATTACK,
    BEFORE_APPEND,
    BEFORE_ULTIMATE,
};

enum GameState { VICTORY, DEFEATED, GOING };

struct BattleCore {
    static BattleCore& getInstance();
    BattleCoreState battleCoreState = BEFORE_ATTACK;
    std::array<std::unique_ptr<CharacterBattleState>,
               playerMaxCount + monsterMaxCount>
        characterBattleStates;
    std::array<const Character*, playerMaxCount + monsterMaxCount> characters =
        {};
    std::array<const CharacterProperty*, playerMaxCount + monsterMaxCount>
        originalCharacterProperty = {};
    std::list<BattleSequence> appendATKs;
    void tick(CharacterId attacker, int skillNum,
              const std::vector<CharacterId>& targets);
    const std::vector<HitInfo>& getHitInfoInTick();
    void resetHitInfoInTick();
    int turnCounter = 0;
    const int judgeSpeed = 100;
    float judgeActionPoint = 0;

    void initActionPoint();

    int getNextAction();

    GameState getGameState();

   private:
    BattleCore();
    ~BattleCore();

    std::vector<HitInfo> hitInfoInTick;
    void doAttack(int attacker, int skillNum, const std::vector<int>& targets);
};

#endif
