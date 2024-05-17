//
// Created by Symbolic on 2024/5/10.
//

#ifndef STARRAIL_CORE_HERTA_H
#define STARRAIL_CORE_HERTA_H

#include "Character.h"

struct KeepTheBallRolling : public Buff {
    KeepTheBallRolling();
    void enhance(CharacterProperty& characterProperty) override;
};

struct NoOneCanBetrayMe : public Buff {
    NoOneCanBetrayMe();
    void enhance(CharacterProperty& characterProperty) override;
};

struct ItsMagic : public Skill {
    static const std::array<float, 15> percent;
    ItsMagic();
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
    std::vector<int> getTargets(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int aim) override;
};

struct WhatAreYouLookingAt : public Skill {
    static const std::array<float, 9> percent;
    WhatAreYouLookingAt();
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
};

struct OneTimeOffer : public Skill {
    static const std::array<float, 15> percent;
    OneTimeOffer();
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
};

struct FineIWillDoItMyself : public AppendATK {
    static const std::array<float, 15> percent;
    std::array<bool, 9> isPerformed{false};
    FineIWillDoItMyself();
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
    bool isPerform(std::array<std::unique_ptr<CharacterBattleState>, 9>& states,
                   std::array<const CharacterProperty*, 9>&
                       originalCharacterProperty) override;
    std::vector<int> getTargets(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int aim) override;
    BattleSequence getBattleSequence(
        int attacker,
        std::array<std::unique_ptr<CharacterBattleState>, 9>& states) override;
};
struct Herta : public Character {
    Herta();
};
#endif  // STARRAIL_CORE_HERTA_H
