set(CS_EXAMPLES loadwdl)

add_executable(loadwdl
               loadwdl.c)

target_link_libraries(loadwdl ${LUA_LIBRARIES})
target_include_directories(loadwdl PRIVATE ${LUA_INCLUDE_DIR})

# Link with chiventure libraries
foreach(example ${CS_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(cs_examples
        DEPENDS ${CS_EXAMPLES})