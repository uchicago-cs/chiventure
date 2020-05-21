set(TEST_EXE test-custom-actions)

add_executable(${TEST_EXE}
        test_ast_block_functions.c
        test_control_block_functions.c
        test_action_block_functions.c
        test_attribute_functions.c
        test_branch_block_functions.c
        test_conditional_block_functions.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES}})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
