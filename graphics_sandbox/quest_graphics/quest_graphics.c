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

task_tree_mockup_t* synthesizeTest() {
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
    TreeD->lmostchild=TreeG;
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



void drawTaskTree(task_tree_mockup_t* taskTree, double widthSegment, 
                  double heightSegment,Vector2 startPos) 
{
    

}


void runTaskTreeGraphics(task_tree_mockup_t* taskTree, Vector2 windowpos, Vector2 windowsize)
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

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}



int main() {
    task_tree_mockup_t* taskTree = synthesizeTest();
    runTaskTreeGraphics(taskTree, (Vector2){50,80},(Vector2){600,400});
    return 0;
}