#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "raylib.h"
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


typedef struct input_box_graphics{
    Vector2 WindowPos;
    Vector2 WindowSize;
    unsigned MaxCharNum;
    Color BoxColor;
    Color TestColor;
    Color AnnotationColor;
    const char* Annotation;
} input_box_graphics_t;

#endif
