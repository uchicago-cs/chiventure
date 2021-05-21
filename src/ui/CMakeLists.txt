if (raylib_FOUND)

    add_library(ui
                src/coordinate.c
                src/DFS.c
                src/map.c
                src/print_functions.c
                src/ui.c
                src/ui_ctx.c
                src/window.c
                src/gui.c)

    target_include_directories(ui PRIVATE src/)

    target_link_libraries(ui ${CURSES_LIBRARIES})
    target_link_libraries(ui raylib)

    add_subdirectory(examples
                    EXCLUDE_FROM_ALL)
else()
    message(WARNING "Won't build graphics examples because raylib could not be found")
endif()





