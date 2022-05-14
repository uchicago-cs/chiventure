#include "map_graphics.h"

#include "raylib.h"

void runMapGraphics(map_graphics_t* info)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = (int)info->WindowSize.x;
    const int screenHeight = (int)info->WindowSize.y;
    int windowposx = (int)info->WindowPos.x;
    int windowposy = (int)info->WindowPos.y;

    InitWindow(screenWidth, screenHeight, info->MapTitle);
    SetWindowPosition(windowposx,windowposy);

    Texture2D MapTexture = LoadTexture(info->MapImagePath);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(MapTexture,(screenWidth-MapTexture.width)/2,(screenHeight-MapTexture.height)/2,RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}

int main(void) {
    //runMapGraphics();
    return 0;
}