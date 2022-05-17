#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>


#define SCENE_CONTEXT_ID 0;


typedef struct scene_graphics scene_graphics_t;

struct scene_graphics {
    char* SceneName;
    char* ImagePath;
    Vector2 WindowPos;
    Vector2 WindowSize;
    Vector2 SceneSize;
    Vector2 PlayerPosition;
};

