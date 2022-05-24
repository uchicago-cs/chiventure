#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "raylib.h"
#include "common.h"

#define INPUT_BOX_CONTEXT_ID 6
#define MAX_INPUT_CHAR 14

/* Top-level struct that stores all information
 * required for input_box display */
typedef struct input_box_graphics{
    /* Position of the upper-left corner of the Window*/
    Vector2 WindowPos;
    /* The size of the window, field x and y refer to width and height*/
    Vector2 WindowSize;
    /* The Color of the Input Box */
    Color BoxColor;
    /* The Color of the Text */
    Color TextColor;
    /* The Color of Annotation*/
    Color AnnotationColor;
    /* The Color of Outline of the Input Line*/
    Color OutlineColor;
    /* A string that contains the annotation to be displayed*/
    const char* Annotation;
} input_box_graphics_t;

/*
 * Parameters:
 *      Information for every field in the input_box_graphics struct 
 * 
 * Return:
 *      An allocated piece of memory for an input_box_graphics_t struct
 *      that contains all information given in the parameters
 */
input_box_graphics_t* newInputboxGraphics(Vector2 WindowPos, Vector2 WindowSize, Color BoxColor,
                                          Color TextColor, Color AnnotationColor, Color OutlineColor,
                                          const char* Annotation);


/*
 * Parameters:
 *      A 
 *      Information for every field in the input_box_graphics struct 
 * 
 * Return:
 *      SUCCESS on success
 * 
 * Function:
 *      Fills in every piece of information given in the parameters
 *      into the memory pointed to by the pointer parameter
 * 
 */
int initInputboxGraphics(input_box_graphics_t* pointer, Vector2 WindowPos, Vector2 WindowSize, 
                         Color BoxColor, Color TextColor, Color AnnotationColor, Color OutlineColor,
                         const char* Annotation);


/*
 * Parameters:
 *      A pointer to a piece of memory allocated to a input_box_graphics_t struct
 * 
 * Return:
 *      SUCCESS on success
 * 
 * Function:
 *      frees the piece of memory allocated to the input_box_graphics struct
 *      pointed to by the parameter
 */
int freeInputboxGraphics(input_box_graphics_t* pointer);

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
