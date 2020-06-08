set(TEST_EXE test-wdl)

add_executable(${TEST_EXE}
        test_attributes.c
        test_game.c
        test_item.c
        test_objstore.c
        test_room.c
        test_validation.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})