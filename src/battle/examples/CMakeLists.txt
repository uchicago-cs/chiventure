set(BATTLE_EXAMPLES battle_command_example battle_flow_example battle_cli_example)

add_executable(battle_command_example
               battle_command_example.c)

add_executable(battle_flow_example
               battle_flow_example.c)

add_executable(battle_cli_example
               battle_cli_example.c)

# Link with chiventure libraries
foreach(example ${BATTLE_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(battle-examples
        DEPENDS ${BATTLE_EXAMPLES})
