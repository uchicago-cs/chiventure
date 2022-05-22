#include "read_gdl.h"
#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


graphics_t* make_graphics(display_dimensions_t *dimensions, camera_t *camera,
    inventory_display_t *inventory, statistics_display_t *statistics)
{
    graphics_t *graphics;   
    int rc;

    graphics = (graphics_t*)malloc(sizeof(graphics_t));

    if (graphics == NULL)
    {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    rc = init_graphics(graphics, dimensions, camera, inventory, statistics);

    if(rc != SUCCESS)
    {
        fprintf(stderr,"Could not initialize graphics");
        return NULL;
    }

    return graphics;
}

int init_graphics(graphics_t *graphics, display_dimensions_t *dimensions, camera_t *camera,
    inventory_display_t *inventory, statistics_display_t *statistics)
{
    assert(graphics != NULL);

    graphics->dimensions = dimensions;
    graphics->camera = camera;
    graphics->inventory = inventory;
    graphics->statistics = statistics;

    return SUCCESS;
}

int free_graphics(graphics_t* graphics)
{

    assert(graphics != NULL);
    assert(graphics->dimensions != NULL);
    assert(graphics->camera != NULL);
    assert(graphics->inventory != NULL);
    assert(graphics->statistics != NULL);

    free_display_dimensions(graphics->dimensions);
    free_camera(graphics->camera);
    free_inventory_display(graphics->inventory);
    free_statistics_display(graphics->statistics);

    free(graphics);

    return SUCCESS;}

display_dimensions_t* make_display_dimensions(unsigned int width, unsigned int height)
{
    display_dimensions_t *dimensions;   
    int rc;

    dimensions = (display_dimensions_t*)malloc(sizeof(display_dimensions_t));

    if (dimensions == NULL)
    {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    rc = init_display_dimensions(dimensions, width, height);

    if(rc != SUCCESS)
    {
        fprintf(stderr,"Could not initialize display_dimensions");
        return NULL;
    }

    return dimensions;
}


int init_display_dimensions(display_dimensions_t *dimensions, unsigned int width, unsigned int height)
{
    assert(dimensions != NULL);

    dimensions->width = width;
    dimensions->height = height;

    return SUCCESS;
}

int free_display_dimensions(display_dimensions_t *dimensions)
{

    assert(dimensions != NULL);

    free(dimensions);

    return SUCCESS;
}

camera_t* make_camera(unsigned int width, unsigned int height)
{
    camera_t *camera;   
    int rc;

    camera = (camera_t*)malloc(sizeof(camera_t));

    if (camera == NULL)
    {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    rc = init_camera(camera, width, height);

    if(rc != SUCCESS)
    {
        fprintf(stderr,"Could not initialize camera");
        return NULL;
    }

    return camera;
}


int init_camera(camera_t *camera, unsigned int width, unsigned int height)
{
    assert(camera != NULL);

    camera->width = width;
    camera->height = height;

    return SUCCESS;
}

int free_camera(camera_t *camera)
{

    assert(camera != NULL);

    free(camera);

    return SUCCESS;
}

inventory_display_t* make_inventory_display(unsigned int rows, unsigned int columns, color color)
{
    inventory_display_t *inventory;   
    int rc;

    inventory = (inventory_display_t*)malloc(sizeof(inventory_display_t));

    if (inventory == NULL)
    {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    rc = init_inventory_display(inventory, rows, columns, color);

    if(rc != SUCCESS)
    {
        fprintf(stderr,"Could not initialize inventory_display");
        return NULL;
    }

    return inventory;
}

int init_inventory_display(inventory_display_t* inventory, unsigned int rows, unsigned int columns, color color)
{
    assert(inventory != NULL);

    inventory->rows = rows;
    inventory->columns = columns;
    inventory->color = color;

    return SUCCESS;
}

int free_inventory_display(inventory_display_t *inventory)
{

    assert(inventory != NULL);

    free(inventory);

    return SUCCESS;
}

statistics_display_t* make_statistics_display(corner corner, stats_t *statistics, unsigned int num_statistics, mode *mode)
{
    statistics_display_t *statistics_display;   
    int rc;

    statistics_display = (statistics_display_t*)malloc(sizeof(statistics_display_t));

    if (statistics_display == NULL)
    {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    rc = init_statistics_display(statistics_display, corner, statistics, num_statistics, mode);

    if(rc != SUCCESS)
    {
        fprintf(stderr,"Could not initialize statistics_display");
        return NULL;
    }

    return statistics_display;
}

int init_statistics_display(statistics_display_t* statistics_display, corner corner,
    stats_t *statistics,unsigned int num_statistics, mode mode)
{
    assert(statistics_display != NULL);

    statistics_display->corner = corner;
    statistics_display->statistics = statistics;
    statistics_display->num_statistics = num_statistics;
    statistics_display->mode = mode;

    return SUCCESS;
}

int free_statistics_display(statistics_display_t *statistics_display)
{

    assert(statistics_display != NULL);
    assert(statistics_display->statistics != NULL);

    free_stats(statistics_display->statistics);
    free(statistics_display);

    return SUCCESS;
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
    unsigned long inventory = hash("\"Inventory\":");
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
                                fscanf(gdl, "%u", &cols);
                                break;
                            case hash("color"):
                                fscanf(gdl, "%s", spec);
                                color = match_color(spec);
                                break;
                        }
                    }
                    inventory_display_t *inventory_display;
                    inventory = make_inventory_display(rows, cols, color);
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
    graphics_t *graphics = make_graphics(display_dimension, camera, inventory, statistics);
    return graphics
}
