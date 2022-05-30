#ifndef SCENE_GRAPHICS_H
#define SCENE_GRAPHICS_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include "common.h"


typedef struct scene_graphics scene_graphics_t;

struct scene_graphics {
    char* SceneName;
    char* ImagePath;
    Vector2 WindowPos;
    Vector2 WindowSize;
    Vector2 SceneSize;
    Vector2 PlayerPosition;
};

/*
 * Parameters:
 *      SceneName: a string that gives the title of the scene
 *      ImagePath: a string that specifies the path to find the scene texture
 *      WindowPos: a 2-d vector that specifies the position of the upper-left corner of the window
 *      WindowSize: a 2-d vector that stores the width (x) and height (y) of the window
 *      SceneSize: a 2-d vector that stores the width(x) and height(y) of the scene/camera
 *      PlayerPosition: a 2-d vector that stores the position of the player
 * 
 * Returns:
 *      a pointer to a scene_graphics_t struct that contains information from the parameters
 *
 */
scene_graphics_t* new_scene_graphics(char* SceneName, char* ImagePath, Vector2 WindowPos,
                       Vector2 WindowSize, Vector2 SceneSize, Vector2 PlayerPosition);



/*
 * Parameters:
 *     SceneGraphics: a pointer to the scene_graphics_t struct to be freed
 * 
 * Returns:
 *      SUCCESS on success 
 */
int free_scene_graphics(scene_graphics_t* SceneGraphics);

/*
 * Produces a visualization of the current scene in the game
 *
 * Parameters:
 * - scene graphics struct
 *
 * Returns:
 * - SUCCESS upon success
 */
int draw_scene_graphics(scene_graphics_t* scene_graphics);

#endif
