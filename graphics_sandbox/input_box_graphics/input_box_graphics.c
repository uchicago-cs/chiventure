#include "input_box_graphics.h"
#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>



/* See input_box.h*/
input_box_graphics_t* newInputboxGraphics(Vector2 WindowPos, Vector2 WindowSize, Color BoxColor,
                                          Color TextColor, Color AnnotationColor, Color OutlineColor,
                                          const char* Annotation)
{
    input_box_graphics_t* res;
    res = malloc(sizeof(input_box_graphics_t));
    assert(res != NULL);
    int rc = initInputboxGraphics(res, WindowPos,WindowSize,BoxColor,TextColor,
                         AnnotationColor,OutlineColor,Annotation);
    assert(rc == SUCCESS);
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
    return SUCCESS;
}

/* See input_box.h*/
int freeInputboxGraphics(input_box_graphics_t* pointer)
{
    assert(pointer != NULL);
    free(pointer);
    return SUCCESS;
}


