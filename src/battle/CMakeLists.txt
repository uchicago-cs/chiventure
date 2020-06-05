add_library(battle
            src/battle_ai.c
            src/battle_logic.c
            src/battle_state.c
            src/battle_flow.c
            src/battle_flow_structs.c
            src/battle_moves.c
            src/battle_print.c
            src/battle_state.c)

target_include_directories(battle PRIVATE src/)
