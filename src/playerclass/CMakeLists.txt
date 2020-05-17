add_library(playerclass
        src/class.c
        )

target_include_directories(playerclass PRIVATE src/)

target_link_libraries(playerclass ${LIBYAML_LIBRARIES} )






