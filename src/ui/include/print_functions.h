#ifndef PRINT_FUNCTIONS_H
#define PRINT_FUNCTIONS_H

#include "ctx.h"

/* print_info
 * Prints score and number of moves
 *
 * Parameters:
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_info(chiventure_ctx_t *ctx, window_t *win);

/* print_cli
 * Prints the CLI- adds and deltees character based on user input
 *
 * Parameters:
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_cli(chiventure_ctx_t *ctx, window_t *win);

/* print_map
 * Prints the word map in the window (top left corner)
 *
 * Parameters:
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_map(chiventure_ctx_t *ctx, window_t *win);


/* print_to_cli
 * prints the given string the CLI window
 *
 * Parameters:
 *    - ctx : chiventrue context struct
 *    - str : message to be printed
 *
 * No value is returned
 */
void print_to_cli(chiventure_ctx_t *ctx, char *str);


#endif
