add_library(wdl
            src/load_game.c
            src/load_item.c
            src/load_room.c
            src/parse.c
            src/validate.c
            src/load_wdz.c
            src/miniz-zip.c)

target_include_directories(wdl PRIVATE src/)

target_link_libraries(wdl libobj)





