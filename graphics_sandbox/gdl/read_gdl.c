#include "read_gdl.h"
#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


graphics_t* new_graphics(display_dimensions_t *dimensions, camera_t *camera,
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

    return SUCCESS;
}


display_dimensions_t* new_display_dimensions(unsigned int width, unsigned int height)
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


camera_t* new_camera(unsigned int width, unsigned int height)
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


inventory_display_t* new_inventory_display(unsigned int rows, unsigned int columns, color color)
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


statistics_display_t* new_statistics_display(corner corner, stats_t *statistics, unsigned int num_statistics, mode mode)

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
