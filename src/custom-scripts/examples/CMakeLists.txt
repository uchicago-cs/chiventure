set(CS_EXAMPLES lost_order)

add_executable(lost_order
               lost_order.c)

target_link_libraries(lost_order ${LUA_LIBRARIES})
target_include_directories(lost_order PRIVATE ${LUA_INCLUDE_DIR})

# Link with chiventure libraries
foreach(example ${CS_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(cs_examples
        DEPENDS ${CS_EXAMPLES})