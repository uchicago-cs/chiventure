set(TEST_EXE test-quests)

add_executable(${TEST_EXE}
        test_quests_state.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})

target_include_directories(${TEST_EXE} PRIVATE tests/) 