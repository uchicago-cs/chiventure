#ifndef _CLI_INCLUDE_SHELL_H
#define _CLI_INCLUDE_SHELL_H

#include "common/ctx.h"

/*
 * The shell module contains system internal functions
 *
 */

/* ========================= */
/* === interface actions === */
/* ========================= */

/*
 * Prints out a help menu that contains a list of supported commands
 * (Note that this function will be moved to operation.c)
 *
 * Parameters:
 *  - none
 *
 * Returns:
 *  - nothing
 */
void help_text(chiventure_ctx_t *ctx);


/*
 * Prints a greeting message when player starts the game
 * (Note that this function will be moved to operation.c)
 *
 * Parameters:
 *  - none
 *
 * Returns:
 *  - nothing
 */
void greet(chiventure_ctx_t *ctx);


/*
 * Prints out the history of valid command inputs in the current session
 *
 * Parameters:
 *  - none
 *
 * Returns:
 *  - none
 */
void print_history(chiventure_ctx_t *ctx);


/*
 * Prints out error messages for user errors (as opposed to bugs in code)
 * This function is mostly replaced by other more detailed error messages
 *
 * Parameters:
 *  - input string
 *
 * Returns:
 *  - none
 */
void shell_error(char *s);


/*
 * Prints out error messages for user errors (as opposed to bugs in code)
 * - this version takes a string arg for added flexibility
 *
 * Parameters:
 *  - fmt: error message
 *  - s: input string
 *
 * Returns:
 *  - none
 */
void shell_error_arg(char *fmt, char *s);

#endif /* _CLI_INCLUDE_SHELL_H */
