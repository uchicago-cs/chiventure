#include "scene_graphics.h"

/* See scene_graphics.h */
int draw_scene_graphics(scene_graphics_t* scene_graphics)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = scene_graphics->WindowSize.x;
    const int screenHeight = scene_graphics->WindowSize.y;

    InitWindow(screenWidth, screenHeight, "NSFW SCENE!!!");


    Texture2D scene = LoadTexture(scene_graphics->ImagePath);

    float ulxcoord = scene_graphics->PlayerPosition.x - (scene_graphics->SceneSize.x/2);
    float ulycoord = scene_graphics->PlayerPosition.y - (scene_graphics->SceneSize.y/2);
    Rectangle showScene = {ulxcoord, ulycoord, scene_graphics->SceneSize.x,scene_graphics->SceneSize.y};
    Vector2 drawPosition = {(screenWidth - scene_graphics->SceneSize.x)/2, (screenHeight - scene_graphics->SceneSize.y)/2};

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

            ClearBackground(RAYWHITE);

            DrawTextureRec(scene, showScene, drawPosition, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(scene);  // Unload scene texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return SUCCESS;
}


int main(void) {

    scene_graphics_t scene_graphics; // replace: = new_scene_graphics();

    scene_graphics.SceneName="NSWF";
    scene_graphics.SceneSize=(Vector2) {400,400};
    scene_graphics.PlayerPosition=(Vector2) {400,400};
    scene_graphics.WindowSize=(Vector2) {440,440};
    scene_graphics.WindowPos=(Vector2) {100,100};
    scene_graphics.ImagePath="nsfw.png";


    runSceneGraphics(&scene_graphics);

    return 0;
}

