add_library(game-state
        src/game.c
        src/game_action.c
        src/item.c
        src/path.c
        src/player.c
        src/room.c)

target_link_libraries(game-state ${LUA_LIBRARIES})
target_include_directories(game-state PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(game-state PRIVATE src/)

