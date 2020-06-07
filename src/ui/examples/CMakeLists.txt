if (raylib_FOUND)
    set(UI_EXAMPLES map_raylib_example)

    add_executable(map_raylib_example
                   map_raylib_example.c)

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