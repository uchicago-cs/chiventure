add_library(custom-actions
            src/action_block.c
            src/branch_block.c
            src/conditional_block.c   
            src/control_block.c)

target_include_directories(custom-actions PRIVATE include/)

