add_library(wdl
            src/load_game.c
            src/load_item.c
            src/load_room.c
	    src/object.c
            src/parse.c
            src/validate.c
            src/wdlparser.c)

target_include_directories(wdl PRIVATE src/)

target_link_libraries(wdl libobj)
target_link_libraries(wdl ${JSONC_LIBRARIES} ${LIBZIP_LIBRARIES})





