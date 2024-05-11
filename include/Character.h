#ifndef CHARACTER_H
#define CHARACTER_H

#include <cstddef>
#define CharacterId int

#define add(x) result.x = this->x + b.x;
#define mult(x) result.x = this->x * (b.x + 1);

#include <array>
#include <iostream>
#include <memory>
#include <vector>

const int playerMaxCount = 4;
const int monsterMaxCount = 5;

enum Property {
    PHYSICAL,
    FIRE,
    ICE,
    LIGHTNING,
    WIND,
    QUANTUM,
    IMAGINARY,
};

struct CharacterProperty {
    // Basic
    int hp = 100;
    int attack = 100;
    int defense = 100;
    int speed = 100;
    int weakness = 1;
    int shelled = 0;
    // Advance
    float criticalRate{};
    float criticalDamage{};
    float breakEffect{};
    float outgoingHealingBoost{};
    float energy{};
    float energyRegenerationRate{};
    float effectHitRate{};
    float effectResist{};
    // Property Damage
    float physicalDamage{1};
    float physicalResist{1};
    float fireDamage{1};
    float fireResist{1};
    float iceDamage{1};
    float iceResist{1};
    float lightningDamage{1};
    float lightningResist{1};
    float windDamage{1};
    float windResist{1};
    float quantumDamage{1};
    float quantumResist{1};
    float imaginaryDamage{1};
    float imaginaryResist{1};
    CharacterProperty operator+(const CharacterProperty& b) const {
        CharacterProperty result;
        add(hp);
        add(attack);
        add(defense);
        add(speed);
        add(weakness);
        add(shelled);
        // Advance
        add(criticalRate);
        add(criticalDamage);
        add(breakEffect);
        add(outgoingHealingBoost);
        add(energy);
        add(energyRegenerationRate);
        add(effectHitRate);
        add(effectResist);
        // Property Damage
        add(physicalDamage);
        add(physicalResist);
        add(fireDamage);
        add(fireResist);
        add(iceDamage);
        add(iceResist);
        add(lightningDamage);
        add(lightningResist);
        add(windDamage);
        add(windResist);
        add(quantumDamage);
        add(quantumResist);
        add(imaginaryResist);
        add(imaginaryDamage);
        return result;
    }
    CharacterProperty operator*(const CharacterProperty& b) {
        CharacterProperty result;
        mult(hp);
        mult(attack);
        mult(defense);
        mult(speed);
        mult(weakness);
        mult(shelled);
        // Advance
        mult(criticalRate);
        mult(criticalDamage);
        mult(breakEffect);
        mult(outgoingHealingBoost);
        mult(energy);
        mult(energyRegenerationRate);
        mult(effectHitRate);
        mult(effectResist);
        // Property Damage
        mult(physicalDamage);
        mult(physicalResist);
        mult(fireDamage);
        mult(fireResist);
        mult(iceDamage);
        mult(iceResist);
        mult(lightningDamage);
        mult(lightningResist);
        mult(windDamage);
        mult(windResist);
        mult(quantumDamage);
        mult(quantumResist);
        mult(imaginaryResist);
        mult(imaginaryDamage);
        return result;
    }
};

struct Relic {
    enum RelicPlace { HEAD, HAND, BODY, FEET, BALL, STRING };
    int exp{};
    int level{};
    CharacterProperty enhance;
};

class LightCone {
   public:
    int lightCoreGlobalId{};
    int exp{};
    int level{};
    virtual void onBattleStart() = 0;
    virtual void onUltimate() = 0;
    virtual void onSkill() = 0;
    virtual void onBasicATK() = 0;
    CharacterProperty enhance;
};

struct Buff {
    enum BuffType { BUFF, DEBUFF };
    bool isVisible;
    bool isLong;
    BuffType type;
    int life;
    void update() {}
};

struct CharacterBattleState {
    enum CharacterState {
        NORMAL,
        PREPARE_FOR_APPEND_ATTACK,
        FROZEN,
        DEAD,
        BROKEN
    };
    int characterLocalId;
    int characterGlobalId;
    float actionPoint{};
    CharacterState state;
    std::unique_ptr<CharacterProperty> characterProperty;
    std::vector<std::unique_ptr<Buff>> buffs = {};
    std::vector<Property> weakpoints = {};
    CharacterBattleState(int localId, int globalId,
                         CharacterProperty basicCharacterProperty)
        : characterLocalId(localId),
          characterGlobalId(globalId),
          characterProperty(
              std::make_unique<CharacterProperty>(basicCharacterProperty)),
          state(NORMAL) {}

    void applyDamage(int hpDamage, int shelledDamage, int weaknessDamage) {
        characterProperty->hp -= hpDamage;
        characterProperty->shelled -= shelledDamage;
        characterProperty->weakness -= weaknessDamage;
        if (characterProperty->hp <= 0) {
            state = DEAD;
            return;
        }
        if (characterProperty->weakness <= 0) {
            state = BROKEN;
        }
    }
    CharacterState getState() const { return state; }
};

struct HitInfo {
    int attacker;
    int target;
    int hpDamage;
    int weaknessDamage;
    int shelledDamage;
};

struct Skill {
    Property property = PHYSICAL;
    int skillGlobalId = 0;
    int level = 0;
    int targetCount = 0;
    virtual HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) {
        return {0, 0, 0, 0, 0};
    }
    virtual std::vector<Buff> getBuff(bool isFriend) { return {}; }
    virtual std::vector<int> getTargets(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int aim) {
        return {aim};
    }
    virtual void initState() {}
};

struct BattleSequence {
    int attacker;
    int skillNum;
    std::vector<CharacterId> targets;
};

struct AppendATK : public Skill {
    virtual bool isPerform(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& states,
        std::array<const CharacterProperty*, 9>& characters) {
        return false;
    }
    virtual BattleSequence getBattleSequence(
        int attacker,
        std::array<std::unique_ptr<CharacterBattleState>, 9>& states) {
        return {};
    }
};

class Character {
   public:
    int level;
    int exp;
    int characterGlobalId;
    std::unique_ptr<CharacterProperty> basicCharacterProperty;
    std::unique_ptr<LightCone> lightCone;
    std::array<std::unique_ptr<Relic>, 6> costumes;
    std::vector<std::unique_ptr<Skill>> skills;
    std::vector<AppendATK*> appendATKSkills;
    std::vector<Property> weakpoints;
    Character() {
        level = 1;
        exp = 0;
        characterGlobalId = 0;
        basicCharacterProperty =
            std::make_unique<CharacterProperty>(CharacterProperty());
    }
    inline CharacterBattleState* getInitCharacterBattleState() {
        CharacterProperty property = getInitProperty();

        auto result = new CharacterBattleState(-1, characterGlobalId, property);
        result->weakpoints = weakpoints;
        return result;
    }
    CharacterProperty getInitProperty() {
        CharacterProperty property = *basicCharacterProperty;
        for (const auto& costume : costumes) {
            if (costume == nullptr) continue;
            property = property + costume->enhance;
        }
        if (lightCone != nullptr) property = property * lightCone->enhance;
        return property;
    };
};

#endif