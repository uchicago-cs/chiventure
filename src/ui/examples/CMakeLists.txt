set(UI_EXAMPLES map_raylib_example)

add_executable(map_raylib_example
               map_raylib_example.c)

# Link with chiventure libraries
foreach(example ${UI_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

target_link_libraries(${UI_EXAMPLES} raylib)

find_package(raylib 3.0 QUIET)

add_custom_target(ui_examples
        DEPENDS ${UI_EXAMPLES})