add_library(sound
            src/hashtable.c)

target_include_directories(sound PRIVATE src/)

target_link_libraries(sound common)





