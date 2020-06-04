set(TEST_EXE test-wdl)

add_executable(${TEST_EXE}
        test_game.c
        test_item.c
        test_objstore.c
        test_room.c
        test_validation.c
        test_wdlparser.c
        main.c)

target_link_libraries(${TEST_EXE} ${CRITERION_LIBRARY})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${TEST_EXE} ${module})
endforeach(module)

add_test(NAME ${TEST_EXE}
         COMMAND ${TEST_EXE})

target_link_libraries(${TEST_EXE} ${JSONC_LIBRARIES} ${LIBZIP_LIBRARIES})

target_include_directories(${TEST_EXE} PRIVATE ${LIBZIP_INCLUDE_DIR})
target_include_directories(${TEST_EXE} PRIVATE ${JSONC_INCLUDE_DIR})
target_include_directories(${TEST_EXE} PRIVATE ${CMAKE_SOURCE_DIR}/src/wdl/src/)