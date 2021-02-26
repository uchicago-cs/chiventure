add_library(libobj
            src/obj.c
            src/parser.c
            src/stack.c)

target_include_directories(libobj PRIVATE src/)

target_link_libraries(libobj ${LIBZIP_LIBRARIES} ${LIBYAML_LIBRARIES})
