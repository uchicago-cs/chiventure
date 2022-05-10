#ifndef INPUT_BOX_H
#define INPUT_BOX_H


/*
 * Runs the input box window and really enables data input
 *
 * Parameters:
 *      windowDimension: the (width, height) dimension of the window to be initialized;
 *      windowPosition: the (x,y) position of the window to be initialized;
 *      input_buffer: a string buffer to get user input from the textbox;
 *
 * Return:
 *      Nothing
 */
void run_input_box(Vector2 windowDimension, Vector2 windowPosition, char* input_buffer);

#endif
