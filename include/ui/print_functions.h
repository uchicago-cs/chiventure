#ifndef PRINT_FUNCTIONS_H
#define PRINT_FUNCTIONS_H

#include "common/ctx.h"
#include "ui/ui_ctx.h"


typedef struct window window_t;

/* print_homescreen
 * Prints the home screen
 *
 * Parameters:
 *   - win : window where the home screen should be printed
 *   - banner : chiventure banner to display
 * No value is returned
 */
void print_homescreen(window_t *win, const char *banner);

/* print_banner
 * Prints only the banner
 *
 * Parameters:
 *   - win : window where the home screen should be printed
 *   - banner : chiventure banner to display
 * No value is returned
 */
void print_banner(window_t *win, const char *banner);


/* print_info
 * Prints "Main Window"
 *
 * Parameters:
 *   - ctx : chiventure context struct
 *   - win : window where to print the info
 *   - retval: not used in this context
 *
 */
void print_info(chiventure_ctx_t *ctx, window_t *win, int *retval);

/* print_cli
 * Prints the CLI- adds and deletes character based on user input
 * Only calls to execute multiple commands separated by 'AND' when
 * both succeed, but calls to execute commands separated by ';' unconditionally
 *
 * Parameters:
 *   - ctx : chiventure context struct
 *   - win : window where to print the info
 *   - retval: an out parameter to have the string "QUIT" make the game close
 *
 */
void print_cli(chiventure_ctx_t *ctx, window_t *win, int *retval);

/* print_map
 * Prints the word map in the window (top left corner)
 *
 * Parameters:
 *   - ctx : chiventure context struct
 *   - win : window where to print the info
 *   - retval: not used in this function
 *
 */
void print_map(chiventure_ctx_t *ctx, window_t *win, int *retval);


/* print_to_cli
 * prints the given string the CLI window.
 *
 * Parameters:
 *    - ctx: chiventure context struct
 *    - str: message to be printed
 *
 * Returns:
 *  - Always returns 0
 */
int print_to_cli(chiventure_ctx_t *ctx, char *str);

#endif
