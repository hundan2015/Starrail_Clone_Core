
#include "Character.h"
#include <BattleCore.h>
#include <algorithm>
#include <memory>

void BattleCore::tick(CharacterId character, int skillNum,
    std::vector<CharacterId> targets)
{
    if (battleCoreState != BEFORE_ROUND) {
        // Perform normal attack.
        std::shared_ptr<Character>& c = characters[character];
        const Skill* const targetSkill = c->skills[skillNum].get();
        for (auto& target : targets) {

            // TODO: Add some buffs to the character.
        }
        // TODO: Scan characters for append attack.
    } else {
        // TODO: Add some shit perform.
    }
}