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
    char* image_path; // the file path where the image is located
    Vector2 window_size; // refers to display dimensions specified in the GDL
    Vector2 player_position; // what is this? - waht about room_t *curr_room?
} scene_graphics_t;

// to be written
// scene_graphics_t* new_scene_graphics(char *title, char *image_path, graphics_t *graphics, room_t *curr_room);


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
void runSceneGraphics(scene_graphics_t* scene_graphics);


#endif
