add_library(quests
            src/quests_state.c)

target_include_directories(quests PRIVATE src/)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)
