set(NPC_EXAMPLES dialogue_example npc_example conversation_mode_example battle_move_example_2021
    battle_npc_with_time_example_2022 npc_example_2022)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lpthread")

add_executable(dialogue_example
               dialogue_example.c)

add_executable(npc_example
               npc_example.c)

add_executable(conversation_mode_example
               conversation_mode_example.c)

add_executable(battle_move_example_2021
               battle_move_example_2021.c)

add_executable(npc_example_2022 npc_example_2022.c)

target_link_options(npc_example_2022 PUBLIC -lpthread)

add_executable(battle_npc_with_time_example_2022
               battle_npc_with_time_example_2022.c)

# Link with chiventure libraries
foreach(example ${NPC_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module} pthread)
    endforeach(module)
endforeach(example)

add_custom_target(npc-examples
        DEPENDS ${NPC_EXAMPLES})
