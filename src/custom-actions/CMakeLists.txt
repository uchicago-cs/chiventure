add_library(custom-actions
            src/action_block.c
            src/conditional_block.c
            src/branch_block.c
            src/control_block.c
            src/ast_block.c)
            src/custom-actions-cond.c)

target_include_directories(custom-actions PRIVATE include/)
