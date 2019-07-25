cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

project(chiventure C)
find_package(Protobuf-c REQUIRED)
find_package(Criterion REQUIRED)
find_package(Curses REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

set(CHIVENTURE_MODULES action_management checkpointing cli common game-state libobj ui wdl)

# When the directories are reorganized, we just need to add the following
# statement, and then remove the foreach(module) loops for adding the
# per-module include directories
#
# include_directories(include/)

add_subdirectory(src/libobj)

# chiventure executable
add_executable(chiventure-bin src/chiventure.c)

# This is a temporary solution before the directories
# are reorganized
foreach(module ${CHIVENTURE_MODULES})
    target_include_directories(chiventure-bin PRIVATE src/${module}/include/)
endforeach(module)

foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(chiventure-bin ${module})
endforeach(module)

set_target_properties(chiventure-bin
        PROPERTIES OUTPUT_NAME chiventure)




