cmake_minimum_required(VERSION 3.10)

include_directories(../../include/)

add_library(skilltrees STATIC
            skill.c
            inventory.c)
