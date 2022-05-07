
#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_INPUT_CHARS     14

/* See input_box.h*/
void run_input_box(Vector2 windowDimension, Vector2 windowPosition, char* input_buffer) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = (const int) windowDimension.x;
    const int screenHeight = (const int) windowDimension.y;

    InitWindow(screenWidth, screenHeight, "Game Input Box");
    SetWindowPosition(windowPosition.x, windowPosition.y);
    

    char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    Rectangle textBox = { screenWidth/2.0f - 240, 70, 480, 50 };
    bool mouseOnText = false;

    int framesCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 10 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }
            
            if(IsKeyPressed(KEY_ENTER))
            {
                input_buffer = strdup(name);
                letterCount = 0;
                name[letterCount] = '\0';
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("PLACE MOUSE OVER INPUT BOX TO INPUT COMMAND", screenWidth/2.0f - 240, 140, 18, GRAY);

            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGREEN);
            else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, DARKGREEN);

            DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, DARKGREEN);
                }
                else DrawText("Press BACKSPACE to delete chars...", screenWidth/2.0f - 240, 40, 18, GRAY);
            }

        EndDrawing();
        //Just for testing purpose//
        printf("%s",input_buffer);
        fflush(stdout);
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


}

int main(void)
{
    char buffer[100];
    run_input_box((Vector2){500,200},(Vector2){800,600},buffer);
    printf("%s",buffer);
    return 0;
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();
    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}
