set(GAME-STATE_EXAMPLES stats_example)

add_executable(stats_example
               stats_example.c)

# Link with chiventure libraries
foreach(example ${GAME-STATE_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(game-state-examples
        DEPENDS ${GAME-STATE_EXAMPLES})
