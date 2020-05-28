add_library(npc
            src/dialogue.c
            src/npc.c)

target_include_directories(npc PRIVATE src/)
target_include_directories(npc PRIVATE ${CMAKE_SOURCE_DIR}/src/game-state/src/)


