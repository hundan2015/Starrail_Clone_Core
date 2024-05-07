#ifndef CHARACTER_H
#define CHARACTER_H
#include <array>
#include <iostream>
#include <memory>
#include <vector>

struct Buff {
    void doSomething() { }
};

struct CharacterProperty {
    // Basic
    int hp;
    int attack;
    int defense;
    int speed;
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
};

enum RelicPlace {
    HEAD,
    HAND,
    BODY,
    FEET,
    BALL,
    STRING
};

struct Relic {
    int exp;
    int level;
    CharacterProperty enhance;
};

class LightCone {
public:
    std::string name;
    int exp;
    int level;
    virtual void onBattleStart();
    virtual void onUltimate();
    virtual void onSkill();
    virtual void onBasicATK();
    CharacterProperty enhance;
};

enum CharacterState {
    NORMAL,
    PREPARE_FOR_APPEND_ATTACK,
    FROZEN,
    QUANTUM,
    DEAD,
};

class Character;

struct Skill {
    std::string name;
    virtual std::vector<Buff> hit(const CharacterProperty* hitterProperty,
        CharacterProperty* ownerProperty,
        CharacterState* ownerState) const
    {
        return std::vector<Buff>();
    }
};

class Character {
public:
    int level;
    int exp;
    CharacterState state;
    std::string name;
    std::unique_ptr<CharacterProperty> basicCharacterProperty;
    std::unique_ptr<CharacterProperty> characterProperty;
    std::unique_ptr<LightCone> lightCone;
    std::array<std::unique_ptr<Relic>, 6> costumes;
    std::vector<std::unique_ptr<Buff>> buffs;
    std::vector<std::unique_ptr<Skill>> skills;
};

#endif