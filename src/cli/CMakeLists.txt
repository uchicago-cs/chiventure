add_library(cli
            src/cmd.c
            src/operations.c
            src/parser.c
            src/shell.c)

target_link_libraries(cli ${LUA_LIBRARIES})
target_include_directories(cli PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(cli PRIVATE src/)

target_link_libraries(cli checkpointing)
target_link_libraries(cli action_management)
target_link_libraries(cli ui)
target_link_libraries(cli game-state)
target_link_libraries(cli common)

# TODO: Checkpointing (which CLI depends on) uses a private header file
#       from game-state. See TODO in checkpointing CMakeLists.txt
target_include_directories(cli PRIVATE ../game-state/src/)





