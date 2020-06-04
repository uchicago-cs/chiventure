add_library(npc
            src/dialogue.c
            src/npc.c)

target_include_directories(npc PRIVATE src/)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)
                 