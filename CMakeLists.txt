cmake_minimum_required(VERSION 3.10)
project(chiventure C)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

find_package(JSON-C REQUIRED)
find_package(LibZIP REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Optional dependencies

set(OPTIONAL_MODULES "")

find_package(Lua 5.3 QUIET)
if (Lua_FOUND)
    message(STATUS "Found Lua: ${LUA_VERSION_STRING}")
    set(Lua_INCLUDE_DIRS ${Lua_SOURCE_DIR} ${LUA_INCLUDE_DIR})
    add_definitions(-DLUA)
    list(APPEND OPTIONAL_MODULES custom-scripts)
endif()

find_package(raylib 3.0 QUIET)
if (raylib_FOUND)
    message(STATUS "Found raylib: ${raylib_LIBRARY}")
    add_compile_definitions(GUI_AVAILABLE)
endif()

find_package(Espeak)

set(CHIVENTURE_MODULES action_management battle cli common custom-actions game-state libobj quests sound npc openworld playerclass skilltrees ui wdl)

list(APPEND CHIVENTURE_MODULES ${OPTIONAL_MODULES})

include_directories(${INCLUDE_DIRS})
include_directories(include/)

foreach(module ${CHIVENTURE_MODULES})
    add_subdirectory(src/${module})
endforeach(module)

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
foreach(module ${CHIVENTURE_MODULES})
    if(EXISTS ${PROJECT_SOURCE_DIR}/tests/${module})
        add_subdirectory(tests/${module})
    endif()
endforeach(module)

# EXAMPLES
add_custom_target(examples)
foreach(module ${CHIVENTURE_MODULES})
    if(TARGET ${module}-examples)
        add_dependencies(examples ${module}-examples)
    endif()
endforeach(module)
