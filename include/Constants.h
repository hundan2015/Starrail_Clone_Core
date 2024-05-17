#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <cstddef>
#include <array>
#include <cstring>
#include <string>
#include "ConstantNameChinese.h"
#include "ConstantNameEnglish.h"

std::array<std::string, 100> skillStrings = {SKILL_FAREWELL_HIT,
                                             SKILL_RIP_HOME_RUN,
                                             SKILL_STAR_DUST_ACE_SINGLE,
                                             SKILL_STAR_DUST_ACE_MULTI,
                                             SKILL_ITS_MAGIC,
                                             SKILL_ONE_TIME_OFFER,
                                             SKILL_WHAT_ARE_YOU_LOOKING_AT,
                                             SKILL_TIRELESS_CHARGE};



std::array<std::string, 100> characterStrings = {
    CHARACTER_TRAIL_BLAZER_DESTRUCTION, CHARACTER_HERTA,
    CHARACTER_MOB_SILVERMANE_SOLDIER};


std::array<std::string, 100> buffStrings = {BUFF_KEEP_THE_BALL_ROLLING,
                                            BUFF_NO_ONE_CAN_BETRAY_ME,
                                            BUFF_DEFENCE_DECREASE};

constexpr int getSkillNameId(const char* name) {
    for (size_t i = 0; i < skillStrings.size(); ++i) {
        if (strcmp(name, skillStrings[i].data()) == 0) return i;
    }
    return -1;
}

constexpr int getCharacterNameId(const char* name) {
    for (size_t i = 0; i < characterStrings.size(); ++i) {
        if (strcmp(name, characterStrings[i].data()) == 0) return i;
    }
    return -1;
}

constexpr int getBuffNameId(const char* name) {
    for (size_t i = 0; i < buffStrings.size(); ++i) {
        if (strcmp(name, buffStrings[i].data()) == 0) return i;
    }
    return -1;
}

#endif