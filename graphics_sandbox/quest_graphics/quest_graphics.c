#include "quest_graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


/* See quest_graphics.h */
quest_graphics_t* new_quest_graphics(Vector2 WindowPos, Vector2 WindowSize,
    Vector2 SegmentDimension, Vector2 DrawStartPosition, 
    task_tree_mockup_t *TaskTree, char* CurrentTaskName, 
    bool ShowRemainingHorizontal, float SquareSide)
{
    quest_graphics_t *questGraphics;
    int rc;

    questGraphics = malloc(sizeof(quest_graphics_t));

    if (questGraphics == NULL)
    {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    rc = init_quest_graphics(questGraphics, WindowPos, WindowSize,
        SegmentDimension, DrawStartPosition, TaskTree, CurrentTaskName, 
        ShowRemainingHorizontal, SquareSide);

    if(rc == FAILURE)
    {
        fprintf(stderr,"Could not initialize quest_graphics");
        return NULL;
    }

    return questGraphics;
}

/* See quest_graphics.h*/
int init_quest_graphics(quest_graphics_t *questGraphics, Vector2 WindowPos,
    Vector2 WindowSize, Vector2 SegmentDimension, Vector2 DrawStartPosition, 
    task_tree_mockup_t *TaskTree, char* CurrentTaskName, 
    bool ShowRemainingHorizontal, float SquareSide)
{
    assert(questGraphics != NULL);
    //assert(TaskTree != NULL);
    assert(CurrentTaskName != NULL);

    questGraphics->WindowPos = WindowPos;
    questGraphics->WindowSize = WindowSize;
    questGraphics->SegmentDimension = SegmentDimension;
    questGraphics->DrawStartPosition = DrawStartPosition;
    questGraphics->TaskTree = TaskTree;
    questGraphics->CurrentTaskName = CurrentTaskName;
    questGraphics->ShowRemainingHorizontal = ShowRemainingHorizontal;
    questGraphics->SquareSide = SquareSide;

    return SUCCESS;
}

/* See quest_graphics.c*/
int free_quest_graphics(quest_graphics_t *questGraphics)
{
    assert(questGraphics != NULL);

    free(questGraphics);

    return SUCCESS;
}






