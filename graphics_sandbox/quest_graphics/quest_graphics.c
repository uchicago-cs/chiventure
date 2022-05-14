#include "quest_graphics.h"
#include "stdio.h"
#include "stdlib.h"

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
    res->movement_tracker = 5;
    res->totalsteps = 4;

    return res;
}


void drawTaskTree(task_tree_mockup_t* taskTree, char* current_task_name, float widthSegment, 
                  float heightSegment,Vector2 startPos, float squareside) 
{
    pos_in_tree_t* pos_data = getTaskPos(taskTree, current_task_name);
    task_tree_mockup_t* current_taskTree = taskTree;
    char stepsremaining = pos_data->totalsteps;
    int tracker = pos_data->movement_tracker;
    float x = startPos.x;
    float y = startPos.y;
    float xtmp, ytmp;

    DrawRectangleLines(x,y,squareside,squareside,BLACK);
    DrawText(current_taskTree->task_name,xtmp+(squareside*0.1),y+(squareside*0.5),20,BLACK);

    while(stepsremaining > 0) {
        int thismove = tracker & 1;
        if (thismove == 0) {
            float xloop = x;
            float yloop = y;

            //Draw the whole horizontal line
            //Draw the task names
            current_taskTree = current_taskTree->lmostchild;
            ytmp = y;
            y += heightSegment;
            DrawLine(x, ytmp, x, y, BLACK);
            DrawRectangleLines(xtmp-(squareside/2),y,squareside,squareside,BLACK);
            DrawText(current_taskTree->task_name,xtmp-(squareside*0.4),y+(squareside*0.5),20,BLACK);
            y += squareside;

        }

        if (thismove == 1) {
            current_taskTree = current_taskTree->rsibling;
            xtmp = x;
            x += widthSegment;
            DrawLine(xtmp, y, x, y, BLACK);
            DrawRectangleLines(xtmp,y+(squareside/2),squareside,squareside,BLACK);
            DrawText(current_taskTree->task_name,xtmp+(squareside*0.1),y,20,BLACK);
            x += squareside;
        }  
        stepsremaining --;
        tracker = tracker>>1;
    }

}


void runTaskTreeGraphics(task_tree_mockup_t* taskTree, Vector2 windowpos, Vector2 windowsize,          
                        char*current_taskname)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = windowsize.x;
    const int screenHeight = windowsize.y;

    InitWindow(screenWidth, screenHeight, "Quest");
    SetWindowPosition(windowpos.x, windowpos.y);

    double widthSegment = (screenWidth - 100)/getTreeMaxWidth(taskTree) - 30;
    double heightSegment = (screenWidth - 100)/getTreeMaxHeight(taskTree) - 20;

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

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(TextFormat("hp: %03i/%03i", hp, hp_requirement), 20, 20, 20, RED);

            DrawText(TextFormat("level: %02i/%02i", level, level_requirement), 20, 50, 20, GREEN);

            DrawText(TextFormat("xp: %02i", xp), 20, 80, 20, BLUE);

            drawTaskTree(taskTree,"F",20,20,(Vector2){50,50},10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}



int main() {
    task_tree_mockup_t* taskTree = synthesizeTest1();
    runTaskTreeGraphics(taskTree, (Vector2){50,80},(Vector2){600,400},"F");
    task_tree_mockup_t* next;
    //Free
    return 0;
}