#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>
#include <cstring>
#include <string>

#define SKILL_FAREWELL_HIT "再见安打"
#define SKILL_RIP_HOME_RUN "安息全垒打"

#define SKILL_ITS_MAGIC "是魔法，我加了魔法"
#define SKILL_ONE_TIME_OFFER "一锤子买卖"
#define SKILL_WHAT_ARE_YOU_LOOKING_AT "看什么看"
#define SKILL_FINE_I_WILL_DO_IT_MYSELF "还是我来吧"

#define CHARACTER_TRAIL_BLAZER "开拓者"
#define CHARACTER_HERTA "黑塔"
std::array<std::string, 100> skillStrings = {
    SKILL_FAREWELL_HIT,
    SKILL_RIP_HOME_RUN,
    "星辰王牌",
    SKILL_ITS_MAGIC,
    SKILL_ONE_TIME_OFFER,
    SKILL_WHAT_ARE_YOU_LOOKING_AT
};
std::array<std::string, 100> characterStrings = {
    CHARACTER_TRAIL_BLAZER,
    CHARACTER_HERTA
};

constexpr int getSkillNameId(const char* name)
{
    for (int i = 0; i < skillStrings.size(); ++i) {
        if (strcmp(name, skillStrings[i].data()) == 0)
            return i;
    }
    return -1;
}
constexpr int getCharacterNameId(const char* name)
{
    for (int i = 0; i < characterStrings.size(); ++i) {
        if (strcmp(name, characterStrings[i].data()) == 0)
            return i;
    }
    return -1;
}

#endif