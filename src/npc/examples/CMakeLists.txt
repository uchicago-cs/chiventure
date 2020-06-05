set(NPC_EXAMPLES convo)

add_executable(convo
               dialogue_example.c
               ../src/dialogue.c)

# Link with chiventure libraries
foreach(example ${CLI_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(npc-examples
        DEPENDS ${NPC_EXAMPLES})