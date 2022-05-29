if (Espeak_FOUND)
    set(SOUND_EXAMPLES test-tts)

    add_executable(test-tts
                   test-tts.c)

    # Link with chiventure libraries
    foreach(example ${SOUND_EXAMPLES})
        foreach(module ${CHIVENTURE_MODULES})
            target_link_libraries(${example} ${module})
            target_link_libraries(${example} espeak-ng)
        endforeach(module)
    endforeach(example)

    add_custom_target(sound-examples
            DEPENDS ${SOUND_EXAMPLES})
else()
    message(WARNING "Won't build sound examples because espeak-ng could not be found")
endif()
