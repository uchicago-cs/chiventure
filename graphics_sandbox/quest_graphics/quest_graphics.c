#include "quest_graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int getTreeMaxWidth(task_tree_mockup_t* taskTree) {
    //To do
    return 4;
}

int getTreeMaxHeight(task_tree_mockup_t* taskTree) {
    //To do
    return 3;
}

task_tree_mockup_t* synthesizeTest1() {
    task_tree_mockup_t *TreeA = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeB = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeC = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeD = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeE = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeF = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeG = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeH = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeI = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));

    TreeA->task_name="A";
    TreeA->rsibling=TreeB;
    TreeA->lmostchild=NULL;
    TreeA->parent=NULL;

    TreeB->task_name="B";
    TreeB->rsibling=TreeC;
    TreeB->lmostchild=TreeE;
    TreeB->parent = NULL;

    TreeC->task_name= "C";
    TreeC->rsibling=TreeD;
    TreeC->lmostchild=TreeG;
    TreeC->parent=NULL;

    TreeD->task_name="D";
    TreeD->rsibling=NULL;
    TreeD->lmostchild=NULL;
    TreeD->parent=NULL;

    TreeE->task_name="E";
    TreeE->rsibling=NULL;
    TreeE->lmostchild=TreeF;
    TreeE->parent=TreeB;

    TreeF->task_name="F";
    TreeF->rsibling=TreeH;
    TreeF->lmostchild=NULL;
    TreeF->parent=TreeE;

    TreeG->task_name="G";
    TreeG->rsibling=NULL;
    TreeG->lmostchild=NULL;
    TreeG->parent=TreeC;

    TreeH->task_name="H";
    TreeH->rsibling=TreeI;
    TreeH->lmostchild=NULL;
    TreeH->parent=TreeE;

    TreeI->task_name="I";
    TreeI->rsibling=NULL;
    TreeI->lmostchild=NULL;
    TreeI->parent=TreeE;

    return TreeA;

}

pos_in_tree_t* getTaskPos(task_tree_mockup_t* taskTree, char* wanted_task_name) {

    pos_in_tree_t *res = (pos_in_tree_t *)malloc(sizeof(pos_in_tree_t));
    res->movement_tracker = 1;
    res->totalsteps = 3;

    return res;
}



void runTaskTreeGraphics(quest_graphics_t* quest_graphics)
{


    // Initialization
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
        float squareside = quest_graphics->SquareeSide;

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
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}



int main() {
    task_tree_mockup_t *TreeA = synthesizeTest1();

    quest_graphics_t quest_graphics;

    quest_graphics.TaskTree=TreeA;
    quest_graphics.WindowPos=(Vector2){80,80};
    quest_graphics.WindowSize=(Vector2){600,400};
    quest_graphics.DrawStartPosition=(Vector2){150,150};
    quest_graphics.SegmentDimension=(Vector2){50,50};
    quest_graphics.SquareeSide=30;
    quest_graphics.CurrentTaskName="F";
    quest_graphics.ShowRemainingHorizontal=true;


    runTaskTreeGraphics(&quest_graphics);
    //Free
    return 0;
}