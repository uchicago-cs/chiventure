set(CS_EXAMPLES loadwdl loadwdl2 demonstration)

# Link with chiventure libraries
foreach(example ${CS_EXAMPLES})
    add_executable(${example}
               ${example}.c)
    target_link_libraries(${example} ${LUA_LIBRARIES})
    target_include_directories(${example} PRIVATE ${LUA_INCLUDE_DIR})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(cs_examples
        DEPENDS ${CS_EXAMPLES})