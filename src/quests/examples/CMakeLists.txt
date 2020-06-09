set(QUESTS_EXAMPLES quest-example)

add_executable(quest-example
               quest-example.c)

target_link_libraries(quest-example ${LUA_LIBRARIES})
target_include_directories(quest-example PRIVATE ${LUA_INCLUDE_DIR})

# Link with chiventure libraries
foreach(example ${QUESTS_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(quests-examples
        DEPENDS ${QUESTS_EXAMPLES})