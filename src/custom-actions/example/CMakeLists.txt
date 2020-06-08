set(CUSTOM_ACTIONS_EXAMPLES custom-actions-demo)

add_executable(custom-actions-demo
               custom-actions-demo.c)

# Link with chiventure libraries
foreach(example ${CUSTOM_ACTIONS_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(custom-actions-examples
    DEPENDS ${CUSTOM_ACTIONS_EXAMPLES})
