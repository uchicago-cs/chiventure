#include <criterion/criterion.h>                                                
#include <stdlib.h>                                                             
#include <stdbool.h>                                                            
#include "read_gdl.h" 

/* Checks that new_inventory_display properly mallocs and inits values for an
 * inventory_display_t struct */
Test(inventory, new)
{
    unsigned int rows = 3;
    unsigned int columns = 10;
    color c = YELLOW;

    inventory_display_t *inventory;
    inventory = new_inventory_display(rows,columns,c);

    cr_assert_not_null(inventory,"make_inventory_display() failed");
    
    cr_assert_eq(inventory->rows,3,"make_inventory_display() didn't set rows");
    cr_assert_eq(inventory->columns,10,"make_inventory_display() didn't set columns");
    cr_assert_eq(inventory->color,YELLOW,"make_inventory_display() didn't set color");
}

/* Checks that init_inventory_display properly inits values for an 
 * inventory_display_t struct */
Test(inventory, init)
{
    unsigned int rows = 3;
    unsigned int columns = 10;
    color c = YELLOW;

    inventory_display_t inventory;
    int rc;

    rc = init_inventory_display(&inventory,rows,columns,c);

    cr_assert_eq(rc, SUCCESS, "init_inventory_display() failed");

    cr_assert_eq(inventory.rows, 3,
                "init_inventory_display() didn't set rows");
    cr_assert_eq(inventory.columns, 10,
                "init_inventory_display() didn't set columns");
    cr_assert_eq(inventory.color, YELLOW,
                "init_inventory_display() didn't set color");
}

/* Checks that free_inventory_display properly frees memory used for an 
 * inventory_display_t struct */
Test(inventory, free)
{
    unsigned int rows = 3;
    unsigned int columns = 10;
    color c = YELLOW;
    int rc;

    inventory_display_t *inventory;
    inventory = new_inventory_display(rows,columns,c);

    cr_assert_not_null(inventory,"make_inventory_display()");
    
    rc = free_inventory_display(inventory);

    cr_assert_eq(rc,SUCCESS,"free_inventory_display() failed");
}
