#include "read_gdl.h"
#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

display_dimensions_t* init_display_dimensions(unsigned int width, unsigned int height)
{
    inventory_display_t *dimensions;                                               
    dimensions = (display_dimensions_t*)malloc(sizeof(display_dimensions_t));
    if (dimensions == NULL)
    {
        error("Could not allocate memory");
        return NULL;
    }
    unsigned int width, height;

    // todo                            
    return dimensions;
}

inventory_display_t* init_inventory_display(unsigned int row, unsigned int columns, color color)
{
    inventory_display_t *inventory;                                               
    inventory = (inventory_display_t*)malloc(sizeof(inventory_display_t));
    // todo                                       
    if (inventory == NULL)
    {
        error("Could not allocate memory");
        return NULL;
    }
    return inventory;
}

statistics_display_t* init_statistics_display(corner corner, stats_t *statistics, mode mode)
{
    statistics_display_t *statistics;                                               
    statistics = (statistics_display_t*)malloc(sizeof(statistics_display_t));
    if (statistics == NULL)
    {
        error("Could not allocate memory");
        return NULL;
    }
    // todo                                       
    return statistics;
}

// char* retrieve_input_string()

graphics_t* process_gdl(FILE *gdl)
{
    // initialize graphics struct
    graphics_t *gdl_graphics;
    gdl_graphics = (graphics_t*)malloc(sizeof(graphics_t));

    // define info strings to compare to
    char *dimensions_str =  "\"Display_Dimensions\":";
    char *inventory_str = "\"Inventory\":";
    char *statistics_str = "\"Statistics\":";
    char *camera_str = "\"Camera_Size\":";

    // throw away top "{"
    char *top;
    scanf("%s", &top);

    while (scanf("%s") != NULL) {
        // pull key
        char *key;
        scanf("%s", &key);

        // check which info to process and fill
        if (strcmp(key, dimensions_str) == 0) {
            // throw away top "{"
            scanf("%s", &top);
            char *curr_str;
            // loop through to pull info until second "}"
            char *end = "}";
            // define known info
            char *width_str = "\"width\":";
            char *height_str = "\"height\":";
            unsigned int width, height;
            // pull and set info
            while (strcmp(curr_str, end) != 0) {
                scanf("%s", &curr_str);
                if (strcmp(width_str, curr_str) == 0) {
                    scanf("%d", &width);
                } else if (height_str, strcmp(curr_str) == 0) {
                    scanf("%d", &height);
                }
                else {
                    error("Unknown parameter in Display_Dimensions");
                    return NULL;
                }
            }
        } 
    }
}


