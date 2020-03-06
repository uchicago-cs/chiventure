cmake_minimum_required(VERSION 3.5.1)
project(chiventure C)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

find_package(Protobuf-c REQUIRED)
find_package(Criterion REQUIRED)
find_package(Curses REQUIRED)
find_package(LibYAML REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

set(CHIVENTURE_MODULES action_management checkpointing cli common game-state libobj ui wdl)

include_directories(include/)

add_subdirectory(src/action_management)
add_subdirectory(src/checkpointing)
add_subdirectory(src/cli)
add_subdirectory(src/common)
add_subdirectory(src/game-state)
add_subdirectory(src/libobj)
add_subdirectory(src/ui)
add_subdirectory(src/wdl)

# chiventure executable
add_executable(chiventure-bin src/chiventure.c)

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(chiventure-bin ${module})
endforeach(module)

set_target_properties(chiventure-bin
        PROPERTIES OUTPUT_NAME chiventure)


# TESTS

set(TEST_LIBS ${CRITERION_LIBRARY} ${PROTOBUF-C_LIBRARIES})

file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "tests/*.c")

add_executable(test-chiventure ${TEST_SOURCES})

target_link_libraries(test-chiventure ${TEST_LIBS})

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(test-chiventure ${module})
endforeach(module)


# TODO: Checkpointing uses a private header file from game-state
#       Whatever structs they use should be moved to their public
#       header files. It also needs access to the protobuf files.
target_include_directories(test-chiventure PRIVATE
        src/game-state/src/
        src/checkpointing/src/
        ${CMAKE_CURRENT_BINARY_DIR}/src/checkpointing/protobuf/)




