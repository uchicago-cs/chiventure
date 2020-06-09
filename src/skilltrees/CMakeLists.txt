cmake_minimum_required(VERSION 3.10)

include_directories(../../include/)

add_library(skilltrees STATIC
            src/skilltrees_common.c
            src/skill.c
            src/inventory.c
            src/skilltree.c)

add_subdirectory(examples
                 EXCLUDE_FROM_ALL)
