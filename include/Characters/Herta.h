//
// Created by Symbolic on 2024/5/10.
//

#ifndef STARRAIL_CORE_HERTA_H
#define STARRAIL_CORE_HERTA_H

#include "Character.h"
#include "Constants.h"
#include "utils.h"
struct ItsMagic : public Skill {
    std::array<float, 15> percent{1.2, 1.28, 1.36, 1.44, 1.52, 1.6,  1.7, 1.8,
                                  1.9, 2.0,  2.08, 2.16, 2.24, 2.32, 2.4};
    ItsMagic() {
        targetCount = 5;
        property = ICE;
        skillGlobalId = getSkillNameId(SKILL_ITS_MAGIC);
    }
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override {
        float p = percent[level];
        auto& attackerState = battleStates[attacker];
        auto& targetState = battleStates[target];

        return {attackerState->characterLocalId, targetState->characterLocalId,
                (int)(p * targetState->characterProperty->attack), 0, 0};
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
    std::array<float, 9> percent{0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3};
    WhatAreYouLookingAt() {
        targetCount = 1;
        property = ICE;
        skillGlobalId = getSkillNameId(SKILL_WHAT_ARE_YOU_LOOKING_AT);
    }
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override {
        float p = percent[level];
        auto& attackerState = battleStates[attacker];
        auto& targetState = battleStates[target];
        return {attackerState->characterLocalId, targetState->characterLocalId,
                (int)(p * targetState->characterProperty->attack), 0, 0};
    }
};

struct OneTimeOffer : public Skill {
    std::array<float, 15> percent{0.5,  0.55,  0.6,   0.65,  0.7,
                                  0.75, 0.812, 0.875, 0.937, 1.0,
                                  1.05, 1.1,   1.15,  1.2,   1.25};
    OneTimeOffer() {
        targetCount = 1;
        property = ICE;
        skillGlobalId = getSkillNameId(SKILL_ONE_TIME_OFFER);
    }
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override {
        float p = percent[level];
        auto& attackerState = battleStates[attacker];
        auto& targetState = battleStates[target];
        return {attackerState->characterLocalId, targetState->characterLocalId,
                (int)(p * targetState->characterProperty->attack), 0, 0};
    }
};

struct FineIWillDoItMyself : public AppendATK {
    std::array<float, 15> percent{0.25,  0.265, 0.28,  0.295, 0.31,
                                  0.325, 0.343, 0.362, 0.381, 0.4,
                                  0.415, 0.43,  0.445, 0.46,  0.475};
    std::array<bool, 9> isPerformed{false};
    FineIWillDoItMyself() {
        targetCount = 5;
        property = ICE;
        skillGlobalId = getSkillNameId(SKILL_FINE_I_WILL_DO_IT_MYSELF);
    }
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override {
        //        float p = percent[level];
        //        auto& attackerState = battleStates[attacker];
        //        auto& targetState = battleStates[target];
        //        return {attackerState->characterLocalId,
        //        targetState->characterLocalId,
        //                (int)(p * targetState->characterProperty->attack), 0,
        //                0};
        return hitGeneral<ICE, 15>(percent, level, battleStates, attacker,
                                   target);
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
