add_library(battle
	    src/battle_classes.c
	    src/battle_moves.c
            src/battle_state.c)

target_include_directories(battle PRIVATE src/)
