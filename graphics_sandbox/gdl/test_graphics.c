#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "read_gdl.h"

/*Checks that new_graphics() properly mallocs and inits values for a 
 * graphics_t struct */
Test(graphics, new)
{
    stats_global_t *global_stat = stats_global_new("Health",10.0);
    stats_t *stat = stats_new(global_stat,10.0);

    
    statistics_display_t *stats = new_statistics_display(TOP_LEFT,stat,1,NUMERICAL);
    display_dimensions_t *dimensions = new_display_dimensions(500,400);
    inventory_display_t *inventory = new_inventory_display(3,10,RED);
    camera_t *camera = new_camera(300,300);
    
    graphics_t *graphics;
    graphics = new_graphics(dimensions,camera,inventory,stats);

    cr_assert_not_null(graphics,"new_graphics() failed");

    cr_assert_eq(graphics->statistics->corner,TOP_LEFT,
                "new_graphics() didn't set statistics corner");
    cr_assert_eq(graphics->statistics->mode, NUMERICAL,
                "new_graphics() didn't set statistics mode");
    cr_assert_eq(graphics->statistics->num_statistics,1,
                "new_graphics() didn't set statistics num_statistics");
    cr_assert_eq(graphics->statistics->statistics->max,10,
                "new_graphics() didn't set statistics stat_t field");
    
    cr_assert_eq(graphics->camera->width,300,
                "new_graphics() didn't set camera width");
    cr_assert_eq(graphics->camera->height,300,
                "new_graphics() didn't set camera height");

    cr_assert_eq(graphics->dimensions->width,500,
                "new_graphics() didn't set dimensions width");
    cr_assert_eq(graphics->dimensions->height,400,
                "new_graphics() didn't set dimensions height");

    cr_assert_eq(graphics->inventory->rows,3,
                "new_graphics() didn't set inventory rows");
    cr_assert_eq(graphics->inventory->columns,10,
                "new_graphics() didn't set inventory columns");
    cr_assert_eq(graphics->inventory->color, RED,
                "new_graphics() didn't set inventory color");
}

/*Checks that init_graphics() properly inits values for graphics_t struct */
Test(graphics, init)
{
    stats_global_t *global_stat = stats_global_new("Health",10.0);              
    stats_t *stat = stats_new(global_stat,10.0);                                
                                                                                  
                                                                                  
    statistics_display_t *stats = new_statistics_display(TOP_LEFT,stat,1,NUMERICAL);
    display_dimensions_t *dimensions = new_display_dimensions(500,400);         
    inventory_display_t *inventory = new_inventory_display(3,10,RED);           
    camera_t *camera = new_camera(300,300);                                     
                                                                                 
    graphics_t graphics;
    int rc;

    rc = init_graphics(&graphics,dimensions,camera,inventory,stats);

    cr_assert_eq(rc,SUCCESS,"init_graphics() failed");

    cr_assert_eq(graphics.statistics->corner,TOP_LEFT,                         
                "init_graphics() didn't set statistics corner");                 
    cr_assert_eq(graphics.statistics->mode, NUMERICAL,                         
                "init__graphics() didn't set statistics mode");                   
    cr_assert_eq(graphics.statistics->num_statistics,1,                        
                "init_graphics() didn't set statistics num_statistics");         
    cr_assert_eq(graphics.statistics->statistics->max,10,                      
                "init_graphics() didn't set statistics stat_t field");           
                                                                                 
    cr_assert_eq(graphics.camera->width,300,                                   
                "init_graphics() didn't set camera width");                      
    cr_assert_eq(graphics.camera->height,300,                                  
                "init_graphics() didn't set camera height");                     
                                                                                
    cr_assert_eq(graphics.dimensions->width,500,                               
                "init_graphics() didn't set dimensions width");                  
    cr_assert_eq(graphics.dimensions->height,400,                              
                "init_graphics() didn't set dimensions height");                 
                                                                                 
    cr_assert_eq(graphics.inventory->rows,3,                                   
                "init_graphics() didn't set inventory rows");                    
    cr_assert_eq(graphics.inventory->columns,10,                               
                "init_graphics() didn't set inventory columns");                 
    cr_assert_eq(graphics.inventory->color, RED,                               
                "init_graphics() didn't set inventory color");                   
}

/* Checks that free_graphics properly frees memory used for graphics_t struct*/
Test(graphics, free)
{
    stats_global_t *global_stat = stats_global_new("Health",10.0);              
    stats_t *stat = stats_new(global_stat,10.0);                                
    
    statistics_display_t *stats = new_statistics_display(TOP_LEFT,stat,1,NUMERICAL);
    display_dimensions_t *dimensions = new_display_dimensions(500,400);         
    inventory_display_t *inventory = new_inventory_display(3,10,RED);           
    camera_t *camera = new_camera(300,300);                                     
                                                                                  
    graphics_t *graphics;                                                       
    int rc;

    graphics = new_graphics(dimensions, camera, inventory, stats);

    rc = free_graphics(graphics);

    cr_assert_eq(rc,SUCCESS,"free_graphics() failed");
}
