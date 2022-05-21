#ifndef QUEST_GRAPHICS_H
#define QUEST_GRAPHICS_H

#include "raylib.h"
#include <stdbool.h>

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



quest_graphics_t* new_quest_graphics(Vector2 WindowPos, Vector2 WindowSize,
    Vector2 SegmentDimension, Vector2 DrawStartPosition, 
    task_tree_mockup_t *TaskTree, char* CurrentTaskName, 
    bool ShowRemainingHorizontal, float SquareSide);


int init_quest_graphics(quest_graphics_t *questGraphics, Vector2 WindowPos,
    Vector2 WindowSize, Vector2 SegmentDimension, Vector2 DrawStartPosition, 
    task_tree_mockup_t *TaskTree, char* CurrentTaskName, 
    bool ShowRemainingHorizontal, float SquareSide);
    
int free_quest_graphics(quest_graphics_t *questGraphics);

void runTaskTreeGraphics(quest_graphics_t* quest_graphics);

#endif
