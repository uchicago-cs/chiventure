add_library(wdl
            src/wdl_ctx.c
            src/attributes.c
            src/load_game.c
            src/load_item.c
            src/load_room.c
            src/load_npc.c
            src/objstore.c
	        src/object.c
            src/parse.c
            src/validate.c
            src/load_wdz_common.c
            src/load_wdz_lzip.c)

target_include_directories(wdl PRIVATE src/)
target_include_directories(wdl PRIVATE ${LIBZIP_INCLUDE_DIR})
target_include_directories(wdl PRIVATE ${JSONC_INCLUDE_DIR})

target_link_libraries(wdl libobj ${JSONC_LIBRARIES} ${LIBZIP_LIBRARIES})
target_link_libraries(wdl npc)





