add_library(custom-actions
            src/custom-actions-effect.c
            src/custom-actions-cond.c)

target_include_directories(custom-actions PRIVATE include/)
