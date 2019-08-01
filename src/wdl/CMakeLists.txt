project(wdl C)

add_library(wdl
            src/load_game.c
            src/load_item.c
            src/load_room.c
            src/parse.c
            src/validate.c)

target_include_directories(wdl PRIVATE src/)

# This is a temporary solution before the directories
# are reorganized
target_include_directories(wdl PRIVATE include/)
foreach(module ${CHIVENTURE_MODULES})
    target_include_directories(wdl PRIVATE ../${module}/include/)
endforeach(module)





