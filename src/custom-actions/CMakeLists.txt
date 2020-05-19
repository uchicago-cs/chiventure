add_library(custom-actions
            src/action_block_functions.c
            src/ast_block_functions.c
            src/attribute_functions.c
            src/branch_block_functions.c
            src/conditional_block_functions.c
            src/control_block_functions.c)

target_include_directories(custom-actions PRIVATE src/)
