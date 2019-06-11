#ifndef PRINT_FUNCTIONS_H
#define PRINT_FUNCTIONS_H

#include "ctx.h"


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


/* print_info
 * Prints "Main Window"
 *
 * Parameters:
 *   - ctx : chiventure context struct
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_info(chiventure_ctx_t *ctx, window_t *win);

/* print_cli
 * Prints the CLI- adds and deletes character based on user input
 *
 * Parameters:
 *   - ctx : chiventure context struct
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_cli(chiventure_ctx_t *ctx, window_t *win);

/* print_map
 * Prints the word map in the window (top left corner)
 *
 * Parameters:
 *   - ctx : chiventure context struct
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_map(chiventure_ctx_t *ctx, window_t *win);


/* print_to_cli
 * prints the given string the CLI window
 *
 * Parameters:
 *    - ctx : chiventure context struct
 *    - str : message to be printed
 *
 * No value is returned
 */
void print_to_cli(chiventure_ctx_t *ctx, char *str);


#endif
