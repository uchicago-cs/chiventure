#include "scene_graphics.h"




void runSceneGraphics(scene_graphics_t* scene_graphics)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = scene_graphics->WindowSize.x;
    const int screenHeight = scene_graphics->WindowSize.y;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - scene scrolling");


    Texture2D scene = LoadTexture(scene_graphics->ImagePath);

    float ulxcoord = scene_graphics->PlayerPosition.x - (scene_graphics->SceneSize.x/2);
    float ulycoord = scene_graphics->PlayerPosition.y - (scene_graphics->SceneSize.y/2);
    Rectangle showScene = {ulxcoord, ulycoord, scene_graphics->SceneSize.x,scene_graphics->SceneSize.y};
    Vector2 drawPosition = {(screenWidth - scene_graphics->SceneSize.x)/2, (screenHeight - scene_graphics->SceneSize.y)};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        ulxcoord = scene_graphics->PlayerPosition.x - (scene_graphics->SceneSize.x/2);
        ulycoord = scene_graphics->PlayerPosition.y - (scene_graphics->SceneSize.y/2);
        Rectangle showScene = {ulxcoord, ulycoord, scene_graphics->SceneSize.x,scene_graphics->SceneSize.y};

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            Clearscene(RAYWHITE);

            // Draw scene image twice
            // NOTE: Texture is scaled twice its size
            DrawTextureRec(scene, showScene, drawPosition, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(scene);  // Unload scene texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

int main(void) {

    return 0;
}