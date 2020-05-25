set(TEST_EXE test-custom-actions)

add_executable(${TEST_EXE}
        test_action_block.c
<<<<<<< HEAD
=======
        test_ast_block.c
>>>>>>> c18b8c226a0caef29c7f837312b5b2cc9e71e018
        test_branch_block.c
        test_conditional_block.c
        test_control_block.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

target_include_directories(${TEST_EXE} PRIVATE ${CMAKE_SOURCE_DIR}/src/custom-actions/include/)

foreach(module ${CHIVENTURE_MODULES}})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
