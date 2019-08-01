project(common C)

add_library(common
            src/ctx.c
            src/sample_game.c)

target_include_directories(common PRIVATE src/)

target_link_libraries(common cli)

# This is a temporary solution before the directories
# are reorganized
target_include_directories(common PRIVATE include/)
foreach(module ${CHIVENTURE_MODULES})
    target_include_directories(common PRIVATE ../${module}/include/)
endforeach(module)





