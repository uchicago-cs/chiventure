set(TEST_EXE test-custom-scripts)

add_executable(${TEST_EXE}
        test_types.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})

add_library(tests-custom-scripts
            test_types.c)

target_link_libraries(tests-custom-scripts ${LUA_LIBRARIES})
target_include_directories(tests-custom-scripts PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(tests-custom-scripts PRIVATE tests/)