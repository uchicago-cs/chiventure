add_library(sound
            src/sound.c
            src/tts.c)

target_include_directories(sound PRIVATE src/)

target_link_libraries(sound common)

add_subdirectory(examples
        EXCLUDE_FROM_ALL)




