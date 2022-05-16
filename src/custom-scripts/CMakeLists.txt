add_library(custom-scripts
            src/get_custom_type.c)

target_link_libraries(custom-scripts ${LUA_LIBRARIES})
target_include_directories(custom-scripts PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(custom-scripts PRIVATE src/)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)