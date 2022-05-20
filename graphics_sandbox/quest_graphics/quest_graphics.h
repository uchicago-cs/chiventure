#ifndef QUEST_GRAPHICS_H
#define QUEST_GRAPHICS_H

#define QUEST_CONTEXT_ID 3

#include "raylib.h"
#include <stdbool.h>

typedef struct task_tree_mockup task_tree_mockup_t;

struct task_tree_mockup {
    const char* task_name;
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
     * Start from the last bit
     * goes from right to left
     */
    int movement_tracker;
    // Tallying the total number of steps
    char totalsteps;
} pos_in_tree_t;

typedef struct quest_graphics{
    Vector2 WindowPos;
    Vector2 WindowSize;
    Vector2 SegmentDimension;
    Vector2 DrawStartPosition;
    task_tree_mockup_t *TaskTree;
    char* CurrentTaskName;
    bool ShowRemainingHorizontal;
    float SquareSide;
} quest_graphics_t;

/*
 * Creates a new quest graphics struct
 *
 * Parameters:
 * - the quest graphics struct
 * - the window position
 * - the window size
 * - the segment dimension
 * - the draw start position
 * - the task tree
 * - the current task name
 * - boolean for whether the remaining tasks should be shown
 * - the square side
 *
 * Returns:
 * - the quest graphics struct
 */
quest_graphics_t* quest_graphics_new(Vector2 WindowPos, Vector2 WindowSize,
    Vector2 SegmentDimension, Vector2 DrawStartPosition, 
    task_tree_mockup_t *TaskTree, char* CurrentTaskName, 
    bool ShowRemainingHorizontal, float SquareSide);


/*
 * Initializes a quest graphics struct
 *
 * Parameters:
 * - the quest graphics struct
 * - the window position
 * - the window size
 * - the segment dimension
 * - the draw start position
 * - the task tree
 * - the current task name
 * - boolean for whether the remaining tasks should be shown
 * - the square side
 *
 * Returns:
 * - 1 on success
 */
int quest_graphics_init(quest_graphics_t *questGraphics, Vector2 WindowPos,
    Vector2 WindowSize, Vector2 SegmentDimension, Vector2 DrawStartPosition, 
    task_tree_mockup_t *TaskTree, char* CurrentTaskName, 
    bool ShowRemainingHorizontal, float SquareSide);

/*
 * Frees a quest graphics struct
 *
 * Parameters:
 * - the quest graphics struct
 *
 * Returns:
 * - 1 on success
 */
int quest_graphics_free(quest_graphics_t *questGraphics);

void runTaskTreeGraphics(quest_graphics_t* quest_graphics);

#endif
