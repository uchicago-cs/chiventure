add_library(action_management
            src/actionmanagement.c
            src/get_actions.c)

target_include_directories(action_management PRIVATE src/)

target_link_libraries(action_management ${LUA_LIBRARIES})
target_include_directories(action_management PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(action_management PRIVATE src/)






