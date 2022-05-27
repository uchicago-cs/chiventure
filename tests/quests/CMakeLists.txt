set(TEST_EXE test-quests)

add_executable(${TEST_EXE}
        test_prereq.c
        test_quests_state.c
        test_quests_hash.c
        test_quest.c
        test_task.c
        main.c
        )

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})