add_library(sound
            src/sound.c)

target_include_directories(sound PRIVATE src/)

target_link_libraries(sound common)
target_link_libraries(sound SDL2)
target_link_libraries(sound SDL2_mixer)




