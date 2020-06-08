add_library(quests
        quests_state.c)

target_link_libraries(quests ${LUA_LIBRARIES})
target_include_directories(quests PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(quests PRIVATE src/)
