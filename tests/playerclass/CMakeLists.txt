set(TEST_EXE test-playerclass)

add_executable(${TEST_EXE}
        test_class.c
        test_class_item.c
        test_multiclass.c
        test_class_prefabs.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})