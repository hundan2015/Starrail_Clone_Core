//
// Created by Symbolic on 2024/5/12.
//

#ifndef STARRAIL_CORE_COMMONBUFFS_H
#define STARRAIL_CORE_COMMONBUFFS_H
#include "Character.h"
#include "Constants.h"

struct DefenseDecrease : public Buff {
    float percent;
    DefenseDecrease(int lifeTime, float percent) : percent(percent) {
        life = lifeTime;
        type = DEBUFF;
        isVisible = true;
        isLong = false;
        buffGlobalId = getBuffNameId(BUFF_DEFENCE_DECREASE);
    }
    void enhance(CharacterProperty& characterProperty) override {
        characterProperty.defense *= percent;
    }
};

#endif  // STARRAIL_CORE_COMMONBUFFS_H
