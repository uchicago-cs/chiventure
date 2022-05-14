#ifndef MAP_GRAPHICS_H
#define MAP_GRAPHICS_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

// An include statement for open_world will be added when the map is 
// integrated to chiventure as a whole

/* This module will allow the designer to display their player's map */

/*
 * Main running function for MAP Graphics */

void runMAPGraphics();

// We use a Vector2 to mockup the coordinate struct

typedef struct map_graphics {
    Vector2 WindowPos;
    Vector2 WindowSize;
    const char* MapImagePath;
    const char* MapTitle;
} map_graphics_t;





#endif
