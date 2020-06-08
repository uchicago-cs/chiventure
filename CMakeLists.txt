cmake_minimum_required(VERSION 3.10)
project(chiventure C)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

find_package(Protobuf-c REQUIRED)
find_package(LibYAML REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

find_package(Lua 5.3 REQUIRED)
set(Lua_INCLUDE_DIRS ${Lua_SOURCE_DIR} ${LUA_INCLUDE_DIR})
add_definitions(-DLUA)
include_directories(${INCLUDE_DIRS})

find_package(raylib 3.0 QUIET)
if (raylib_FOUND)
    message(STATUS "Found raylib: ${raylib_LIBRARY}")
endif()

set(CHIVENTURE_MODULES action_management battle checkpointing cli common custom-actions custom-scripts game-state libobj quests npc openworld playerclass skilltrees ui wdl)

include_directories(include/)

add_subdirectory(src/action_management)
add_subdirectory(src/battle)
add_subdirectory(src/checkpointing)
add_subdirectory(src/cli)
add_subdirectory(src/common)
add_subdirectory(src/custom-actions)
add_subdirectory(src/custom-scripts)
add_subdirectory(src/game-state)
add_subdirectory(src/libobj)
add_subdirectory(src/quests)
add_subdirectory(src/npc)
add_subdirectory(src/openworld)
add_subdirectory(src/skilltrees)
add_subdirectory(src/playerclass)
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
find_package(Criterion REQUIRED)
enable_testing()
add_subdirectory(tests)


# EXAMPLES
add_custom_target(examples)
foreach(module ${CHIVENTURE_MODULES})
    if(TARGET ${module}-examples)
        add_dependencies(examples ${module}-examples)
    endif()
endforeach(module)
