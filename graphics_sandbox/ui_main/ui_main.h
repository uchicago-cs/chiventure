/*
 * This module defines a window struct. The window struct contains information
 * pertaining to the custom GDL file that authors write for graphics
 */ 

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include "raylib.h"
#include "input_box.h"
#include "inventory_graphics.h"
#include "npc_graphics.h"
#include "quest_graphics.h"
#include "scene_graphics.h"
#include "read_gdl.h"

/*
 * These are the various types of windows that a user can generate. By type, we
 * mean what information the subscreen contains.
 */
typedef enum window_type {
    SCENE,
    NPC,
    INVENTORY,
    MAP,
    QUESTS,
    INPUT_BOX,
    EFFECTS,
    CLASS,
    MOVES,
    SKILLS,
    STATS,
} window_type_t;

typedef union windows {
    npc_graphics_t npc_graphics;
    map_graphics_t map_graphics;
    quest_graphics_t quest_graphics;
    input_box_graphics_t input_box_graphics;
    inventory_graphics_t inventory_graphics;
    //To Add
} windows_t;

typedef struct ui_linkedlist ui_linkedlist_t;

struct ui_linkedlist {
    window_type_t WindowType;
    window_t* Window;
    ui_linkedlist_t* next;
};

#endif
