cmake_minimum_required(VERSION 3.10)

include_directories(../../include/)

add_library(skilltrees STATIC
            stdst.c
            skill.c
            inventory.c
            skilltree.c)
