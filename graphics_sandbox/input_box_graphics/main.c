#include "raylib.h"
#include "input_box_graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed()
{

    bool keyPressed = false;
    int key = GetKeyPressed();
    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}

/* See input_box.h*/
void run_input_box(input_box_graphics_t *input_box_graphics, char* input_buffer) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = input_box_graphics->WindowSize.x;
    const int screenHeight = input_box_graphics->WindowSize.y;

    InitWindow(screenWidth, screenHeight, "Game Input Box");
    SetWindowPosition(input_box_graphics->WindowPos.x, input_box_graphics->WindowPos.y);
    

    char name[MAX_INPUT_CHAR + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
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
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHAR))
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

            DrawRectangleRec(textBox, input_box_graphics->BoxColor);
            DrawText(input_box_graphics->Annotation, screenWidth/2.0f - 240, 140, 18, input_box_graphics->AnnotationColor);
            if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, input_box_graphics->TextColor);
            else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, input_box_graphics->OutlineColor);

            DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, input_box_graphics->TextColor);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHAR)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, input_box_graphics->TextColor);
                }
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
    input_box_graphics_t input_box_graphics;
    input_box_graphics.BoxColor = LIGHTGRAY;
    input_box_graphics.TextColor = DARKGREEN;
    input_box_graphics.WindowPos = (Vector2){800,600};
    input_box_graphics.WindowSize = (Vector2){500,200};
    input_box_graphics.AnnotationColor =  GRAY;
    input_box_graphics.OutlineColor = DARKGRAY;
    input_box_graphics.Annotation = "PLACE MOUSE OVER INPUT BOX TO INPUT COMMAND";
    run_input_box(&input_box_graphics,buffer);
    printf("%s",buffer);
    return 0;
}