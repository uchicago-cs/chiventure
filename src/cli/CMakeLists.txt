project(cli C)

add_library(cli
            src/cmd.c
            src/operations.c
            src/parser.c
            src/shell.c)

target_include_directories(cli PRIVATE src/)

target_link_libraries(cli checkpointing)
target_link_libraries(cli action_management)
target_link_libraries(cli common)

# TODO: Checkpointing (which CLI depends on) uses a private header file
#       from game-state. See TODO in checkpointing CMakeLists.txt
target_include_directories(cli PRIVATE ../game-state/src/)

# This is a temporary solution before the directories
# are reorganized
target_include_directories(cli PRIVATE include/)
foreach(module ${CHIVENTURE_MODULES})
    target_include_directories(cli PRIVATE ../${module}/include/)
endforeach(module)





