add_library(quests
            src/quests_state.c)

target_link_libraries(quests ${LUA_LIBRARIES})
target_include_directories(quests PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(quests PRIVATE src/)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)
