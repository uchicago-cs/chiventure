add_library(common
            src/ctx.c
            src/custom_types.c
            src/sample_game.c)

target_link_libraries(common ${LUA_LIBRARIES})
target_include_directories(common PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(common PRIVATE src/)

target_link_libraries(common cli)






