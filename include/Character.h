#ifndef CHARACTER_H
#define CHARACTER_H

#define CharacterId int

#include <array>
#include <list>
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
    float hp = 100;
    float attack = 100;
    float defense = 100;
    float speed = 100;
    float toughness = 1;
    float shelled = 0;
    float damageDecrease = 1;
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
};

struct Relic {
    enum RelicPlace { HEAD, HAND, BODY, FEET, BALL, STRING };
    int exp{};
    int level{};
    virtual void enhance(CharacterProperty& characterProperty) = 0;
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
    virtual void enhance(CharacterProperty& characterProperty) = 0;
};

struct Buff {
    enum BuffType { BUFF, DEBUFF };
    bool isVisible{};
    bool isLong = false;
    BuffType type{BUFF};
    int life{};
    int level{};
    int buffGlobalId{};
    virtual void enhance(CharacterProperty& characterProperty);
    void update();
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
    int eidolonLevel{};
    float actionPoint{};
    int level = 1;
    CharacterState state;
    std::unique_ptr<CharacterProperty> characterProperty;
    std::list<std::unique_ptr<Buff>> buffs = {};
    std::vector<Property> weakpoints = {};
    CharacterBattleState(int localId, int globalId,
                         CharacterProperty basicCharacterProperty);

    void applyDamage(float hpDamage, float shelledDamage, float weaknessDamage);
    CharacterState getState() const;
    CharacterProperty getCurrentProperty();
};

struct HitInfo {
    int attacker;
    int target;
    float hpDamage;
    float weaknessDamage;
    float shelledDamage;
    bool isCritical = false;
    std::vector<Buff> selfBuffs{};
    std::vector<Buff> targetBuffs{};
};

struct Skill {
    Property property = PHYSICAL;
    int skillGlobalId = 0;
    int level = 0;
    int targetCount = 0;
    virtual HitInfo hit(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int attacker, int target) = 0;
    virtual std::vector<int> getTargets(
        std::array<std::unique_ptr<CharacterBattleState>, 9>& battleStates,
        int aim);
    virtual void initState();
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
    int eidolonLevel{};
    std::unique_ptr<CharacterProperty> basicCharacterProperty;
    std::unique_ptr<LightCone> lightCone;
    std::array<std::unique_ptr<Relic>, 6> costumes;
    std::vector<std::unique_ptr<Skill>> skills;
    std::vector<AppendATK*> appendATKSkills;
    std::vector<Property> weakpoints;
    Character();
    CharacterBattleState* getInitCharacterBattleState();
    CharacterProperty getInitProperty();
};

#endif