add_library(game-state
        src/game.c
        src/game_action.c
        src/item.c
        src/mode.c
        src/path.c
        src/player.c
        src/room.c
        src/stats.c
        src/condition.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lpthread")

target_include_directories(game-state PRIVATE src/) 
target_link_libraries(game-state cli)
target_link_libraries(game-state npc)
target_link_libraries(game-state quests)
target_link_libraries(game-state Threads::Threads)
# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)





