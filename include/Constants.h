#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>
#include <cstring>
#include <string>

std::array<std::string, 3> skillStrings = {
    "再见安打",
    "安息全垒打",
    "星辰王牌",
};
std::array<std::string, 3> characterStrings = {
    "开拓者",
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