add_library(openworld
            src/autogenerate.c
            ../../../tests/openworld/test_autogenerate.c)

target_include_directories(openworld PRIVATE sample_generation/)

target_link_libraries(openworld wdl)
target_link_libraries(openworld game-state)
target_link_libraries(openworld common)

# TODO: Checkpointing (which CLI depends on) uses a private header file
#       from game-state. See TODO in checkpointing CMakeLists.txt
#target_include_directories(cli PRIVATE ../game-state/src/)
