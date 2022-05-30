add_library(battle
            src/battle_move_maker.c
            src/battle_ai.c
            src/battle_logic.c
            src/battle_state.c
            src/battle_flow.c
            src/battle_flow_structs.c
            src/battle_moves.c
            src/battle_state.c
            ../playerclass/examples/class-list.c
            src/battle_print.c
            src/battle_state.c
            src/battle_default_objects.c
	    src/battle_test_utility.c)

target_include_directories(battle PRIVATE src/)

target_link_libraries(battle m)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)
