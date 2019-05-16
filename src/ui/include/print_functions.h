#ifndef PRINT_FUNCTIONS_H
#define PRINT_FUNCTIONS_H


/* print_scor
 * Prints score and number of moves
 *
 * Parameters:
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_info(window_t *win);

/* print_cli
 * Prints the CLI- adds and deltees character based on user input
 *
 * Parameters:
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_cli(window_t *win);

/* print_map
 * Prints the word map in the window (top left corner)
 *
 * Parameters:
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_map(window_t *win);

/* print_window
 * Calls the print function associated with the given window
 *
 * Parameters:
 *    - win : window which we want to print
 *
 * does not return anything
 */
void print_window(window_t *win);
#endif
