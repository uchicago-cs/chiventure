set(CLI_EXAMPLES extra-command)

add_executable(extra-command
               extra-command.c)

# Link with chiventure libraries
foreach(example ${CLI_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(cli-examples
        DEPENDS ${CLI_EXAMPLES})

