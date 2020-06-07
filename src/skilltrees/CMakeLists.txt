cmake_minimum_required(VERSION 3.10)

include_directories(../../include/)

add_library(skilltrees STATIC
            src/stdst.c
            src/skill.c
            src/inventory.c
            src/skilltree.c)
