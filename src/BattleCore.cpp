
#include <BattleCore.h>

#include <algorithm>
#include <cstddef>
#include <memory>
#include <ostream>

#include "Character.h"
#include "Constants.h"
#include "iostream"

using std::cout;
using std::string;
// string endl = "\n";
using std::endl;

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
        for (auto& targetBuff : i.targetBuffs) {
            characterBattleStates[i.target]->buffs.push_back(
                std::make_unique<Buff>(targetBuff));
        }
        for (auto& selfBuff : i.selfBuffs) {
            characterBattleStates[i.attacker]->buffs.push_back(
                std::make_unique<Buff>(selfBuff));
        }
        characterBattleStates[i.target]->applyDamage(
            i.hpDamage, i.shelledDamage, i.weaknessDamage);
    }

    // Process append attacks.
    for (size_t i = 0; i < characters.size(); ++i) {
        auto attackerCharacter = characters[i];
        if (attackerCharacter == nullptr) continue;
        for (size_t j = 0; j < attackerCharacter->appendATKSkills.size(); ++j) {
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
        auto& targetInfo = characterBattleStates[target];
        auto& skill = attackerCharacter->skills[skillNum];
        HitInfo result = skill->hit(characterBattleStates, attacker, target);
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
    for (size_t i = 0; i < characterBattleStates.size(); ++i) {
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
    for (size_t i = 0; i < characterBattleStates.size(); ++i) {
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
BattleCore& BattleCore::getInstance() {
    static BattleCore battleCore;
    return battleCore;
}
BattleCore::BattleCore() {}
BattleCore::~BattleCore() {}

// TODO: Currently, this function have some part of front end. These code should
// be moved out.
void BattleCore::singleAction(int action, int target) {
    BattleCore& battleCore = BattleCore::getInstance();
    int nextActionCharacterId = battleCore.getNextAction();
    string name = characterStrings[battleCore.characters[nextActionCharacterId]
                                       ->characterGlobalId];
    cout << "Current action character id:" << nextActionCharacterId << endl;
    cout << "Name:" << name << endl;
    cout << "Skill Points:";
    for (int i = 0; i < skillPoint; ++i) {
        cout << "+";
    }
    cout << endl;
    if (battleCore.characterBattleStates[target] == nullptr) {
        cout << "Bad target!" << endl;
        return;
    }
    if (battleCore.characters[nextActionCharacterId]->skills[action] ==
        nullptr) {
        cout << "Bad action!" << endl;
        return;
    }

    if (nextActionCharacterId < playerMaxCount &&
        battleCore.characters[nextActionCharacterId]
                ->skills[action]
                ->skillType == Skill::SKILL_NORMAL) {
        battleCore.skillPoint++;
        battleCore.skillPoint =
            std::min(battleCore.skillPoint, battleCore.maxSkillPoint);
    }

    if (nextActionCharacterId < playerMaxCount &&
        battleCore.characters[nextActionCharacterId]
                ->skills[action]
                ->skillType == Skill::SKILL_SKILL) {
        if (battleCore.skillPoint < 0) {
            cout << "Not enough skill point!" << endl;
            return;
        }
        battleCore.skillPoint--;
    }

    battleCore.tick(nextActionCharacterId, action,
                    battleCore.characters[nextActionCharacterId]
                        ->skills[action]
                        ->getTargets(battleCore.characterBattleStates, target));
    auto& hitInfos = battleCore.getHitInfoInTick();
    for (auto& i : hitInfos) {
        auto& targetCharacter = battleCore.characters[i.target];
        auto& targetCharacterState = battleCore.characterBattleStates[i.target];
        string criticalString = i.isCritical ? ",critical!" : "";
        cout << name << " hit "
             << characterStrings[targetCharacter->characterGlobalId]
             << criticalString << endl;
        cout << characterStrings[targetCharacter->characterGlobalId]
             << " HP:" << targetCharacterState->characterProperty->hp << endl;
    }
    if (battleCore.getGameState() != GOING) return;
    battleCore.resetHitInfoInTick();

    if (battleCore.battleCoreState == BEFORE_APPEND) {
        auto appendATKInfo = battleCore.appendATKs.front();
        auto tempName = characterStrings[appendATKInfo.attacker];
        battleCore.tick(0, 0, {});
        auto& appendHitInfos = battleCore.getHitInfoInTick();
        for (auto& i : appendHitInfos) {
            auto& targetCharacter = battleCore.characters[i.target];
            auto& targetCharacterState =
                battleCore.characterBattleStates[i.target];
            string criticalString = i.isCritical ? ",critical!" : "";
            cout << tempName << " have a append hit on "
                 << characterStrings[targetCharacter->characterGlobalId]
                 << criticalString << endl;
            cout << characterStrings[targetCharacter->characterGlobalId]
                 << " HP:" << targetCharacterState->characterProperty->hp
                 << endl;
        }
        if (battleCore.getGameState() != GOING) return;
        battleCore.resetHitInfoInTick();
    }
    if (battleCore.battleCoreState == BEFORE_ROUND) {
        battleCore.tick(0, 0, {});
        auto& appendHitInfos = battleCore.getHitInfoInTick();
        for (auto& i : appendHitInfos) {
            auto& attacker = battleCore.characters[i.attacker];
            auto tempName = characterStrings[attacker->characterGlobalId];
            auto& targetCharacter = battleCore.characters[i.target];
            auto& targetCharacterState =
                battleCore.characterBattleStates[i.target];
            string criticalString = i.isCritical ? ",critical!" : "";
            cout << tempName << " have a before round hit on "
                 << characterStrings[targetCharacter->characterGlobalId]
                 << criticalString << endl;
            cout << characterStrings[targetCharacter->characterGlobalId]
                 << " HP:" << targetCharacterState->characterProperty->hp
                 << endl;
        }
        if (battleCore.getGameState() != GOING) return;
        battleCore.resetHitInfoInTick();
    }
}
