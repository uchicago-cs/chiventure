add_library(game-state
        src/game.c
        src/game_action.c
        src/item.c
        src/path.c
        src/player.c
        src/room.c
        src/stats.c
        src/command.c
        src/condition.c)

target_include_directories(game-state PRIVATE src/)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)





