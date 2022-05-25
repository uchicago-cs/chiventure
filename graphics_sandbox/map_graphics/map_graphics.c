#include "map_graphics.h"
#include "raylib.h"
#include <assert.h>


Vector2 getCurrentCoordinate() {
    //Todo
    return GetMousePosition();
}

/* See map_graphics.h for documentation */ 
map_graphics_t* new_map_graphics(char *title, char *image_path)
{
    map_graphics_t *map;
    map = (map_graphics_t*)malloc(sizeof(map_graphics_t));

    map->title = title;
    map->image_path = image_path;

    // needs to be filled -> there should be a call to a gdl function here

    return map;
}

/* See map_graphics.h for documentation */ 
int free_map_graphics(map_graphics_t *map_graphics)
{
    assert(map_graphics!=NULL);
    // this may also need some editing

    free(map_graphics);
    return SUCCESS;
}



