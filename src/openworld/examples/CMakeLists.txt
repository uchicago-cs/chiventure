set(OPENWORLD_EXAMPLES openworld-demo-2021 debug2)

add_executable(openworld-demo-2021
               openworld-demo-2021.c)

add_executable(debug2
               debug2.c)

# Link with chiventure libraries
foreach(example ${OPENWORLD_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(openworld-examples
        DEPENDS ${OPENWORLD_EXAMPLES})
        