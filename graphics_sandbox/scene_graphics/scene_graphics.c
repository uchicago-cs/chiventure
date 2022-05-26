#include "scene_graphics.h"
#include "raylib.h"

/* See scene_graphics.h*/
scene_graphics_t* new_scene_graphics(char* SceneName, char* ImagePath, Vector2 WindowPos,
                       Vector2 WindowSize, Vector2 SceneSize, Vector2 PlayerPosition)
{
    scene_graphics_t* s;
    s = malloc(sizeof(scene_graphics_t));
    s->SceneName=SceneName;
    s->ImagePath=ImagePath;
    s->WindowPos=WindowPos;
    s->WindowSize=WindowSize;
    s->SceneSize=SceneSize;
    s->PlayerPosition=PlayerPosition;

    return s;
    
}

/* See scene_graphics.h*/
int free_scene_graphics(scene_graphics_t* SceneGraphics)
{
    free(SceneGraphics);
    return SUCCESS;
}

