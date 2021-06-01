add_library(wdl
            src/load_game.c
            src/load_item.c
            src/load_room.c
            src/load_class.c
            src/validate.c)

target_include_directories(wdl PRIVATE src/)
target_include_directories(wdl PRIVATE ${LIBZIP_INCLUDE_DIR})
target_include_directories(wdl PRIVATE ${JSONC_INCLUDE_DIR})

# Adding playerclass and skilltrees prevents certain undefined reference errors the chiventure executeable.
target_link_libraries(wdl libobj playerclass skilltrees ${JSONC_LIBRARIES} ${LIBZIP_LIBRARIES})





