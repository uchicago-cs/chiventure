set(TEST_EXE test-skilltrees)

add_executable(${TEST_EXE}
        test_init.c
        complex_skill_test.c
        effect_test.c
        complex_skill_test.c
        inventory_test.c
        reader_test.c
        skill_test.c
        skilltree_test.c
        skilltrees_common_test.c
        main.c
        )

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
