#include <criterion/criterion.h>                                                
#include <stdlib.h>                                                             
#include <stdbool.h>                                                            
#include "read_gdl.h" 

Test(inventory, new)
{
    unsigned int rows = 3;
    unsigned int columns = 10;
    color c = YELLOW;

    inventory_display_t inventory;
    inventory = make_inventory_display(rows,columns,c);

    cr_assert_not_null(inventory,"make_inventory_display() failed");
    
    cr_assert_eq(inventory->rows,3,"make_inventory_display() didn't set rows");
    cr_assert_eq(inventory->columns,10,"make_inventory_display() didn't set columns");
    cr_assert_eq(inventory->color,YELLOW,"make_inventory_display() didn't set color");
}

Test(inventory, free)
{
    unsigned int rows = 3;
    unsigned int columns = 10;
    color c = YELLOW;
    int rc;

    inventory_display_t inventory;
    inventory = make_inventory_display(rows,columns,c);

    cr_assert_not_null(inventory,"make_inventory_display()");
    
    rc = free_inventory_display(inventory);

    cr_assert_eq(rc,SUCCESS,"free_inventory_display() failed");
}
