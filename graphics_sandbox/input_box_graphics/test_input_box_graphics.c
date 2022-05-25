#include "input_box_graphics.h"
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>

/* Testing newInputboxGraphics*/
Test(input_box_graphics, new)
{
    input_box_graphics_t* i;
    i = newInputboxGraphics((Vector2){100,110},(Vector2){500,520},BLACK,
                            WHITE,GREEN,DARKGREEN,"I am annotation");
    cr_assert_not_null(i, "input_box_graphics failed to allocate memory");
    cr_assert_eq(i->WindowPos.x, 100, "input_box_graphics failed to set WindowPos.x");
    cr_assert_eq(i->WindowPos.y, 110, "input_box_graphics failed to set WindowPos.y");
    cr_assert_eq(i->WindowSize.x, 500, "input_box_graphics failed to set WindowSize.x");
    cr_assert_eq(i->WindowSize.y, 520, "input_box_graphics failed to set WindowSize.y");
    cr_assert_eq(i->BoxColor.r,0,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i->BoxColor.g,0,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i->BoxColor.b,0,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i->BoxColor.a,255,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i->TextColor.r,255,"input_box_graphics failed to set TextColor");  
    cr_assert_eq(i->TextColor.g,255,"input_box_graphics failed to set TextColor"); 
    cr_assert_eq(i->TextColor.b,255,"input_box_graphics failed to set TextColor"); 
    cr_assert_eq(i->TextColor.a,255,"input_box_graphics failed to set TextColor"); 
    cr_assert_eq(i->AnnotationColor.r,0,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i->AnnotationColor.g,228,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i->AnnotationColor.b,48,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i->AnnotationColor.a,255,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i->OutlineColor.r,0,"input_box_graphics failed to set OutlineColor"); 
    cr_assert_eq(i->OutlineColor.g,117,"input_box_graphics failed to set OutlineColor"); 
    cr_assert_eq(i->OutlineColor.b,44,"input_box_graphics failed to set OutlineColor"); 
    cr_assert_eq(i->OutlineColor.a,255,"input_box_graphics failed to set OutlineColor"); 
}

/* Testing initInputboxGraphics*/
Test(input_box_graphics, init)
{
    input_box_graphics_t i;
    int rc = initInputboxGraphics(&i,(Vector2){100,110},(Vector2){500,520},BLACK,
                                  WHITE,GREEN,DARKGREEN,"I am annotation");
    cr_assert_eq(rc,SUCCESS,"initInputboxGraphics has failed");
    cr_assert_eq(i.WindowPos.x, 100, "input_box_graphics failed to set WindowPos.x");
    cr_assert_eq(i.WindowPos.y, 110, "input_box_graphics failed to set WindowPos.y");
    cr_assert_eq(i.WindowSize.x, 500, "input_box_graphics failed to set WindowSize.x");
    cr_assert_eq(i.WindowSize.y, 520, "input_box_graphics failed to set WindowSize.y");
    cr_assert_eq(i.BoxColor.r,0,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i.BoxColor.g,0,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i.BoxColor.b,0,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i.BoxColor.a,255,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i.TextColor.r,255,"input_box_graphics failed to set TextColor");  
    cr_assert_eq(i.TextColor.g,255,"input_box_graphics failed to set TextColor"); 
    cr_assert_eq(i.TextColor.b,255,"input_box_graphics failed to set TextColor"); 
    cr_assert_eq(i.TextColor.a,255,"input_box_graphics failed to set TextColor"); 
    cr_assert_eq(i.AnnotationColor.r,0,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i.AnnotationColor.g,228,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i.AnnotationColor.b,48,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i.AnnotationColor.a,255,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i.OutlineColor.r,0,"input_box_graphics failed to set OutlineColor"); 
    cr_assert_eq(i.OutlineColor.g,117,"input_box_graphics failed to set OutlineColor"); 
    cr_assert_eq(i.OutlineColor.b,44,"input_box_graphics failed to set OutlineColor"); 
    cr_assert_eq(i.OutlineColor.a,255,"input_box_graphics failed to set OutlineColor"); 

}

/* Testing freeInputboxGraphics*/
Test(input_box_graphics, free)
{
    input_box_graphics_t* i;
    i = newInputboxGraphics((Vector2){100,110},(Vector2){500,520},BLACK,
                            WHITE,GREEN,DARKGREEN,"I am annotation");
    cr_assert_not_null(i, "input_box_graphics failed to allocate memory");
    cr_assert_eq(i->WindowPos.x, 100, "input_box_graphics failed to set WindowPos.x");
    cr_assert_eq(i->WindowPos.y, 110, "input_box_graphics failed to set WindowPos.y");
    cr_assert_eq(i->WindowSize.x, 500, "input_box_graphics failed to set WindowSize.x");
    cr_assert_eq(i->WindowSize.y, 520, "input_box_graphics failed to set WindowSize.y");
    cr_assert_eq(i->BoxColor.r,0,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i->BoxColor.g,0,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i->BoxColor.b,0,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i->BoxColor.a,255,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i->TextColor.r,255,"input_box_graphics failed to set TextColor");  
    cr_assert_eq(i->TextColor.g,255,"input_box_graphics failed to set TextColor"); 
    cr_assert_eq(i->TextColor.b,255,"input_box_graphics failed to set TextColor"); 
    cr_assert_eq(i->TextColor.a,255,"input_box_graphics failed to set TextColor"); 
    cr_assert_eq(i->AnnotationColor.r,0,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i->AnnotationColor.g,228,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i->AnnotationColor.b,48,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i->AnnotationColor.a,255,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i->OutlineColor.r,0,"input_box_graphics failed to set OutlineColor"); 
    cr_assert_eq(i->OutlineColor.g,117,"input_box_graphics failed to set OutlineColor"); 
    cr_assert_eq(i->OutlineColor.b,44,"input_box_graphics failed to set OutlineColor"); 
    cr_assert_eq(i->OutlineColor.a,255,"input_box_graphics failed to set OutlineColor"); 

    int rc;
    rc = freeInputboxGraphics(i);
    cr_assert_eq(rc,SUCCESS,"freeInputboxGraphics failed");

}