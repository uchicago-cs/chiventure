add_library(ui
            src/coordinate.c
            src/DFS.c
            src/map.c
            src/print_functions.c
            src/ui.c
            src/ui_ctx.c
            src/window.c)

target_include_directories(ui PRIVATE src/)

target_link_libraries(ui ${CURSES_LIBRARIES})







