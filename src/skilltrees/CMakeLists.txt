cmake_minimum_required(VERSION 3.10)

include_directories(../../include/skilltrees/)

add_library(skilltrees STATIC
            skilltrees.c)
