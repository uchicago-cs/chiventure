#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_INVENTORY    21          // Maximum Number of Inventory Items


void runInventoryGrahpics(Vector2 screeDimension, Vector2 windowPosition, unsigned max_inventory
                          )
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Player Inventory Screen");


    Image balloonimg = LoadImage("test_images/balloon.png");
    ImageResize(&balloonimg,100,100);
    Texture2D cheems = LoadTextureFromImage(balloonimg);

    Rectangle slots[MAX_INVENTORY] = { 0 };     // Rectangles array
    
    for (int i = 0; i < MAX_INVENTORY; i++)
    {
        slots[i].x = 20.0f + 100.0f *(i%7) + 10.0f *(i%7);
        slots[i].y = 80.0f + 100.0f *(i/7) + 10.0f *(i/7);
        slots[i].width = 100.0f;
        slots[i].height = 100.0f;
    }

    int colorState[MAX_INVENTORY] = { 0 };           // Color state: 0-DEFAULT, 1-MOUSE_HOVER

    Vector2 mousePoint = { 0.0f, 0.0f };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePoint = GetMousePosition();

        for (int i = 0; i < MAX_INVENTORY; i++)
        {
            if (CheckCollisionPointRec(mousePoint, slots[i])) colorState[i] = 1;
            else colorState[i] = 0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Inventory", 350, 42, 20, BLACK);
            DrawText("press SPACE to see all items", GetScreenWidth() - 180, GetScreenHeight() - 40, 10, GRAY);
        


        for (int i = 0; i < MAX_INVENTORY; i++)    // Draw all rectangles
            {
                // draw the rectangles (all just grey for now)
                //DrawRectangleRec(slots[i], Fade(LIGHTGRAY, colorState[i]? 0.6f : 1.0f));
                DrawTextureRec(cheems, (Rectangle){0.0f,0.0f,slots[i].width, slots[i].height}, (Vector2){slots[i].x, slots[i].y}, WHITE);

                if (IsKeyDown(KEY_SPACE) || colorState[i])  // display text if mouse is hovering or SPACE is held
                {   
                    DrawRectangle((int)slots[i].x, (int)(slots[i].y + slots[i].height - 26), (int)slots[i].width, 20, BLACK);
                    DrawRectangleLinesEx(slots[i], 6, Fade(BLACK, 0.3f));
                    /*DrawText(colorNames[i], (int)(slots[i].x + slots[i].width - MeasureText(colorNames[i], 10) - 12),
                        (int)(slots[i].y + slots[i].height - 20), 10, colors[i]);*/

                }
            }


        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    UnloadTexture(cheems);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


}


int main(void)
{
    return 0;
}
