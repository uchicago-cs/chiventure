set(OPENWORLD_EXAMPLES openworld-demo-2022)

add_executable(openworld-demo-2022
               openworld-demo-2022.c)

# Link with chiventure libraries
foreach(example ${OPENWORLD_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(openworld-examples
        DEPENDS ${OPENWORLD_EXAMPLES})
        