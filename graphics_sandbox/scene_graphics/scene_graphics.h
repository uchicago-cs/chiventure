#ifndef SCENE_GRAPHICS_H
#define SCENE_GRAPICS_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include "read_gdl.h"
#include "game.h"


#define SCENE_CONTEXT_ID 0;


/* Defines the information required to display a scene */
struct scene_graphics {
    char* title;
    char* image_path; 
    Vector2 window_size; 
    Vector2 player_position; 
} scene_graphics_t;


/*
 * Allocates and initializes a new scene struct
 *
 * Parameters:
 * - a title for the scene
 * - the file path where the scene is located
 * - a graphics struct
 *
 * Returns:
 * - a pointer to a scene struct with initialzed fields on the heap
 */
scene_graphics_t* new_scene_graphics(char *title, char *image_path, graphics_t *graphics);


/*
 * Frees a scene struct
 *
 * Parameters:
 * - the scene struct
 *
 * Returns:
 * - nothing - functions as a side effect
 */
void free_scene_graphics(scene_graphics_t* scene_graphics);


/*
 * Produces a visualization of the current scene in the game
 *
 * Parameters:
 * - scene graphics struct
 *
 * Returns:
 * - nothing - functions as a side effect
 */
void draw_scene_graphics(scene_graphics_t* scene_graphics);


#endif
