#ifndef PARSE_H
#define PARSE_H

#include "raylib.h"


typedef struct graphics_component graphics_component_t;

typedef enum {
    NPC_GRAPHICS,
    INPUT_BOX,
    INVENTORY_GRAPHICS,
    SCENE_GRAPHICS,
    QUEST_GRAPHICS,
} component_name_t;

typedef struct {
    component_name_t component_name;
    Rectangle position_and_size;
} graphics_component_t;




#endif
