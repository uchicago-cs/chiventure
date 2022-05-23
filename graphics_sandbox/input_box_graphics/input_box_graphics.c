#include "input_box.h"
#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_INPUT_CHAR 14


typedef struct input_box_graphics{
    Vector2 WindowPos;
    Vector2 WindowSize;
    Color BoxColor;
    Color TextColor;
    Color AnnotationColor;
    Color OutlineColor;
    const char* Annotation;
} input_box_graphics_t;

/* See input_box.h*/
input_box_graphics_t* newInputboxGraphics(Vector2 WindowPos, Vector2 WindowSize, Color BoxColor,
                                          Color TextColor, Color AnnotationColor, Color OutlineColor,
                                          const char* Annotation)
{
    input_box_graphics_t* res;
    res = malloc(sizeof(input_box_graphics_t));
    assert(res != NULL);
    initInputboxGraphics(res, WindowPos,WindowSize,BoxColor,TextColor,
                         AnnotationColor,OutlineColor,Annotation);
    return res;

}


/* See input_box.h*/
int initInputboxGraphics(input_box_graphics_t* pointer, Vector2 WindowPos, Vector2 WindowSize, 
                         Color BoxColor, Color TextColor, Color AnnotationColor, Color OutlineColor,
                         const char* Annotation)
{
    assert(pointer != NULL);
    pointer->WindowPos=WindowPos;
    pointer->WindowSize=WindowSize;
    pointer->BoxColor=BoxColor;
    pointer->TextColor=TextColor;
    pointer->AnnotationColor=AnnotationColor;
    pointer->OutlineColor=OutlineColor;
    pointer->Annotation=Annotation;
    return 1;
}

/* See input_box.h*/
int freeInputboxGraphics(input_box_graphics_t* pointer)
{
    assert(pointer != NULL);
    free(pointer);
    return 1;
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed()
{

    bool keyPressed = false;
    int key = GetKeyPressed();
    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}
