#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "read_gdl.h"

Test(display_dimensions, new)
{
    unsigned int width = 500;
    unsigned int height = 400;

    display_dimensions_t *dimensions;
    dimensions =  new_display_dimensions(width,height);

    cr_assert_not_null(dimensions, "make_display_dimensions() failed");
    
    cr_assert_eq(dimensions->width,500,"make_display_dimensions() didn't set width");
    cr_assert_eq(dimensions->height,400,"make_display_dimensions() didn't set height");
}

Test(display_dimensions, free)
{
    unsigned int width = 500;
    unsigned int height = 400;
    int rc;

    display_dimensions_t *dimensions;
    dimensions = new_display_dimensions(width,height);
    
    cr_assert_not_null(dimensions, "make_display_dimensions() failed");
    
    rc = free_display_dimensions(dimensions);
    
    cr_assert_eq(rc,SUCCESS,"free_display_dimensions() failed");
}



