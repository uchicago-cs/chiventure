set(PLAYERCLASS_EXAMPLES class-list)

add_executable(class-list
               class-list.c)

# Link with chiventure libraries
foreach(example ${CLI_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(playerclass-examples
        DEPENDS ${PLAYERCLASS_EXAMPLES})

