# List all skilltrees example files
set(SKILLTREES_EXAMPLES skilltrees_demo)

# Add skilltrees presentation executable
add_executable(skilltrees_demo
               skilltrees_demo.c)

# Link with chiventure libraries
foreach(example ${SKILLTREES_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(skilltrees_examples
        DEPENDS ${SKILLTREES_EXAMPLES})
