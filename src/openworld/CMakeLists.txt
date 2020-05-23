#add_library(openworld
#            src/autogenerate.c
#            ../../../tests/openworld/test_autogenerate.c)

add_library(openworld
<<<<<<< HEAD
            src/autogenerate.c
	    sample_generation/sample_rooms.c
	    sample_generation/sample_items.c
            ../../../tests/openworld/test_autogenerate.c)
=======
	    src/autogenerate.c
	    src/gen_structs.c)
>>>>>>> 8ef40519ca7be2e9161d8eec254101580c64d749

target_include_directories(openworld PRIVATE src/)

target_link_libraries(openworld wdl)
target_link_libraries(openworld game-state)
target_link_libraries(openworld common)

# TODO: Checkpointing (which CLI depends on) uses a private header file
#       from game-state. See TODO in checkpointing CMakeLists.txt
#target_include_directories(cli PRIVATE ../game-state/src/)
