set(TEST_EXE test-cli)

add_executable(${TEST_EXE}
        test_cmd.c
        test_parser.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

# TODO: Checkpointing (which CLI depends on) uses a private header file
#       from game-state. See TODO in checkpointing CMakeLists.txt
target_include_directories(${TEST_EXE} PRIVATE ${CMAKE_SOURCE_DIR}/src/game-state/src/)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})