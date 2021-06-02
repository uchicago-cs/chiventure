add_library(sound
            src/sound.c)

target_include_directories(sound PRIVATE src/)

target_link_libraries(sound common)





