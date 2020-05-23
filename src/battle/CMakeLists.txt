add_library(battle
            src/battle_state.c
            src/battle_flow.c
            src/battle_structs.c)

target_include_directories(battle PRIVATE src/)
