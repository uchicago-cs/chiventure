set(OPENWORLD_EXAMPLES openworld_example)

add_executable(openworld_example
               openworld_example.c)

# Link with chiventure libraries
foreach(example ${OPENWORLD_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(openworld-examples
        DEPENDS ${OPENWORLD_EXAMPLES})
        