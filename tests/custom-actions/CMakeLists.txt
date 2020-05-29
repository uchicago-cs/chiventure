set(TEST_EXE test-custom-actions)

add_executable(${TEST_EXE}
<<<<<<< HEAD
<<<<<<< HEAD
        test_action_block.c
        test_conditional_block.c
=======
>>>>>>> origin/dev
        test_control_block.c
        test_branch_block.c
        test_ast_block.c
<<<<<<< HEAD
=======
        test_ca_cond.c
>>>>>>> origin/dev
=======
>>>>>>> origin/dev
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

target_include_directories(${TEST_EXE} PRIVATE ${CMAKE_SOURCE_DIR}/src/custom-actions/include/)

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
