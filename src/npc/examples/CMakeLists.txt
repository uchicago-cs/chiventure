set(NPC_EXAMPLES dialogue_example npc_example)

add_executable(dialogue_example
               dialogue_example.c)

add_executable(npc_example
               npc_example.c)

# Link with chiventure libraries
foreach(example ${NPC_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(npc-examples
        DEPENDS ${NPC_EXAMPLES})