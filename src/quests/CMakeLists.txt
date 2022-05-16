cmake_minimum_required(VERSION 3.10)

include_directories(../../include/)

add_library(quests STATIC
            src/quest_hash.c
            src/quest.c
            src/task.c)

add_subdirectory(examples
                 EXCLUDE_FROM_ALL)