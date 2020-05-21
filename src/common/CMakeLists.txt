add_library(common
            src/ctx.c
            src/sample_game.c)

add_library(custom-scripts
            src/custom_types.c)

target_link_libraries(custom-scripts ${LUA_LIBRARIES})
target_include_directories(custom-scripts PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(custom-scripts PRIVATE src/)

target_include_directories(common PRIVATE src/)

target_link_libraries(common cli)






