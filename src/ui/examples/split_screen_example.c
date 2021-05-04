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
    room_t *room3 = room_new("room3", "This is room 3", "Wow, this is the final room.");

    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);

    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");
    create_connection(game, "room2", "room3", "EAST");

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

        //Images can be at the most 500 x 500 pixels and they have to have
        //the png Image format

        Image room1 = LoadImage("../../../../src/ui/sandbox/images/room1.png");  
        Image room2 = LoadImage("../../../../src/ui/sandbox/images/room2.png");
        Image room3 = LoadImage("../../../../src/ui/sandbox/images/room3.png");  
        ImageResize(&room3, ScreenWidth/2, ScreenHeight/2);
        ImageResize(&room2, ScreenWidth/2, ScreenHeight/2);     
        ImageResize(&room1, ScreenWidth/2, ScreenHeight/2);           
        Texture2D texture1 = LoadTextureFromImage(room1);
        Texture2D texture2 = LoadTextureFromImage(room2);
        Texture2D texture3 = LoadTextureFromImage(room3);
        // Image converted to texture, uploaded to GPU memory (VRAM)
        UnloadImage(room1);   
        UnloadImage(room2);
        UnloadImage(room3);
        // Once image has been converted to texture and uploaded to VRAM, it 
        // can be unloaded from RAM

        int heightbuf2 = 150;
        int rectHeight = 120;

        ClearBackground(RAYWHITE);

        // Drawing the Color Rectangles for each room
        if (!(strcmp(ctx->game->curr_room->room_id, "room1"))){
            DrawTexture(texture1, ScreenWidth/4, ScreenHeight/10, WHITE);
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
