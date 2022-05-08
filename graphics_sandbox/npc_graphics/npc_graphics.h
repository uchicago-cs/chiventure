#ifndef NPC_GRAPHICS_H
#define NPC_GRAPHICS_H

/* This would be implemented in part2
 *  When we want to integrate this feature
 *  to the game*/
//#include "npc/npc.h"


typedef struct npc_action npc_action_t;
/*
 * A hashed/linked list that uses action_name as a key
 * and the path to the image and the frame numebrs of
 * that image as the values
 */
struct npc_action {
    /* The name of the action*/
    char* action_name;
    /* The path to the multi-frame image storing that action*/
    char* action_image_path;
    /* The total number of frames in that multi-frame image*/
    unsigned frame_number;
    /* The frequency by which the frames update */
    double switch_frequency;
    /* Pointer to the next linked action component*/
    npc_action_t* next;
};

typedef struct npc_line npc_line_t;
/*
 * A hashed/linked list that uses line_name as a key
 * and the string that represents the line
 */
struct npc_line {
    /* The name of the line*/
    char* line_name;
    /* The line that would be printed out in the textbox*/
    const char* line;
    /* Pointer to the next lineked line compoenent*/
    npc_line_t* next;
};

typedef struct npc_graphics npc_graphics_t;

struct npc_graphics {
    /* The name of the NPC*/
    char* npc_name;
    
    /* We want to show more info about the
       the NPC; we will implement more in the
       next sprint*/
    //npc_t npc_info;
    
    /* Pointer to the first (default) action*/
    npc_action_t* head_action;
    
    /* Pointer to the first (default) line*/
    npc_line_t* head_line;
    npc_graphics_t* next;
};

/* */


npc_action_t* ActionNew(char* action_name, char* action_image_path, unsigned frame_number,
                       double switch_frequency);

int ActionInit(npc_action_t* pointer, char* action_name, char* action_image_path, unsigned frame_number,
                       double switch_frequency);

int ActionFree(npc_action_t* pointer);

npc_line_t* LineNew(char* line_name, const char* line);

int LineInit(npc_line_t* pointer, char* line_name, const char* line);

int LineFree(npc_line_t* pointer);
/*
 * A function that gets the action struct specified by the name of
 * that action
 *
 * Parameters:
 *      action_name: the name of that action, needs to be exact;
 *      npc_graphics: the whole npc_grpahics information struct;
 *
 * Return:
 *      The npc_action_t struct that represents the wanted action.
 */
npc_action_t* GetAction(char* action_name, npc_graphics_t* npc_graphics);

/*
 * A function that gets the line struct specified by the name of
 * that line
 *
 * Parameters:
 *      line_name: the name of that line, needs to be exact;
 *      npc_graphics: the whole npc_grpahics information struct;
 *
 * Return:
 *      The npc_line_t struct that represents the wanted line struct.
 */
npc_line_t* GetLine(char* line_name, npc_graphics_t* npc_graphics);

/*
 * A function that gets the graphics information of a specified 
 * NPC from all NPCs
 *
 * Parameters:
 *      NPC_name: the name of the NPC, needs to be exact;
 *      npcs: the linked list of all npcs
 * 
 * Return:
 *      The graphcis information, in npc_graphics_t, for
 *      the specified NPC. */
npc_graphics_t* GetNPC(char* NPC_name, npc_graphics_t** npcs);


/*
 * The main runing function for NPC Graphics
 *
 * Parameters:
 *      npcs: the linked list for all NPCs
 *      NPCname: the name of the NPC, needs to be exact
 *      action: the action that needs to be printed out
 *      line_name: the name of the line that needs to be printed out
 *      windloc: the location of the upper-left corner of the window
 *      windowsize: the size of the window (width, height)
 * 
 * Return:
 *      Nothing.
 */
void runNPCGraphics(npc_graphics_t** npcs, char* NPCname, char* action, char* line_name,
                    Vector2 windowloc, Vector2 windowsize, Color textcolor);

#endif
