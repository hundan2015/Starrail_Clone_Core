
#include <BattleCore.h>
#include <memory>

void BattleCore::tick(CharacterId character, int skillNum,
    std::vector<CharacterId> targets)
{
    if (battleCoreState != BEFORE_ROUND) {
        // Perform normal attack.
        std::shared_ptr<Character>& c = characters[character];
        const Skill* const targetSkill = c->skills[skillNum].get();
        for (auto& target : targets) {
            std::shared_ptr<Character>& t = characters[target];
            auto buffs = targetSkill->hit(c->characterProperty.get(), t->characterProperty.get(),
                &t->state);
            // TODO: Add some buffs to the character.
        }
        // TODO: Scan characters for append attack.
        // TODO: Add some state transform.
    } else {
        // TODO: Add some shit perform.
    }
}