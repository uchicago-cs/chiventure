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


/* Parameters:
 *      taskTree:
 *          a (currently mockup) task tree structure
 *      wanted_task_name:
 *          the name of the wanted task for search
 * Function:
 *      get the position of a wanted task in the taskTree
 *      to endow a priori knowledge when drawing
 * 
 * Return:
 *      a pointer to pos_in_tree_t struct that represents
 *      the way that the task can be searched in the task tree
 * 
 * Note: currently hardcoded, future version should enable dynamic
 */
pos_in_tree_t* getTaskPos(task_tree_mockup_t* taskTree, char* wanted_task_name) {
    //Todo
    pos_in_tree_t *res = (pos_in_tree_t *)malloc(sizeof(pos_in_tree_t));
    res->movement_tracker = 1;
    res->totalsteps = 3;

    return res;
}

/* See quest_graphics.h*/
void runTaskTreeGraphics(quest_graphics_t* quest_graphics)
{
    //--------------------------------------------------------------------------------------
    const int screenWidth = quest_graphics->WindowSize.x;
    const int screenHeight = quest_graphics->WindowSize.y;
    InitWindow(screenWidth, screenHeight, "Quest");
    SetWindowPosition(quest_graphics->WindowPos.x, quest_graphics->WindowPos.y);

    double widthSegment = quest_graphics->SegmentDimension.x;
    double heightSegment = quest_graphics->SegmentDimension.y;

    //Currently Hardcoded, need to be flexible in the future as
    // as we read in from the real quest struct;
    int hp, level, xp;
    int hp_requirement = 500;
    int level_requirement = 7;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        //hp = getHealth();
        hp = 300;
        //level = getLevel();
        level = 4;
        //xp = getExperience();
        xp = 400;

        pos_in_tree_t* pos_data = getTaskPos(quest_graphics->TaskTree, quest_graphics->CurrentTaskName);
        task_tree_mockup_t* current_taskTree = quest_graphics->TaskTree;
        char stepstotal = pos_data->totalsteps;
        int tracker = pos_data->movement_tracker;
        float x = quest_graphics->DrawStartPosition.x;
        float y = quest_graphics->DrawStartPosition.y;
        float xtmp, ytmp, xcopy, ycopy;
        int thismove;
        int lastmove = tracker >> (stepstotal-1);
        float squareside = quest_graphics->SquareSide;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(TextFormat("hp: %03i/%03i", hp, hp_requirement), 20, 20, 20, RED);

            DrawText(TextFormat("level: %02i/%02i", level, level_requirement), 20, 50, 20, GREEN);

            DrawText(TextFormat("xp: %02i", xp), 20, 80, 20, BLUE);

            DrawRectangleLines(x,(y-squareside/2),squareside,squareside,BLACK);
            DrawText(current_taskTree->task_name,x+(squareside*0.3),y-squareside*0.3,20,BLACK);

            if ((tracker&1)==0) {
                y += squareside/2;
            } else {
                x += squareside/2;
            }

        for(int i = 0; i < stepstotal; i++) {
            thismove = tracker & 1;
            if (thismove == 0) {
                if (quest_graphics->ShowRemainingHorizontal) {
                    task_tree_mockup_t* copy = current_taskTree;
                    xcopy = x;
                    ycopy = y;
                    while ((copy = copy->rsibling)) {
                        xcopy += squareside/2;
                        xtmp = xcopy;
                        xcopy += widthSegment;
                        DrawLine(xtmp, ycopy, xcopy, ycopy, BLACK);
                        DrawRectangleLines(xcopy,ycopy-(squareside/2),squareside,squareside,BLACK);
                        DrawText(copy->task_name,xcopy+(squareside*0.3),(ycopy-squareside*0.2),20,BLACK);
                        xcopy += squareside/2;
                    }
                }
                if((current_taskTree = current_taskTree->lmostchild)) {
                    y += squareside/2;
                    ytmp = y;
                    y += heightSegment;
                    DrawLine(x, ytmp, x, y, BLACK);
                    DrawRectangleLines(x-(squareside/2),y,squareside,squareside,BLACK);
                    DrawText(current_taskTree->task_name,(x-0.2*squareside),(y+0.2*squareside),20,BLACK);
                    y += squareside/2;
                } else {
                    break;
                }
            } else {
                if((current_taskTree = current_taskTree->rsibling)) {
                    x += squareside/2;
                    xtmp = x;
                    x += widthSegment;
                    DrawLine(xtmp, y, x, y, BLACK);
                    DrawRectangleLines(x,y-(squareside/2),squareside,squareside,BLACK);
                    DrawText(current_taskTree->task_name,x+(squareside*0.3),(y-squareside*0.2),20,BLACK);
                    x += squareside/2;
                } else {
                    break;
                }
            }
            tracker >>= 1;
        }

        DrawCircleLines(x,y,squareside,RED);
        
        EndDrawing();
        
    }
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}



