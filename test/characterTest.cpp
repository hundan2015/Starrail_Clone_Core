#include <iostream>

#include "Character.h"
#include "Characters/TrailBlazerPhysic.h"
using std::cout;
int main() {
    TrailBlazerPhysic c;
    auto battleState = c.getInitCharacterBattleState();
    cout << battleState->state;
    auto result = c.skills[0]->hit(battleState, battleState);
    cout << result.hpDamage;
}