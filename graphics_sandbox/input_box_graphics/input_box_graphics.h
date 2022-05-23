#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "raylib.h"

#define INPUT_BOX_CONTEXT_ID 6


typedef struct input_box_graphics{
    Vector2 WindowPos;
    Vector2 WindowSize;
    Color BoxColor;
    Color TextColor;
    Color AnnotationColor;
    Color OutlineColor;
    const char* Annotation;
} input_box_graphics_t;

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
void run_input_box(input_box_graphics_t *input_box_graphics, char* input_buffer);

#endif
