add_library(custom-actions
            src/ast_block.c
            src/branch_block.c
            src/control_block.c
            src/custom_action.c
            src/interface.c
            src/action_block.c
            src/conditional_block.c)


target_include_directories(custom-actions PRIVATE include/)
