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


/*
 * Matches a string of a color to a background color implementable in Raylib
 *
 * Parameters:
 * - the string name for the color
 *
 * Returns:
 * - an integer whose value corresponds to the color
 */
int match_color(char *color)
{
    char* colors[] = {"White", "Gray", "Black", "Red", "Blue", "Green", "Yellow", "Orange", "Purple", "Pink"};
    for(int i = 0 i < 10; i++) {
        if (strcmp(colors[i], color) == 0) {
            return i;
        }
    }
    fprintf(stderr, "invalid input color");
    exit(1);
}


/*
 * Matches a string for a corner to an implementable value
 *
 * Paramters:
 * - the string name of the corner
 *
 * Returns:
 * - an integer with the value of the corner
 */
int match_corner(char *corner)
{
    char *corners[] = {"Top Left", "Top Right", "Bottom Left", "Bottom Right"};
    for(int i = 0; i < 4; i ++) {
        if (strcmp(corners[i], corner) == 0) {
            return i;
        }
    }
    fprintf(stderr, "invalid input corner");
    exit(1);
} 


graphics_t* read_gdl()
{
    // Open the GDL
    FILE *gdl;
    gdl = fopen("gdl.txt","r"); // could read from any specific location

    // Define information strings for comparisons
    unsigned long display = hash("\"Display_Dimensions\":");
    unsigned long camera = hash("\"Camera\":");
    unsigned long inventory hash("\"Inventory\":");
    // wishlist item    unsigned long map = hash("\"map\":");
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
    int at_end = 0;
    while (!at_end) {

        // pull title
        char title[100];
        if (fscanf(gdl, "%s", &title) != EOF) {

            // map title to structure 
            unsigned long h = hash(title);
        
            switch (h) {
                case display: case camera:
                    getc(gdl);
                    fscanf(gdl, "%s", spec);
                    if (strcmp(spec, "\"width\"") == 0) {
                        fscanf(gdl, "%u", width);
                        fscanf(gdl, "%*s %d", height);
                    } else {
                        fscanf(gdl, "%u", height);
                        fscanf(gdl, "%*s %d", width); 
                    }
                    if (h == display) {
                        display_dimensions_t *display_dimension;
                        display_dimension = make_display_dimensions(width, height);
                    } else {
                        camera_t *camera;
                        camera = make_camera(width, height);
                    }
                    break;
                case inventory:
                    getc(gdl);
                    for(int i = 0; i < 3; i++) {
                        fscanf(gdl, "%s", spec);
                        switch (hash(spec)) {
                            case hash("rows"):
                                fscanf(gdl, "%u", &rows);
                                break;
                            case hash("columns"):
                                fscanf(gdl, "%u", &columns);
                                break;
                            case hash("color"):
                                fscanf(gdl, "%s", spec);
                                color = match_color(spec);
                                break;
                        }
                    }
                    inventory_display_t *inventory_display;
                    inventory = make_inventory_display(rows, columns, color);
                    break;
                // case map: is a wishlist item
                case statistics:
                    getc(gdl);
                    for(int i = 0; i < 3; i++) {
                        fscanf(gdl, "%s", spec);
                        switch (hash(spec)) {
                            case hash("corner"):
                                corner = match_corner(spec);
                                break;
                            case hash(names):
                                // where are starting stats specified?
                        }
                    }
            }
            // to pass over the closing brace "}"
            getc(gdl);
        } else {
            at_end = 1;
        }
    }
    graphics = make_graphics(display_dimensions_t *dimensions, camera_t *camera, inventory_display_t *inventory, statistics_display_t *statistics);
    return graphics
}
