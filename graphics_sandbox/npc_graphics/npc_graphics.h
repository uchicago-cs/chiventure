#ifndef NPC_GRAPHICS_H
#define NPC_GRAPHICS_H

/* This would be implemented in part2
 *  When we want to integrate this feature
 *  to the game*/
//#include "npc/npc.h"

#define NPC_CONTEXT_ID 2;

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

typedef struct npc_info npc_info_t;

struct npc_info {
    /* The name of the NPC*/
    char* npc_name;
    
    /* We want to show more info about the
       the NPC; we will implement more in the
       next sprint*/
    //npc_t npc_info_t;
    
    /* Pointer to the first (default) action*/
    npc_action_t* head_action;
    
    /* Pointer to the first (default) line*/
    npc_line_t* head_line;
    npc_info_t* next;
};


typedef struct npc_graphics{
    Vector2 WindowPos;
    Vector2 WindowSize;
    Color textcolor;
    char* current_npc;
    char* current_action;
    char* current_line;
    npc_info_t* npc_linkedlist;
} npc_graphics_t;


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
 *      npc_info: the whole npc_grpahics information struct;
 *
 * Return:
 *      The npc_action_t struct that represents the wanted action.
 */
npc_action_t* GetAction(char* action_name, npc_info_t* npc_info);

/*
 * A function that gets the line struct specified by the name of
 * that line
 *
 * Parameters:
 *      line_name: the name of that line, needs to be exact;
 *      npc_info: the whole npc_grpahics information struct;
 *
 * Return:
 *      The npc_line_t struct that represents the wanted line struct.
 */
npc_line_t* GetLine(char* line_name, npc_info_t* npc_info);

/*
 * A function that gets the graphics information of a specified 
 * NPC from all NPCs
 *
 * Parameters:
 *      NPC_name: the name of the NPC, needs to be exact;
 *      npcs: the linked list of all npcs
 * 
 * Return:
 *      The graphcis information, in npc_info_t, for
 *      the specified NPC. */
npc_info_t* GetNPC(char* NPC_name, npc_info_t* npcs);


/*
 * The main runing function for NPC Graphics
 *
 * Parameters:
 *      npc_graphics_t: All information required for the npc window
 * 
 * Return:
 *      Nothing.
 */
void runNPCGraphics(npc_graphics_t* npc_graphics);

#endif
