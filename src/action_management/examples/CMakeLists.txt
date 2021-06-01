set(ACTION_MANAGEMENT_EXAMPLES spring2021-demo)

add_executable(spring2021-demo
               spring2021-demo.c)

# Link with chiventure libraries
foreach(example ${ACTION_MANAGEMENT_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(action_management-examples
        DEPENDS ${ACTION_MANAGEMENT_EXAMPLES})

