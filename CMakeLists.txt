cmake_minimum_required(VERSION 3.6.0)
project(starrail_core VERSION 0.1.0 LANGUAGES C CXX)



include(CTest)
enable_testing()

add_executable(starrail_core main.cpp src/BattleCore.cpp
        include/Characters/Herta.h
        include/Characters/Monsters/SilvermaneSoldier.h
        )
add_executable(character_test test/characterTest.cpp src/BattleCore.cpp
        include/Characters/Herta.h
        include/Characters/Monsters/SilvermaneSoldier.h
        )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include_directories(./include)

enable_testing()
add_executable(battleCoreGameTest test/battleCoreMiniGame.cpp src/BattleCore.cpp
        include/Characters/Herta.h
        include/utils.h
        include/commonBuffs.h
        include/Characters/Monsters/SilvermaneSoldier.h
        )

# if(MSVC)
#   target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
# else()
#   target_compile_options(battleCoreGameTest PRIVATE -Wall -Wextra -Wpedantic -Werror)
# endif()