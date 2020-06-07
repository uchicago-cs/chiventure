set(SKILLTREES_EXAMPLES skilltrees_presentation)

add_executable(skilltrees_presentation
               skilltrees_presentation.c)

# Link with chiventure libraries
foreach(example ${SKILLTREES_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(skilltrees_examples
        DEPENDS ${SKILLTREES_EXAMPLES})
