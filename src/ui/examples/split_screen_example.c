#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "action_management/actionmanagement.h"
#define MAX_INPUT_CHARS 20
#define POS_ZERO 0

chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
} 

int main() {

    chiventure_ctx_t *ctx = create_sample_ctx();

    //initialize the window height and width
    int ScreenWidth = 800;
    int ScreenHeight = 500;

    InitWindow(ScreenWidth, ScreenHeight, "load image sandbox program");

    /*//loading the texture into memory
    Image room = LoadImage("image.png");

    //converting the image to a texture for raylib in VRAM
    Texture2D texture = LoadTextureFromImage(room); */

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

        //Draw Image
        BeginDrawing();
        int heightbuf2 = 150;
        int rectHeight = 120;

        ClearBackground(RAYWHITE);
        DrawRectangle (ScreenWidth/4, ScreenHeight/10, ScreenWidth/2, ScreenHeight/2, DARKBLUE);
        DrawRectangleRec(textBox, WHITE);
        DrawRectangle(POS_ZERO, ScreenHeight - heightbuf2, ScreenWidth, rectHeight, WHITE);
        DrawRectangleLines(POS_ZERO, ScreenHeight - heightbuf2, ScreenWidth, heightbuf2, BLACK);

        int xbuf = 5;
        int ybuf = 8;
        int lineIndictorY = textBox.y + 10;
        int lineIndictorX = textBox.x + xbuf + MeasureText(name, 21);
        int fontSize = 20;
        int fontSpacing = 5;

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

    //UnloadTexture(texture);
    CloseWindow();

    return 0;
}
