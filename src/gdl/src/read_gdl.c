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
    // todo                            
    return dimensions;
}


inventory_display_t* init_inventory_display(unsigned int row, unsigned int columns, color color)
{
    inventory_display_t *inventory;                                               
    inventory = (inventory_display_t*)malloc(sizeof(inventory_display_t));
    if (inventory == NULL)
    {
        error("Could not allocate memory");
        return NULL;
    }
    // todo
    return inventory;
}


statistics_display_t* init_statistics_display(corner corner, stats_t *statistics, mode *mode)
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

/* 
 * Including here a has function: djb2, for an easy compairison of strings.
 * This implementation was pulled from http://www.cse.yorku.ca/~oz/hash.html.
 */
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


graphics_t* read_gdl();
{
    // Open the GDL
    FILE *gdl;
    gdl = fopen("gdl.txt","r"); // could read from any specific location

    // Initialize graphics struct
    graphics_t *graphics;
    graphics = (graphics_t*)malloc(sizeof(graphics_t));

    // Define information strings for comparisons
    unsigned long display = hash("\"Display_Dimensions\":");
    unsigned long camera = hash("\"Camera\":");
    unsigned long inventory hash("\"Inventory\":");
    unsigned long map = hash("\"map\":");
    unsigned long statistics = hash("\"Statistics\":");

    // Define useful variables for the reading function
    unsigned int width;
    unsigned int height;
    unsigned int rows;
    unsigned int cols;
    color color;
    corner corner;
    char spec[20];

    // Skip over top "{"
    getc(gdl);

    // read through the file
    while (1) {

        // pull title
        char title[100];
        if (fscanf(gdl, "%s", &title) != EOF) {

            // map title to structure 
            unsigned long h = hash(title);
        
            switch (h) {
                case display: case camera:
                    getc(gdl);
                    fscanf(gdl, "%s", &spec);
                    if (strcmp(spec, "\"width\"") == 0) {
                        fscanf(gdl, "%u", width);
                        fscanf(gdl, "%*s %d", height);
                    } else {
                        fscanf(gdl, "%u", height);
                        fscanf(gdl, "%*s %d", width); 
                    }
                    if (h == display) {
                        make_display_dimensions(width, height);
                    } else {
                        make_camera(width, height);
                    }
                    break;
                case inventory:
                    getc(gdl);
                    for(int i = 0; i < 3; i++) {
                        fscanf(gdl, "%s", &spec);
                
                case map:
                    getc(gdl)
                    fscanf(gdl, "%s", &spec);
                        
                case statistics:
            }
        }   
/*
if (strcmp(title, dimensions_str) == 0) {
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
*/
    }
    fclose(gdl);
}
