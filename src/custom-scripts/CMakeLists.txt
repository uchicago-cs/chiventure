add_library(custom-scripts
            src/custom_type.c
            src/custom_types.c)

target_link_libraries(custom-scripts ${LUA_LIBRARIES})
target_include_directories(custom-scripts PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(custom-scripts PRIVATE src/)