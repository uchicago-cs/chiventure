add_library(custom-actions
            src/control_block.c
            src/ast_block.c)

target_include_directories(custom-actions PRIVATE include/)
