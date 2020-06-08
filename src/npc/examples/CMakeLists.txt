set(NPC_EXAMPLES dialogue_example npc_example)

add_executable(dialogue_example
               dialogue_example.c)

add_executable(npc_example
               npc_example.c)

target_link_libraries(dialogue_example ${LUA_LIBRARIES})
target_include_directories(dialogue_example PRIVATE ${LUA_INCLUDE_DIR})

target_link_libraries(npc_example ${LUA_LIBRARIES})
target_include_directories(npc_example PRIVATE ${LUA_INCLUDE_DIR})

# Link with chiventure libraries
foreach(example ${NPC_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(npc-examples
        DEPENDS ${NPC_EXAMPLES})