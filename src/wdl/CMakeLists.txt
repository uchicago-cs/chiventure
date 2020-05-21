add_library(wdl
            src/load_game.c
            src/load_item.c
            src/load_room.c
            src/parse.c
            src/validate.c)

target_link_libraries(wdl ${LUA_LIBRARIES})
target_include_directories(wdl PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(wdl PRIVATE src/)

target_link_libraries(wdl libobj)





