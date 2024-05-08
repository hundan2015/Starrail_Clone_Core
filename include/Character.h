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
    int hp = 0;
    int attack = 0;
    int defense = 0;
    int speed = 0;
    int weakness = 0;
    // Advance
    float criticalRate;
    float criticalDamage;
    float breakEffect;
    float outgoingHealingBoost;
    float energy;
    float energyRegenerationRate;
    float effectHitRate;
    float effectResist;
    // Property Damage
    float physicalDamage;
    float physicalResist;
    float fireDamage;
    float fireResist;
    float iceDamage;
    float iceResist;
    float lightningDamage;
    float lightningResist;
    float windDamage;
    float windResist;
    float quantumDamage;
    float quantumResist;
    float imaginaryDamage;
    float imaginaryResist;
    CharacterProperty operator+(const CharacterProperty& b)
    {
        CharacterProperty result;
        add(hp);
        add(attack);
        add(defense);
        add(speed);
        add(weakness);
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
    CharacterProperty operator*(const CharacterProperty& b)
    {
        CharacterProperty result;
        mult(hp);
        mult(attack);
        mult(defense);
        mult(speed);
        mult(weakness);
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
    enum RelicPlace {
        HEAD,
        HAND,
        BODY,
        FEET,
        BALL,
        STRING
    };
    int exp;
    int level;
    CharacterProperty enhance;
};

class LightCone {
public:
    int lightCoreGlobalId;
    int exp;
    int level;
    virtual void onBattleStart();
    virtual void onUltimate();
    virtual void onSkill();
    virtual void onBasicATK();
    CharacterProperty enhance;
};

struct Buff {
    enum BuffType {
        BUFF,
        DEBUFF
    };
    bool isVisible;
    bool isLong;
    BuffType type;
    int life;
    void update() { }
};

struct CharacterBattleState {
    enum CharacterState {
        NORMAL,
        PREPARE_FOR_APPEND_ATTACK,
        FROZEN,
        DEAD,
    };
    int characterGlobalId;
    CharacterState state;
    std::unique_ptr<CharacterProperty> characterProperty;
    std::vector<std::unique_ptr<Buff>> buffs;
    CharacterBattleState(int id, CharacterProperty basicCharacterProperty)
        : characterGlobalId(id)
        , characterProperty(std::make_unique<CharacterProperty>(basicCharacterProperty))
        , state(NORMAL)
    {
    }
};

struct HitInfo {
    int hpDamage;
    int weaknessDamage;
    int shelledDamage;
};

struct Skill {
    int skillGlobalId;
    int level;
    int targetCount;
    virtual HitInfo hit(CharacterBattleState* attackerState,
        CharacterBattleState* attackedState)
    {
        return { 0, 0, 0 };
    }
    virtual std::vector<Buff> getBuff(bool isFriend)
    {
        return std::vector<Buff>();
    }
};

struct AppendATK : public Skill {
    virtual bool isPerform() { return false; }
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
    std::vector<std::unique_ptr<AppendATK>> appendATKSkills;
    inline CharacterBattleState* getInitCharacterBattleState()
    {
        CharacterProperty property = *basicCharacterProperty;
        for (const auto& costume : costumes) {
            if (costume == nullptr)
                continue;
            property = property + costume->enhance;
        }
        property = property * lightCone->enhance;

        CharacterBattleState* result
            = new CharacterBattleState(characterGlobalId, property);
        return result;
    };
};

#endif