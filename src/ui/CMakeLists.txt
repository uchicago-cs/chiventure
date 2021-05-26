add_library(ui
            src/coordinate.c
            src/DFS.c
            src/map.c
            src/print_functions.c
            src/ui.c
            src/ui_ctx.c
            src/window.c
            src/gui.c)

if (raylib_FOUND)
    target_sources(ui PRIVATE src/gui.c)
    target_link_libraries(ui raylib)
else()
    add_compile_definitions(GUI_AVAILABLE)
endif()

target_include_directories(ui PRIVATE src/)

target_link_libraries(ui ${CURSES_LIBRARIES})

add_subdirectory(examples
                EXCLUDE_FROM_ALL)
