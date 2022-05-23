#include "input_box_graphics.h"
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>


Test(input_box_graphics, new)
{
    input_box_graphics* i;
    i = newInputboxGraphics((Vector2){100,110},(Vector2){500,520},BLACK,
                            WHITE,GREEN,DARKGREEN,"I am annotation");
    cr_assert_not_null(i, "input_box_graphics failed to allocate memory");
    cr_assert_eq(i->WindowPos.x, 100, "input_box_graphics failed to set WindowPos.x");
    cr_assert_eq(i->WindowPos.y, 110, "input_box_graphics failed to set WindowPos.y");
    cr_assert_eq(i->WindowSize.x, 500, "input_box_graphics failed to set WindowSize.x");
    cr_assert_eq(i->WindowSize.y, 520, "input_box_graphics failed to set WindowSize.y");
    cr_assert_eq(i->BoxColor,BLACK,"input_box_graphics failed to set BoxColor");
    cr_assert_eq(i->TextColor,WHITE,"input_box_graphics failed to set TextColor");  
    cr_assert_eq(i->AnnotationColor,GREEN,"input_box_graphics failed to set AnnotationColor"); 
    cr_assert_eq(i->OutlineColor,DARKGREEN,"input_box_graphics failed to set OutlineColor"); 
}


Test(input_box_graphics, init)
{


}

Test(input_box_graphics, free)
{
    

}