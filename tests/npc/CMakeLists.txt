set(TEST_EXE test-npc)

add_executable(${TEST_EXE}
        test_dialogue.c
        test_npc.c
        test_rooms_npc.c
	test_npc_battle.c
        test_npc_move.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})

target_include_directories(${TEST_EXE} PRIVATE tests/) 
