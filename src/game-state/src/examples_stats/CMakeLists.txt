set(STATS_EXAMPLES stats_example)

add_executable(stats_example
               stats_example.c)

# Link with chiventure libraries
foreach(example ${STATS_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(stats-examples
        DEPENDS ${STATS_EXAMPLES})