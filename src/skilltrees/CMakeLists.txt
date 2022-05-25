cmake_minimum_required(VERSION 3.10)

include_directories(../../include/)

add_library(skilltrees STATIC
            src/effect.c
            src/skill.c
            src/inventory.c
            src/reader.c
            src/complex_skills.c
            src/skilltrees_common.c
            src/complex_skills.c
            src/skilltree.c)

add_subdirectory(examples
                 EXCLUDE_FROM_ALL)
