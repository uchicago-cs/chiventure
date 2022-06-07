set(SOUND_EXAMPLES test-tts tts-dialogue-example)

add_executable(test-tts
                test-tts.c)

add_executable(tts-dialogue-example
                tts_dialogue_example.c)

# Link with chiventure libraries
foreach(example ${SOUND_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
        target_link_libraries(${example} espeak-ng)
    endforeach(module)
endforeach(example)

add_custom_target(sound-examples
        DEPENDS ${SOUND_EXAMPLES})
