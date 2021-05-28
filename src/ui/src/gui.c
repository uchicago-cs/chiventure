#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "action_management/actionmanagement.h"
#include "ui/gui.h"
#include "raylib.h"


void run_gui(chiventure_ctx_t *ctx)
{
    /* initialize the window height and width */
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chiventure");

    /* creating a rectangle the size of the window */
    Rectangle window = { POS_ZERO, POS_ZERO, WINDOW_WIDTH, WINDOW_HEIGHT };

    /* initializing input text box */
    char name[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    int textBoxY = SCREEN_HEIGHT - 30;
    int textBoxWidth = 225;
    int textBoxHeight = 30;

    Rectangle textBox = { POS_ZERO, textBoxY, textBoxWidth, textBoxHeight };
    bool mouseOnText = false;

    /* initializing output text box */
    int outputX = 10;
    int outputHeight = 120;
    int heightbuf = 140;
    Rectangle output = { outputX, SCREEN_HEIGHT - heightbuf, SCREEN_WIDTH, outputHeight };
    char *output_text = ctx->game->start_desc;

    int framesCounter = 0;
    SetTargetFPS(10);

    /* loop to produce window of image and text box */
    while (!WindowShouldClose()) {
        if (CheckCollisionPointRec(GetMousePosition(), window))
            mouseOnText = true;
        else
            mouseOnText = false;

        if (mouseOnText) {
            /* Get pressed key (character) on the queue */
            int key = GetKeyPressed();

            /* Check if more characters have been pressed on the same frame */
            while (key > 0) {
                /* NOTE: Only allow keys in range [32..125}
                as these are the printable characters */
                if ((key >= 0) && (key <= 127) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    letterCount++;
                }

                key = GetKeyPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                letterCount--;
                name[letterCount] = '\0';

                if (letterCount < 0) 
                    letterCount = 0;
            }
            /* Close the window if ctrl+d keys are pressed */
            if ((IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) && IsKeyDown(KEY_D)){
                CloseWindow();
                exit(1);
            }
        }

        if (mouseOnText)
            framesCounter++;
        else framesCounter = 0;
        
        if (IsKeyPressed(KEY_ENTER)) {
            /* use the command to string function to turn name into a command */
            cmd *c = cmd_from_string(name, ctx);
            /* the output text is taken from the command structs and game context */
            output_text = (*(c->func_of_cmd))(c->tokens, ctx);

            /* erases text in the text input, clearing the screen */
            int length = letterCount;
            for(int i = 0; i < length; i++) {
                letterCount--;
                name[letterCount] = '\0';
            }
	        name[letterCount] = (char) 32;
	        letterCount++;

            if (letterCount < 0)
                letterCount = 0;
      	}

        int heightbuf2 = 150;
        int rectHeight = 120;

	    BeginDrawing();

        ClearBackground(RAYWHITE);

        /* Drawing the Image for the upper half of the split screen */

        int width = SCREEN_WIDTH/2;
        int height = SCREEN_HEIGHT/2;
        int pos_x = SCREEN_WIDTH/4;
        int pos_y = SCREEN_HEIGHT/10;
        
        /* Loading just one image is a temporary solution
         In the future, we will use a more generic path so that we can load
         game-specific images */
        Image room = LoadImage("../src/ui/src/chiventure.png");   
            
        ImageResize(&room, width, height);
            
        /* Image converted to texture, uploaded to GPU memory (VRAM) */    
        Texture2D texture = LoadTextureFromImage(room);
        
        /* Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM */
        UnloadImage(room);   
        
        DrawTexture(texture, pos_x, pos_y, WHITE);

        DrawRectangleRec(textBox, WHITE);
        DrawRectangle(POS_ZERO, SCREEN_HEIGHT - heightbuf2, SCREEN_WIDTH, rectHeight, WHITE);
        DrawRectangleLines(POS_ZERO, SCREEN_HEIGHT - heightbuf2, SCREEN_WIDTH, heightbuf2, BLACK);

        /* Values related to text and text-box initialized */
        int xbuf = 5;
        int ybuf = 8;
        int lineIndictorY = textBox.y + 10;
        int lineIndictorX = textBox.x + xbuf + MeasureText(name, 21);
        int fontSize = 20;
        int fontSpacing = 5;

        /* Input text and text-box displayed on lower half of split-screen */
        if (mouseOnText) {
            DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, DARKGRAY);

            if (((framesCounter / 5)%2) == 0)
                DrawText("_", lineIndictorX, lineIndictorY, fontSize, DARKGRAY);
        }
            
        DrawText(name, textBox.x + xbuf, textBox.y + ybuf, fontSize, BLACK);
        Font test = GetFontDefault();
        DrawTextRec(test, output_text, output, fontSize, fontSpacing, true, BLACK);

        EndDrawing();
    }
    
    CloseWindow();

}