add_library(battle
            src/logic.c
            src/battle_state.c)

target_include_directories(battle PRIVATE src/)
