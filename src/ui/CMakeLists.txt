add_library(ui
            src/coordinate.c
            src/DFS.c
            src/map.c
            src/print_functions.c
            src/ui.c
            src/ui_ctx.c
            src/window.c)

target_link_libraries(ui ${LUA_LIBRARIES})
target_include_directories(ui PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(ui PRIVATE src/)

target_link_libraries(ui ${CURSES_LIBRARIES})

# TODO: Checkpointing (which UI depends on) uses a private header file
#       from game-state. See TODO in checkpointing CMakeLists.txt
target_include_directories(ui PRIVATE ../game-state/src/)






