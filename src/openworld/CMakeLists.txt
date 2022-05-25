add_library(openworld
            src/autogenerate.c
            src/default_rooms.c
            src/default_items.c
            src/gen_structs.c)

target_include_directories(openworld PRIVATE src/)

target_link_libraries(openworld wdl)
target_link_libraries(openworld game-state)
target_link_libraries(openworld common)

