#ifndef TRAIL_BLAZER_PHYSIC_H
#define TRAIL_BLAZER_PHYSIC_H
#include "Character.h"
#include <array>

struct FarewellHit : public Skill {
    std::array<float, 7> percent = { 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
    FarewellHit()
    {
        name = "Farewell Hit";
    }
};

struct TrailBlazerPhysic : public Character {
    TrailBlazerPhysic()
    {
    }
};

#endif