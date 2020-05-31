set(TEST_EXE test-action_management)

add_executable(${TEST_EXE}
        test_action_new_init_free.c
        test_get_actions.c
        test_item_actions.c
        test_item_item_actions.c
        test_path_actions.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
