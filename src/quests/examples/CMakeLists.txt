set(QUESTS_EXAMPLES quest-example)

add_executable(quest-example
               quest-example.c)

# Link with chiventure libraries
foreach(example ${QUESTS_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(quests-examples
        DEPENDS ${QUESTS_EXAMPLES})