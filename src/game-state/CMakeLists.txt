project(game-state C)

add_library(game-state
        src/game.c
        src/game_action.c
        src/item.c
        src/path.c
        src/player.c
        src/room.c)

target_include_directories(game-state PRIVATE src/)

# This is a temporary solution before the directories
# are reorganized
target_include_directories(game-state PRIVATE include/)
foreach(module ${CHIVENTURE_MODULES})
    target_include_directories(game-state PRIVATE ../${module}/include/)
endforeach(module)





