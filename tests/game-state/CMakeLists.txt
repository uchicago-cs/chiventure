set(TEST_EXE test-game-state)

add_executable(${TEST_EXE}
	test_delete_action.c
        test_game.c
        test_items.c
        test_mode.c
        test_path.c
        test_player.c
        test_rooms.c
        test_stats.c
        test_condition.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
