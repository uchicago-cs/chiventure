set(TEST_EXE test-openworld)

add_executable(${TEST_EXE}
<<<<<<< HEAD
	test_rooms.c
	test_items.c
=======
        test_structs.c
>>>>>>> 8ef40519ca7be2e9161d8eec254101580c64d749
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
