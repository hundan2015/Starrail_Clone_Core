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
    static constexpr std::array<float, 15> percent{
        1.2f, 1.28f, 1.36f, 1.44f, 1.52f, 1.6f,  1.7f, 1.8f,
        1.9f, 2.0f,  2.08f, 2.16f, 2.24f, 2.32f, 2.4f};
    ItsMagic();
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
    std::vector<int> getTargets(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int aim) override;
};

struct WhatAreYouLookingAt : public Skill {
    static constexpr std::array<float, 9> percent{0.5f, 0.6f, 0.7f, 0.8f, 0.9f,
                                                  1.0f, 1.1f, 1.2f, 1.3f};
    WhatAreYouLookingAt();
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
};

struct OneTimeOffer : public Skill {
    static constexpr std::array<float, 15> percent{
        0.5f,   0.55f, 0.6f,  0.65f, 0.7f,  0.75f, 0.812f, 0.875f,
        0.937f, 1.0f,  1.05f, 1.1f,  1.15f, 1.2f,  1.25f};
    OneTimeOffer();
    HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) override;
};

struct FineIWillDoItMyself : public AppendATK {
    static constexpr std::array<float, 15> percent{
        0.25f,  0.265f, 0.28f,  0.295f, 0.31f,  0.325f, 0.343f, 0.362f,
        0.381f, 0.4f,   0.415f, 0.43f,  0.445f, 0.46f,  0.475f};
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
