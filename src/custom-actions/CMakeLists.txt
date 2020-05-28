add_library(custom-actions
            src/ast_block.c
            src/control_block.c)

target_include_directories(custom-actions PRIVATE include/)
