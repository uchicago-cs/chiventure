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

        int map_width, map_height, map_room_width, map_room_height, map_centX, map_centY, ball_rad;
        map_width = width / 10;
        map_height = height / 5;
        map_room_width = map_width / 3;
        map_room_height = map_height / 3;
        map_centX = map_width/2;
        map_centY = -1 * (map_height/2);   
        ball_rad = map_room_width / 5;
        room_t *curr_room = ctx->game->curr_room;
        
        Color colors[8];

        colors[0] = RED;
        colors[1] = PINK;
        colors[2] = PURPLE;
        colors[3] = BLUE;
        colors[4] = YELLOW;
        colors[5] = GREEN;
        colors[6] = ORANGE;
        colors[7] = DARKGREEN;
        
        // map background
        DrawRectangle(map_centX, map_centY, map_width, map_height, BLACK);
        
        int posX = map_centX;
        int posY = map_centY;
        // current room
        DrawRectangle(posX, posY, map_room_width, map_room_height, colors[0]);

        //draw surrounding rooms around current room
        if (find_room_from_dir(curr_room, "EAST") != NULL)
        {   
            posX = map_centX + map_room_width;
            DrawRectangle(posX, posY, map_room_width, map_room_height, colors[1]);

            room_t *east = find_room_from_dir(curr_room, "EAST");
            if (find_room_from_dir(east, "NORTH") != NULL)
            {
                posY = map_centX + map_room_height;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[5]);
            }
            if (find_room_from_dir(east, "SOUTH") != NULL)
            {
                posY = map_centY - map_room_height;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[6]);
            }

        }
        if (find_room_from_dir(curr_room, "WEST") != NULL)
        {
            posX = map_centX - map_room_width;
            DrawRectangle(posX, posY, map_room_width, map_room_height, colors[2]);

            room_t *west = find_room_from_dir(curr_room, "WEST");
            if (find_room_from_dir(west, "NORTH") != NULL)
            {
                posY = map_centX + map_room_height;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[7]);
            }
            if (find_room_from_dir(west, "SOUTH") != NULL)
            {
                posY = map_centX - map_room_height;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[8]);
            }
        }
        if (find_room_from_dir(curr_room, "SOUTH") != NULL)
        {
            posY = map_centX - map_room_height;
            DrawRectangle(posX, posY, map_room_width, map_room_height, colors[3]);

            room_t *south = find_room_from_dir(curr_room, "SOUTH");
            if (find_room_from_dir(south, "EAST") != NULL)
            {
                posX = map_centX + map_room_width;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[6]);
            }
            if (find_room_from_dir(south, "WEST") != NULL)
            {
                posX = map_centX - map_room_width;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[8]);
            }
        }
        if (find_room_from_dir(curr_room, "NORTH") != NULL)
        {
            posY = map_centX + map_room_height;
            DrawRectangle(posX, posY, map_room_width, map_room_height, colors[4]);

            room_t *north = find_room_from_dir(curr_room, "NORTH");
            if (find_room_from_dir(north, "WEST") != NULL)
            {
                posX = map_centX - map_room_width;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[7]);
            }
            if (find_room_from_dir(north, "EAST") != NULL)
            {
                posX = map_centX + map_room_width;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[5]);
            }
        }
        
        //draws player position as ball in the middle of map screen and inside current room
        DrawCircle(map_centX, map_centY, ball_rad, WHITE);

        EndDrawing();
    }
    
    CloseWindow();

}
