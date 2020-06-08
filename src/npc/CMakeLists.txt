add_library(npc
            src/npc.c
            src/rooms-npc.c
            src/dialogue.c)

target_include_directories(npc PRIVATE src/)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)
                 