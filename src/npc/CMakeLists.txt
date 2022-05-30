add_library(npc
            src/npc.c
            src/rooms_npc.c
            src/dialogue.c
            src/npc_move.c
            src/npc_quests.c
	    src/npc_battle.c)

target_include_directories(npc PRIVATE src/)
target_link_libraries(npc battle)
target_link_libraries(npc quests)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)
                 
