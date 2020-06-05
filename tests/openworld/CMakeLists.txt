set(TEST_EXE test-openworld)

add_executable(${TEST_EXE}
    test_autogenerate.c
    test_items.c
    test_rooms.c
    test_structs.c
    main.c)


target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
