set(TEST_EXE test-battle)

add_executable(${TEST_EXE}
        test_battle_ai.c
        test_battle_flow.c
        test_battle_flow_structs.c
        test_battle_logic.c
        test_battle_moves.c
        test_battle_move_maker.c
        test_battle_print.c
        test_battle_state.c
        test_battle_default_objects.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
