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
#include "map_graphics.h"
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
} window_type;

/* Contains the height and width of the window as specified by a game author */
typedef struct display_dimensions {
    unsigned int width;
    unsigned int height;
} display_dimensions_t;

/* This general windows struct that contains information read from the GDL */ 
typedef struct windows {
    display_dimensions_t dimensions; // window width and height
    inventory_display_t inventory_display; // author preferences for inventory
// to be developed    statistics_display_t statistics_display
} windows_t;

/*
typedef union module_data {
    npc_graphics_t npc;
    //input_box_graphics_t input_box;
    //scene_graphics_t scene;
    //inventory_graphics_t inventory;
    //quest_graphics quest;
    //map_graphics map;
} module_data_t;
*/ 

/* This struct contains the information of every window in the split screen
 * Iterative through all linked structs to get the full picture*/
struct splitscreen_info {
    /* For documentation purposes, we assign each struct an index
     * that starts from 0 and increments by 1 each time*/
    unsigned index;
    /* An Enum on the type of the screen*/
    type_subscreen_t type;
    /* The following two fields define the x and y positions of the
     * upper-left corner of the window, in percentages to the whole screen */
    double xpos;  //!!! Maybe we can put this into a single rectangle
    double ypos;
    /* The following two fields define the horizontal and vertical
     * lengths of the window, in percentages to the whole screen */
    double horizontal_length;
    double vertical_length;
    /* A rectangle (of percentages) that specifies the region to print*/
    splitscreen_info_t *next;
    /* A pointer to the Union data struct that contains 
     * the info for individual modules */
    module_data_t* module_data;
};

#endif
