#include <raylib.h>
#include <ctype.h>
#include <signal.h>
#include <string.h>
#include <locale.h>

#include "common/ctx.h"
#include "ui/window.h"
#include "ui/print_functions.h"
#include "ui/ui_ctx.h"
#include "ui/draw_images.h"


void start_gui(chiventure_ctx_t *ctx)
{
    //initialize the window height and width
    int ScreenWidth = 800;
    int ScreenHeight = 500;

    /*The string parameter here should probably be the title of the game*/
    InitWindow(ScreenWidth, ScreenHeight, "load image sandbox program");

    //creating a rectangle the size of the window
    int WindowWidth = 1200;
    int WindowHeight = 700;
    Rectangle window = { POS_ZERO, POS_ZERO, WindowWidth, WindowHeight };

    //initializing input text box
    char name[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    int textBoxY = ScreenHeight - 30;
    int textBoxWidth = 225;
    int textBoxHeight = 30;

    Rectangle textBox = { POS_ZERO, textBoxY, textBoxWidth, textBoxHeight };
    bool mouseOnText = false;

    //initializing output text box
    int outputX = 10;
    int outputHeight = 120;
    int heightbuf = 140;
    Rectangle output = { outputX, ScreenHeight - heightbuf, ScreenWidth, outputHeight };
    /*Is there a starting text thing that could go here?*/
    char *output_text = "You see a path. There is a hollow log on the ground.";

    int framesCounter = 0;
    SetTargetFPS(10);

    //loop to produce window of image and text box
    while (!WindowShouldClose()) {
        if (CheckCollisionPointRec(GetMousePosition(), window))
            mouseOnText = true;
        else
            mouseOnText = false;

        if (mouseOnText) {
        // Get pressed key (character) on the queue
            int key = GetKeyPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0) {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    letterCount++;
                }

                key = GetKeyPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                letterCount--;
                name[letterCount] = '\0';

                if (letterCount < 0) letterCount = 0;
            }
        }

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
        
        if (IsKeyPressed(KEY_ENTER)) {
            // use the command to string function to turn name into a command
            cmd *c = cmd_from_string(name, ctx);
            // the output text is taken from the command structs and game context
            output_text = (*(c->func_of_cmd))(c->tokens, ctx);

            // erases text in the text input, clearing the screen
            int length = letterCount;
            for(int i = 0; i < length; i++) {
                letterCount--;
                name[letterCount] = '\0';
            }

            if (letterCount < 0)
                letterCount = 0;
        }

        int heightbuf2 = 150;
        int rectHeight = 120;

        ClearBackground(RAYWHITE);

        // Drawing the Color Rectangles for each room
        if (!(strcmp(ctx->game->curr_room->room_id, "room1"))){
            DrawTexture(texture1, ScreenWidth/4, ScreenHeight/10, WHITE);
            // draw_room(ctx->game->curr_room->room_id);
	    /*I think to use the above function, you'd need some kind of loop
	     * so that you're drawing all of the rooms rather than just
	     * the current one? Unless I'm misunderstanding what this
	     * code here does*/
        }                                           
        else if (!(strcmp(ctx->game->curr_room->room_id, "room2"))) 
            DrawTexture(texture2, ScreenWidth/4, ScreenHeight/10, WHITE);

        else if (!(strcmp(ctx->game->curr_room->room_id, "room3"))) 
            DrawTexture(texture3, ScreenWidth/4, ScreenHeight/10, WHITE);

        else 
            DrawTexture(texture1, ScreenWidth/4, ScreenHeight/10, WHITE);

        DrawRectangleRec(textBox, WHITE);
        DrawRectangle(POS_ZERO, ScreenHeight - heightbuf2, ScreenWidth, rectHeight, WHITE);
        DrawRectangleLines(POS_ZERO, ScreenHeight - heightbuf2, ScreenWidth, heightbuf2, BLACK);

        int xbuf = 5;
        int ybuf = 8;
        int lineIndictorY = textBox.y + 10;
        int lineIndictorX = textBox.x + xbuf + MeasureText(name, 21);
        int fontSize = 20;
        int fontSpacing = 5;

	/*I couldn't figure out what this if does but I don't think we 
	 * need to change anything?*/
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

    return 0;
}

}
