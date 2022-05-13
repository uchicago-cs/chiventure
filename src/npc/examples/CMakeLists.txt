set(NPC_EXAMPLES dialogue_example npc_example conversation_mode_example battle_move_example_2021)

add_executable(dialogue_example
               dialogue_example.c)

add_executable(npc_example
               npc_example.c)

add_executable(conversation_mode_example
               conversation_mode_example.c)

add_executable(battle_move_example_2021
               battle_move_example_2021.c)

# Link with chiventure libraries
foreach(example ${NPC_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(npc-examples
        DEPENDS ${NPC_EXAMPLES})
