set(TEST_EXE test_sound)

add_executable(${TEST_EXE}
        test_sound.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
    target_link_libraries(sound common)
    target_link_libraries(sound SDL2)
    target_link_libraries(sound SDL2_mixer)
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
