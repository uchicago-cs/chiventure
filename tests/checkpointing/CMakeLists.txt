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

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})