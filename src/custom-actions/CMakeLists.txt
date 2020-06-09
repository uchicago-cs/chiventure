add_library(custom-actions
            src/ast_block.c
            src/branch_block.c
            src/control_block.c
            src/custom_action.c
            src/action_block.c
            src/conditional_block.c
            src/custom-actions-cond.c
            src/custom-actions-effect.c
            src/interface.c
            )

target_include_directories(custom-actions PRIVATE include/)
