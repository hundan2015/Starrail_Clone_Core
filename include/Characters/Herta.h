//
// Created by Symbolic on 2024/5/10.
//

#ifndef STARRAIL_CORE_HERTA_H
#define STARRAIL_CORE_HERTA_H

#include "Character.h"
#include "Constants.h"
#include "utils.h"
struct KeepTheBallRolling : public Buff {
    KeepTheBallRolling() {
        isLong = true;
        buffGlobalId = getBuffNameId(BUFF_KEEP_THE_BALL_ROLLING);
        level = 1;
    }
    void enhance(CharacterProperty& characterProperty) override {
        characterProperty.criticalRate += (float)level * 0.03f;
    };
};

struct NoOneCanBetrayMe : public Buff {
    NoOneCanBetrayMe() {
        buffGlobalId = getBuffNameId(BUFF_NO_ONE_CAN_BETRAY_ME);
        life = 1;
    }
    void enhance(CharacterProperty& characterProperty) override {
        characterProperty.attack *= 1.25f;
    };
};

struct ItsMagic : public Skill {
    std::array<float, 15> percent{1.2f,  1.28f, 1.36f, 1.44f, 1.52f,
                                  1.6f,  1.7f,  1.8f,  1.9f,  2.0f,
                                  2.08f, 2.16f, 2.24f, 2.32f, 2.4f};
    ItsMagic() {
        targetCount = 5;
        property = ICE;
        skillGlobalId = getSkillNameId(SKILL_ITS_MAGIC);
    }
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override {
        if (battleStates[attacker]->eidolonLevel >= 6) {
            battleStates[attacker]->buffs.push_back(
                std::make_unique<NoOneCanBetrayMe>());
        }
        return hitGeneral<ICE, 15>(percent, level, battleStates, attacker,
                                   target);
    }
    std::vector<int> getTargets(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int aim) override {
        std::vector<int> result;
        for (int i = playerMaxCount; i < battleStates.size(); ++i) {
            if (battleStates[i] != nullptr) result.push_back(i);
        }
        return result;
    }
};

struct WhatAreYouLookingAt : public Skill {
    std::array<float, 9> percent{0.5f, 0.6f, 0.7f, 0.8f, 0.9f,
                                 1.0f, 1.1f, 1.2f, 1.3f};
    WhatAreYouLookingAt() {
        targetCount = 1;
        property = ICE;
        skillGlobalId = getSkillNameId(SKILL_WHAT_ARE_YOU_LOOKING_AT);
    }
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override {
        auto result =
            hitGeneral<ICE, 9>(percent, level, battleStates, attacker, target);
        auto& battleCore = BattleCore::getInstance();

        if (battleStates[attacker]->eidolonLevel >= 1 &&
            battleStates[target]->characterProperty->hp <
                0.5 * battleCore.originalCharacterProperty[target]->hp) {
            result.hpDamage +=
                (int)(battleStates[attacker]->characterProperty->attack * 0.4);
        }
        return result;
    }
};

struct OneTimeOffer : public Skill {
    std::array<float, 15> percent{0.5f,  0.55f,  0.6f,   0.65f,  0.7f,
                                  0.75f, 0.812f, 0.875f, 0.937f, 1.0f,
                                  1.05f, 1.1f,   1.15f,  1.2f,   1.25f};
    OneTimeOffer() {
        targetCount = 1;
        property = ICE;
        skillGlobalId = getSkillNameId(SKILL_ONE_TIME_OFFER);
    }
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override {
        return hitGeneral<ICE, 15>(percent, level, battleStates, attacker,
                                   target);
    }
};

struct FineIWillDoItMyself : public AppendATK {
    std::array<float, 15> percent{0.25f,  0.265f, 0.28f,  0.295f, 0.31f,
                                  0.325f, 0.343f, 0.362f, 0.381f, 0.4f,
                                  0.415f, 0.43f,  0.445f, 0.46f,  0.475f};
    std::array<bool, 9> isPerformed{false};
    FineIWillDoItMyself() {
        targetCount = 5;
        property = ICE;
        skillGlobalId = getSkillNameId(SKILL_FINE_I_WILL_DO_IT_MYSELF);
    }
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override {
        if (battleStates[attacker]->eidolonLevel >= 1) {
            bool isHaveBuff = false;
            for (auto& i : battleStates[attacker]->buffs) {
                if (i->buffGlobalId ==
                    getBuffNameId(BUFF_KEEP_THE_BALL_ROLLING)) {
                    isHaveBuff = true;
                    if (i->level < 5) {
                        i->level++;
                    }
                }
            }
            if (!isHaveBuff) {
                battleStates[attacker]->buffs.push_back(
                    std::make_unique<KeepTheBallRolling>());
            }
        }
        if (battleStates[attacker]->eidolonLevel >= 4) {
        }
        auto result =
            hitGeneral<ICE, 15>(percent, level, battleStates, attacker, target);
        if (battleStates[attacker]->eidolonLevel >= 4) {
            result.hpDamage = result.hpDamage * 1.1f;
        }
        return result;
    }
    bool isPerform(std::array<std::unique_ptr<CharacterBattleState>, 9>& states,
                   std::array<const CharacterProperty*, 9>&
                       originalCharacterProperty) override {
        bool result = false;
        for (int i = playerMaxCount; i < states.size(); ++i) {
            if (states[i] == nullptr) continue;
            if (states[i]->characterProperty->hp <=
                    0.5 * originalCharacterProperty[i]->hp &&
                !isPerformed[i]) {
                isPerformed[i] = true;
                result = true;
            } else if (states[i]->characterProperty->hp >=
                       0.5 * originalCharacterProperty[i]->hp) {
                isPerformed[i] = false;
            }
        }
        return result;
    }
    std::vector<int> getTargets(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int aim) override {
        std::vector<int> result;
        for (int i = playerMaxCount; i < battleStates.size(); ++i) {
            if (battleStates[i] != nullptr) result.push_back(i);
        }
        return result;
    }
    BattleSequence getBattleSequence(
        int attacker,
        std::array<std::unique_ptr<CharacterBattleState>, 9>& states) override {
        return {attacker, 3, getTargets(states, 0)};
    }
};
struct Herta : public Character {
    Herta() : Character() {
        characterGlobalId = getCharacterNameId(CHARACTER_HERTA);
        skills.push_back(std::make_unique<WhatAreYouLookingAt>());
        skills.push_back(std::make_unique<OneTimeOffer>());
        skills.push_back(std::make_unique<ItsMagic>());
        auto appendAtk = std::make_unique<FineIWillDoItMyself>();
        appendATKSkills.push_back(appendAtk.get());
        skills.push_back(std::move(appendAtk));

        basicCharacterProperty->hp = 129;
        basicCharacterProperty->attack = 79;
        basicCharacterProperty->defense = 54;
        basicCharacterProperty->speed = 100;
    }
};
#endif  // STARRAIL_CORE_HERTA_H
