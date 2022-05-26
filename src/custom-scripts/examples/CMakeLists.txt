set(CS_EXAMPLES dark_room)

add_executable(dark_room
               dark_room.c)

target_link_libraries(dark_room ${LUA_LIBRARIES})
target_include_directories(dark_room PRIVATE ${LUA_INCLUDE_DIR})

# Link with chiventure libraries
foreach(example ${CS_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(cs_examples
        DEPENDS ${CS_EXAMPLES})