#ifndef QUEST_GRAPHICS_H
#define QUEST_GRAPHICS_H

#include "raylib.h"

typedef struct task_tree_mockup task_tree_mockup_t;

struct task_tree_mockup {
    char* task_name;
    task_tree_mockup_t *parent;
    task_tree_mockup_t *rsibling;
    task_tree_mockup_t *lmostchild;
    int visited;
};


typedef struct pos_in_tree {
    /*
     * Every bit denotes a movement,
     * 1 means going to the right;
     * 0 means going down
     * Start from the first bit
     */
    int movement_tracker;
    // Tallying the total number of steps
    char totalsteps;
} pos_int_tree_t;


int getTreeMaxWidth(task_tree_mockup_t* taskTree);

int getTreeMaxHeight(task_tree_mockup_t* taskTree);



#endif