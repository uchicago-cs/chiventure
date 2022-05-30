#ifndef QUEST_GRAPHICS_H
#define QUEST_GRAPHICS_H

#include "raylib.h"
#include <stdbool.h>
#include "common.h"

typedef struct task_tree_mockup task_tree_mockup_t;


/*
 *  This is a mockup struct that has
 *  identical fields as the real
 *  task_tree struct
 * 
 *  We came up with this mockup struct
 *  to route around complex dependencies
 */
struct task_tree_mockup {
    const char* task_name;
    task_tree_mockup_t *parent;
    task_tree_mockup_t *rsibling;
    task_tree_mockup_t *lmostchild;
    int visited;
};


/*
 * This is a struct used to store
 * a priori knowledge of navigating
 * to a specific struct for drawing
 * branchs of a binar tree
 */
typedef struct pos_in_tree {
    /*
     * Every bit denotes a movement,
     * 1 means going to the right;
     * 0 means going down
     * Start from the last bit
     * goes from right to left
     */
    int movement_tracker;
    // Tallying the total number of steps
    char totalsteps;
} pos_in_tree_t;


/* This is the top-most-level struct
 * that stores everything (for now)
 * needed to dispaly quests*/
typedef struct quest_graphics{
    /* The upperleft corner position of the window*/
    Vector2 WindowPos;
    /* The size of the window, width is x field, height is y field*/
    Vector2 WindowSize;
    /* The length of the segment, horizontal segment is x field, vertical is y*/
    Vector2 SegmentDimension;
    /* The starting position to draw the task tree, relative to the window's upper-left corner*/
    Vector2 DrawStartPosition;
    /* The binary task tree that represents the relationship between tasks*/
    task_tree_mockup_t *TaskTree;
    /* The name/id of the current Task*/
    char* CurrentTaskName;
    /* If true, we will print out every horizontal siblings of the parents of the current task*/
    bool ShowRemainingHorizontal;
    /* The length of the side of the square that represents the task*/
    float SquareSide;
} quest_graphics_t;


/* 
 * Parameters:
 *      Everything in the quest_graphics struct
 * 
 * Returns:
 *      A pointer to the initialized quest_graphics struct that contains
 *      all the information provided through the parameters
 * 
 */
quest_graphics_t* new_quest_graphics(Vector2 WindowPos, Vector2 WindowSize,
    Vector2 SegmentDimension, Vector2 DrawStartPosition, 
    task_tree_mockup_t *TaskTree, char* CurrentTaskName, 
    bool ShowRemainingHorizontal, float SquareSide);


/*
 * Parameters:
 *      A pointer to a quest_graphics struct (allocated memory),
 *      and everythiing in the quest_graphics struct
 * 
 * Function:
 *      Initialize the memory allocated to the quest_graphics struct
 *      with information provided through the parameters
 * 
 * Returns:
 *      SUCCESS on success
 */
int init_quest_graphics(quest_graphics_t *questGraphics, Vector2 WindowPos,
    Vector2 WindowSize, Vector2 SegmentDimension, Vector2 DrawStartPosition, 
    task_tree_mockup_t *TaskTree, char* CurrentTaskName, 
    bool ShowRemainingHorizontal, float SquareSide);
    

/*
 * Parameters:
 *      questGraphics: a pointer to a piece of memory allocated for a quest_graphics struct
 * 
 * Function:
 *      Frees the memory pointed to by the given pointer
 * 
 * Returns:
 *     SUCCESS on success
 *
 */
int free_quest_graphics(quest_graphics_t *questGraphics);


/*
 * Parameters:
 *      quest_graphics:
 *          a pointer to a quest_graphics_t struct, which
 *          contains all information needed for customized quest
 *          graphics dispaly 
 *
 * Returns:
 *      Nothing, and it should not return itself without user command
 * 
 * Function:
 *      Runs the whole questGraphics with given specifications
 */
void runTaskTreeGraphics(quest_graphics_t* quest_graphics);


#endif
