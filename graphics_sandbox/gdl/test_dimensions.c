#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "read_gdl.h"

/*Checks that new_display_dimensions() properly mallocs and inits a new
 * display_dimensions_t struct */
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

/* Checks that init_display_dimensions properly inits values for a 
 * display_dimensions_t struct */
Test(display_dimensions, init)
{
    unsigned int width = 500;
    unsigned int height = 400;

    int rc;
    display_dimensions_t *dimensions;

    rc = init_display_dimensions(dimensions,width,height);
    
    cr_assert_eq(rc, SUCCESS, "init_display_dimensions() failed");

    cr_assert_eq(dimensions->width,500,
                "init_display dimensions didn't set width");
    cr_assert_eq(dimensions->height,400,
                "init_display_dimensions didn't set height");
}


/*Checks that free_display_dimensions() properly frees memory used for 
 * display_dimensions_t struct */
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



