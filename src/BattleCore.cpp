
#include <BattleCore.h>

#include <algorithm>
#include <memory>

#include "Character.h"
#include "iostream"

#ifdef DEBUG
#define debugOut(x) std::cout << x << std::endl;
#else
#define debugOut(x)
#endif

void BattleCore::tick(CharacterId attacker, int skillNum,
                      const std::vector<CharacterId>& targets) {
    if (battleCoreState == BEFORE_ATTACK ||
        battleCoreState == BEFORE_ULTIMATE) {
        // At this case, Agents takes control.
        doAttack(attacker, skillNum, targets);
    } else if (battleCoreState == BEFORE_APPEND) {
        // At this case, The system takes control. Parameters should be ignored.
        auto& appendATKSequence = appendATKs.front();
        doAttack(appendATKSequence.attacker, appendATKSequence.skillNum,
                 appendATKSequence.targets);
        appendATKs.pop_front();
    } else if (battleCoreState == BEFORE_ROUND) {
        // At this case, The system takes control. Parameters should be ignored.
        // TODO: Add some debuff.
        if (appendATKs.empty()) {
            battleCoreState = BEFORE_ATTACK;
            return;
        }
    }

    auto& hitInfos = getHitInfoInTick();
    for (auto& i : hitInfos) {
        characterBattleStates[i.target]->applyDamage(
            i.hpDamage, i.shelledDamage, i.weaknessDamage);
    }

    // Process append attacks.
    for (int i = 0; i < characters.size(); ++i) {
        auto attackerCharacter = characters[i];
        if (attackerCharacter == nullptr) continue;
        for (int j = 0; j < attackerCharacter->appendATKSkills.size(); ++j) {
            auto& appendATK = attackerCharacter->appendATKSkills[j];
            if (!appendATK->isPerform(characterBattleStates,
                                      originalCharacterProperty))
                continue;
            debugOut("Have appendATK!");
            appendATKs.push_front(
                appendATK->getBattleSequence(i, characterBattleStates));
        }
    }

    if (!appendATKs.empty()) {
        battleCoreState = BEFORE_APPEND;
    } else {
        battleCoreState = BEFORE_ROUND;
    }
}
void BattleCore::doAttack(int attacker, int skillNum,
                          const std::vector<int>& targets) {
    auto& attackerInfo = characterBattleStates[attacker];
    auto attackerCharacter = characters[attacker];
    for (auto& target : targets) {
        // TODO: Add some buffs to the attacker.
        auto& targetInfo = characterBattleStates[target];
        auto& skill = attackerCharacter->skills[skillNum];
        HitInfo result = skill->hit(attackerInfo.get(), targetInfo.get());
        // TODO: Add some recalls
        hitInfoInTick.push_back(result);
        if (targetInfo->getState() == CharacterBattleState::BROKEN) {
            // TODO: Add some broken damage.
        }
    }
}
const std::vector<HitInfo>& BattleCore::getHitInfoInTick() {
    return hitInfoInTick;
}
void BattleCore::resetHitInfoInTick() { hitInfoInTick.clear(); }
void BattleCore::initActionPoint() {
    judgeActionPoint = 10000.0f / (float)judgeSpeed;
    for (const auto& characterBattleState : characterBattleStates) {
        if (characterBattleState == nullptr) continue;
        float& actionPoint = characterBattleState->actionPoint;
        actionPoint =
            10000.0f / (float)(characterBattleState->characterProperty->speed);
    }
}
int BattleCore::getNextAction() {
    float minActionPoint = 25600;
    int minActionPointPosition{};
    const float initJudgeActionPoint = 10000.0f / (float)judgeSpeed;
    for (int i = 0; i < characterBattleStates.size(); ++i) {
        if (characterBattleStates[i] == nullptr) continue;
        float& actionPoint = characterBattleStates[i]->actionPoint;
        if (actionPoint < minActionPoint) {
            minActionPoint = actionPoint;
            minActionPointPosition = i;
        }
    }
    if (judgeActionPoint < minActionPoint) {
        turnCounter++;
        judgeActionPoint =
            ((initJudgeActionPoint + judgeActionPoint) - minActionPoint);
    }
    for (int i = 0; i < characterBattleStates.size(); ++i) {
        if (characterBattleStates[i] == nullptr) continue;
        float& actionPoint = characterBattleStates[i]->actionPoint;
        if (i == minActionPointPosition) {
            actionPoint =
                10000.0f /
                (float)(characterBattleStates[i]->characterProperty->speed);
            continue;
        }
        actionPoint -= minActionPoint;
    }
    return minActionPointPosition;
}
GameState BattleCore::getGameState() {
    bool isAlive = false;
    for (int i = 0; i < playerMaxCount; ++i) {
        if (characterBattleStates[i]->state != CharacterBattleState::DEAD) {
            isAlive = true;
            break;
        }
    }
    bool isEnemyAlive = false;
    for (int i = playerMaxCount; i < monsterMaxCount; ++i) {
        if (characterBattleStates[i]->state != CharacterBattleState::DEAD) {
            isEnemyAlive = true;
            break;
        }
    }
    if (isEnemyAlive && isAlive) return GOING;
    if (isEnemyAlive) return DEFEATED;
    return VICTORY;
}
