set(LIBOBJ_EXAMPLES obj-example wdl-example)

add_executable(obj-example
        obj-example.c)

add_executable(wdl-example
        wdl-example.c)

# Link with chiventure libraries
foreach(example ${LIBOBJ_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(libobj-examples
        DEPENDS ${LIBOBJ_EXAMPLES})