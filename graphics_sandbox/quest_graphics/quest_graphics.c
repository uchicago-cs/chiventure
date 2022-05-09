#include "quest_graphics.h"


int getQuestWidth() {
    //To be implemented by the quests team
    return 5;
}

int getQuestHeight() {
    //To be implemented by the quests team
    return 3;
}




void runQuestGraphics(quest_mockup_t* quest, Vector2 windowpos, Vector2 windowsize)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = windowsize.x;
    const int screenHeight = windowsize.y;

    InitWindow(screenWidth, screenHeight, "Quest");
    SetWindowPosition(windowpos.x, windowpos.y);

    int hp, level, xp;
    int hp_requirement, level_requirement;

    hp_requirement = quest->stat_req->hp;
    level_requirement = quest->stat_req->level;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        hp = getHealth();
        level = getLevel();
        xp = getExperience();

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

    return 0;
}



int main() {
    return 0;
}