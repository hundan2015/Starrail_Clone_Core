#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>
#include <cstring>
#include <string>

#define SKILL_FAREWELL_HIT "再见安打"
#define SKILL_RIP_HOME_RUN "安息全垒打"
#define SKILL_STAR_DUST_ACE_SINGLE "星辰王牌_单体攻击"
#define SKILL_STAR_DUST_ACE_MULTI "星辰王牌_群体攻击"

#define SKILL_ITS_MAGIC "是魔法，我加了魔法"
#define SKILL_ONE_TIME_OFFER "一锤子买卖"
#define SKILL_WHAT_ARE_YOU_LOOKING_AT "看什么看"
#define SKILL_FINE_I_WILL_DO_IT_MYSELF "还是我来吧"

std::array<std::string, 100> skillStrings = {SKILL_FAREWELL_HIT,
                                             SKILL_RIP_HOME_RUN,
                                             SKILL_STAR_DUST_ACE_SINGLE,
                                             SKILL_STAR_DUST_ACE_MULTI,
                                             SKILL_ITS_MAGIC,
                                             SKILL_ONE_TIME_OFFER,
                                             SKILL_WHAT_ARE_YOU_LOOKING_AT};

#define CHARACTER_TRAIL_BLAZER_DESTRUCTION "开拓者-毁灭"
#define CHARACTER_HERTA "黑塔"

std::array<std::string, 100> characterStrings = {
    CHARACTER_TRAIL_BLAZER_DESTRUCTION, CHARACTER_HERTA};

#define BUFF_KEEP_THE_BALL_ROLLING "得胜必追击"
#define BUFF_NO_ONE_CAN_BETRAY_ME "世上没人能负我"
std::array<std::string, 100> buffStrings = {BUFF_KEEP_THE_BALL_ROLLING,
                                            BUFF_NO_ONE_CAN_BETRAY_ME};

constexpr int getSkillNameId(const char* name) {
    for (int i = 0; i < skillStrings.size(); ++i) {
        if (strcmp(name, skillStrings[i].data()) == 0) return i;
    }
    return -1;
}

constexpr int getCharacterNameId(const char* name) {
    for (int i = 0; i < characterStrings.size(); ++i) {
        if (strcmp(name, characterStrings[i].data()) == 0) return i;
    }
    return -1;
}

constexpr int getBuffNameId(const char* name) {
    for (int i = 0; i < buffStrings.size(); ++i) {
        if (strcmp(name, buffStrings[i].data()) == 0) return i;
    }
    return -1;
}

#endif