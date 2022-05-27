add_library(action_management
            src/actionmanagement.c
            src/get_actions.c)

target_include_directories(action_management PRIVATE src/)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)






