#include <iostream>

#include "BattleCore.h"
#include "Characters/TrailBlazerPhysic.h"
using std::cout;
int main() {
    TrailBlazerPhysic c;
    auto battleState = c.getInitCharacterBattleState();
    cout << battleState->state;
    auto result = c.skills[0]->hit(battleState, battleState);
    cout << result.hpDamage;
    // Battle core Test
    BattleCore battleCore;
    auto player1 = std::make_unique<TrailBlazerPhysic>(TrailBlazerPhysic());
    auto player2 = std::make_unique<TrailBlazerPhysic>(TrailBlazerPhysic());
    battleCore.characters[0] = player1.get();
    battleCore.characters[4] = player2.get();

    battleCore.characterBattleStates[0] = std::unique_ptr<CharacterBattleState>(
        player1->getInitCharacterBattleState());
    battleCore.characterBattleStates[0]->characterLocalId = 0;
    battleCore.characterBattleStates[4] = std::unique_ptr<CharacterBattleState>(
        player2->getInitCharacterBattleState());
    battleCore.characterBattleStates[4]->characterLocalId = 4;

    battleCore.tick(0, 0, std::vector<int>({4}));
    auto& hitInfos = battleCore.getHitInfoInTick();
    for (auto& i : hitInfos) {
        battleCore.characterBattleStates[i.target]->applyDamage(
            i.hpDamage, i.shelledDamage, i.weaknessDamage);
    }
    battleCore.resetHitInfoInTick();

}