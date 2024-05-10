//
// Created by Symbolic on 2024/5/10.
//
#include <iostream>

#include "BattleCore.h"
#include "Characters/Herta.h"
#include "Characters/TrailBlazerPhysic.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void registerPlayerToBattleCore(BattleCore& battleCore, Character* character,
                                int pos) {
    battleCore.characters[pos] = character;
    battleCore.characterBattleStates[pos] =
        std::unique_ptr<CharacterBattleState>(
            character->getInitCharacterBattleState());
    auto tmp = new CharacterProperty;
    *tmp = character->getInitProperty();
    battleCore.originalCharacterProperty[pos] = tmp;
    battleCore.characterBattleStates[pos]->characterLocalId = pos;
}
int main() {
    BattleCore battleCore;
    // Add some players.
    auto p1 = std::make_unique<Character>(TrailBlazerPhysic());
    auto p2 = std::make_unique<Character>(TrailBlazerPhysic());
    auto p3 = std::make_unique<Character>(Herta());
    registerPlayerToBattleCore(battleCore, p1.get(), 0);
    registerPlayerToBattleCore(battleCore, p3.get(), 1);
    registerPlayerToBattleCore(battleCore, p2.get(), 4);

    battleCore.initActionPoint();
    int action = 0;
    int target;
    while (action != -1) {
        int nextActionCharacterId = battleCore.getNextAction();
        string name =
            characterStrings[battleCore.characters[nextActionCharacterId]
                                 ->characterGlobalId];
        cout << "当前行动角色ID:" << nextActionCharacterId << endl;
        cout << "名字:" << name;
        cin >> action >> target;
        battleCore.tick(nextActionCharacterId, action, {target});
        auto& hitInfos = battleCore.getHitInfoInTick();
        for (auto& i : hitInfos) {
            auto& targetCharacter = battleCore.characters[i.target];
            auto& targetCharacterState =
                battleCore.characterBattleStates[i.target];
            cout << name << "打了"
                 << characterStrings[targetCharacter->characterGlobalId]
                 << endl;
            cout << characterStrings[targetCharacter->characterGlobalId]
                 << " HP:" << targetCharacterState->characterProperty->hp
                 << endl;
        }
        if (battleCore.getGameState() != GOING) break;
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
                cout << tempName << "在追加攻击中打了"
                     << characterStrings[targetCharacter->characterGlobalId]
                     << endl;
                cout << characterStrings[targetCharacter->characterGlobalId]
                     << " HP:" << targetCharacterState->characterProperty->hp
                     << endl;
            }
            if (battleCore.getGameState() != GOING) break;
            battleCore.resetHitInfoInTick();
        }
    }
}