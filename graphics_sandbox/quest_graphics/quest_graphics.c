#include "quest_graphics.h"

task_tree_t* getTreeMaxWidth(task_tree_mockup_t* taskTree) {
    //To do
    return 6;
}

task_tree_t* getTreeMaxHeight(task_tree_mockup_t* taskTree) {
    //To do
    return 4;
}




void runTaskTree(task_tree_mockup_t* taskTree, Vector2 windowpos, Vector2 windowsize)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = windowsize.x;
    const int screenHeight = windowsize.y;

    InitWindow(screenWidth, screenHeight, "Quest");
    SetWindowPosition(windowpos.x, windowpos.y);

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

            DrawText(TextFormat("hp: %08i/%08i", hp, hp_requirement), 200, 80, 20, RED);

            DrawText(TextFormat("level: %08i/%08i", level, level_requirement), 200, 120, 20, GREEN);

            DrawText(TextFormat("xp: %02i", xp), 200, 160, 40, BLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}



int main() {


    return 0;
}