set(CS_EXAMPLES demonstration)

add_executable(demonstration
               demonstration.c)

target_link_libraries(demonstration ${LUA_LIBRARIES})
target_include_directories(demonstration PRIVATE ${LUA_INCLUDE_DIR})

# Link with chiventure libraries
foreach(example ${CS_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(cs_examples
        DEPENDS ${CS_EXAMPLES})