set(TEST_EXE test-custom-actions)

add_executable(${TEST_EXE}
        test_ast_block.c
        test_control_block.c
        test_action_block.c
        test_attribute_functions.c
        test_branch_block.c
        test_conditional_block.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES}})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
