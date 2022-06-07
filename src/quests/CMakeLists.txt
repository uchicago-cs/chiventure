cmake_minimum_required(VERSION 3.10)

include_directories(../../include/)

add_library(quests STATIC
            src/quests_hash.c
            src/prereq.c
            src/quests_state.c
            src/quest.c
            src/task.c
            src/samples.c
            src/quests_cli.c)

add_subdirectory(examples
                 EXCLUDE_FROM_ALL)