add_library(wdl
            src/load_game.c
            src/load_item.c
            src/load_room.c
            src/parse.c
            src/validate.c)

target_include_directories(wdl PRIVATE src/)
target_include_directories(wdl PRIVATE ${LIBZIP_INCLUDE_DIR})
target_include_directories(wdl PRIVATE ${JSONC_INCLUDE_DIR})

target_link_libraries(wdl libobj ${JSONC_LIBRARIES} ${LIBZIP_LIBRARIES})





