add_library(wdl
            src/load_game.c
            src/load_item.c
            src/load_room.c
<<<<<<< HEAD
<<<<<<< HEAD
            src/objstore.c
=======
	    src/object.c
>>>>>>> wdl/libobj-interface
=======
	        src/object.c
            src/objstore.c
>>>>>>> wdl/libobj-hash
            src/parse.c
            src/validate.c)

target_include_directories(wdl PRIVATE src/)

target_link_libraries(wdl libobj)





