set(TEST_EXE test-checkpointing)

add_executable(${TEST_EXE}
        test_load.c
        test_save.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY} ${PROTOBUF-C_LIBRARIES})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

target_include_directories(${TEST_EXE} PRIVATE ${CMAKE_SOURCE_DIR}/src/checkpointing/src/)
target_include_directories(${TEST_EXE} PRIVATE ${PROJECT_BINARY_DIR}/src/checkpointing/protobuf/)

# TODO: Checkpointing uses a private header file from game-state
#       Whatever structs they use should be moved to their public
#       header files.
target_include_directories(${TEST_EXE} PRIVATE ${CMAKE_SOURCE_DIR}/src/game-state/src/)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})