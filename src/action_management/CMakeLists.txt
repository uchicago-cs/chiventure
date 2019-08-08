project(action_management C)

add_library(action_management
            src/actionmanagement.c
            src/get_actions.c)

target_include_directories(action_management PRIVATE src/)

# This is a temporary solution before the directories
# are reorganized
target_include_directories(action_management PRIVATE include/)
foreach(module ${CHIVENTURE_MODULES})
    target_include_directories(action_management PRIVATE ../${module}/include/)
endforeach(module)





