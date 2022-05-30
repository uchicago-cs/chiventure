#ifndef MAP_GRAPHICS_H
#define MAP_GRAPHICS_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include "common.h"

#define MAP_CONTEXT_ID 1


// An include statement for open_world will be added when the map is 
// integrated to chiventure as a whole


// We use a Vector2 to mockup the coordinate struct

typedef struct map_graphics {
    char* title;
    char* image_path;
    Vector2 WindowPos;
    Vector2 display_dimensions; //read this from gdl!
    Vector2 MaxCoordinates;
} map_graphics_t;

/*
 * allocates and initializes a new map struct
 *
 * Parameters:
 * -
 *
 * Returns:
 * a pointer to the freshly allocated mao struct
 */
map_graphics_t* new_map_graphics(char *title, char *image_path); // to be filled


/*
 * frees a map_graphics struct from the heap
 *
 * Parameters:
 * - a map graphics struct
 *
 * Returns:
 * - SUCCESS if success
 */
int free_map_graphics(map_graphics_t *map_graphics);


/*
 * draw the map to the screen
 *
 * Parameters:
 * - a map_graphics struct
 *
 * Returns:
 * - SUCCESS upon success
 */
int draw_map_graphics(map_graphics_t *info);


#endif
