set(TEST_EXE test-cli)

add_executable(${TEST_EXE}
        test_cmd.c
        test_parser.c
        test_game.c
        test_operation.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
