set(TEST_EXE test-custom-actions)

add_executable(${TEST_EXE}
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

target_include_directories(${TEST_EXE} PRIVATE ${CMAKE_SOURCE_DIR}/src/custom-actions/include/)

foreach(module ${CHIVENTURE_MODULES}})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})
