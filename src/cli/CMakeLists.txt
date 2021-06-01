add_library(cli
            src/util.c
            src/cmd.c
            src/cmdlist.c
            src/cli_ctx.c
            src/operations.c
            src/parser.c
            src/shell.c)

target_include_directories(cli PRIVATE src/)

target_link_libraries(cli action_management)
target_link_libraries(cli ui)
target_link_libraries(cli game-state)
target_link_libraries(cli wdl)
target_link_libraries(cli common)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)






