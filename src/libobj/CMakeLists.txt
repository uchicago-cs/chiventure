add_library(libobj
            src/load.c
            src/load_json.c
            src/load_wdz.c
            src/obj.c)

target_include_directories(libobj PRIVATE src/)

target_link_libraries(libobj ${LIBZIP_LIBRARIES} ${JSONC_LIBRARY})

# EXAMPLES
add_subdirectory(examples
        EXCLUDE_FROM_ALL)