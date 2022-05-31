add_library(sound
            src/sound.c
            )

if (Espeak_FOUND)
    target_sources(sound PRIVATE src/tts.c)
    target_link_libraries(sound espeak-ng)
    add_subdirectory(examples
            EXCLUDE_FROM_ALL)
endif()

target_include_directories(sound PRIVATE src/)

target_link_libraries(sound common)
target_link_libraries(sound SDL2)
target_link_libraries(sound SDL2_mixer)





