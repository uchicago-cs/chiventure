if (raylib_FOUND)
    set(UI_EXAMPLES map_raylib_example split_screen_example split_screen_map_example gui_sample_game)

    add_executable(map_raylib_example
                   map_raylib_example.c)
    add_executable(split_screen_example
                   split_screen_example.c)
    add_executable(split_screen_map_example
                   split_screen_map_example.c)
    add_executable(gui_sample_game
                   gui_sample_game.c)               

    # Link with chiventure libraries
    foreach(example ${UI_EXAMPLES})
        foreach(module ${CHIVENTURE_MODULES})
            target_link_libraries(${example} ${module})
            target_link_libraries(${example} raylib)
        endforeach(module)
    endforeach(example)

    add_custom_target(ui-examples
            DEPENDS ${UI_EXAMPLES})
else()
    message(WARNING "Won't build graphics examples because raylib could not be found")
endif()
