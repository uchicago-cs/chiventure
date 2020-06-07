set(BATTLE_EXAMPLES battle_main_example)

add_executable(battle_main
               battle_main.c)

# Link with chiventure libraries
foreach(example ${BATTLE_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(battle-examples
        DEPENDS ${BATTLE_EXAMPLES})
