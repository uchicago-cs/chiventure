#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "action_management/actionmanagement.h"
#include "ui/gui.h"
#include "raylib.h"
#include "game-state/game.h"
#include "game-state/room.h"


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
    create_connection(game, "room2", "room1", "SOUTH");
    create_connection(game, "room2", "room3", "EAST");
    create_connection(game, "room3", "room2", "WEST");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
} 

int main() {
    chiventure_ctx_t *ctx = create_sample_ctx();

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
        char filename[100] = "../../../../src/ui/examples/";

        strcat(filename, ctx->game->curr_room->room_id);

      	strcat(filename, ".png");

        Image room = LoadImage(filename);   

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

        int map_width, map_height, map_room_width, map_room_height, map_topX, map_topY, ball_rad;
        map_width = height / 2;
        map_height = width / 5;
        map_room_width = map_width / 3;
        map_room_height = map_height / 3;
        map_topX = 5;
        map_topY = 5;   
        ball_rad = map_room_width / 10;
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
        DrawRectangle(map_topX, map_topY, map_width, map_height, BLACK);
        
        int posX = map_topX + map_width/2 - map_room_width/2;
        int posY = map_topY + map_height/2 - map_room_height/2;
        // current room
        DrawRectangle(posX, posY, map_room_width, map_room_height, colors[0]);

        //draw surrounding rooms around current room
        if (find_room_from_dir(curr_room, "EAST") != NULL)
        {   
            int tempX = posX + map_room_width;
            DrawRectangle(tempX, posY, map_room_width, map_room_height, colors[1]);

            room_t *east = find_room_from_dir(curr_room, "EAST");
            // draw rooms above and below the room that is east of the current room
            // northeast and southeast rooms to the current room
            if (find_room_from_dir(east, "NORTH") != NULL)
            {
                int tempY = posY - map_room_height;
                DrawRectangle(tempX, tempY, map_room_width, map_room_height, colors[5]);
            }
            if (find_room_from_dir(east, "SOUTH") != NULL)
            {
                int tempY = posY + map_room_height;
                DrawRectangle(tempX, tempY, map_room_width, map_room_height, colors[6]);
            }

        }
        if (find_room_from_dir(curr_room, "WEST") != NULL)
        {
            int tempX = posX - map_room_width;
            DrawRectangle(tempX, posY, map_room_width, map_room_height, colors[2]);

            room_t *west = find_room_from_dir(curr_room, "WEST");
            // draw rooms above and below the room that is west of the current room
            // northwest and southwest rooms to the current room
            if (find_room_from_dir(west, "NORTH") != NULL)
            {
                int tempY = posY - map_room_height;
                DrawRectangle(tempX, tempY, map_room_width, map_room_height, colors[7]);
            }
            if (find_room_from_dir(west, "SOUTH") != NULL)
            {
                int tempY = posY + map_room_height;
                DrawRectangle(tempX, tempY, map_room_width, map_room_height, colors[8]);
            }
        }
        if (find_room_from_dir(curr_room, "SOUTH") != NULL)
        {
            int tempY = posY + map_room_height;
            DrawRectangle(posX, tempY, map_room_width, map_room_height, colors[3]);

            room_t *south = find_room_from_dir(curr_room, "SOUTH");
            // draw rooms next to the room that is south of the current room
            // southeast and southwest rooms to the current room
            if (find_room_from_dir(south, "EAST") != NULL)
            {
                int tempX = posX + map_room_width;
                DrawRectangle(tempX, tempY, map_room_width, map_room_height, colors[6]);
            }
            if (find_room_from_dir(south, "WEST") != NULL)
            {
                int tempX = posX - map_room_width;
                DrawRectangle(tempX, tempY, map_room_width, map_room_height, colors[8]);
            }
        }
        if (find_room_from_dir(curr_room, "NORTH") != NULL)
        {
            int tempY = posY - map_room_height;
            DrawRectangle(posX, tempY, map_room_width, map_room_height, colors[4]);

            room_t *north = find_room_from_dir(curr_room, "NORTH");
            // draw rooms next to the room that is north of the current room
            // northeast and northwest rooms to the current room
            if (find_room_from_dir(north, "WEST") != NULL)
            {
                int tempX = posX + map_room_width;
                DrawRectangle(tempX, tempY, map_room_width, map_room_height, colors[7]);
            }
            if (find_room_from_dir(north, "EAST") != NULL)
            {
                int tempX = posX + map_room_width;
                DrawRectangle(tempX, tempY, map_room_width, map_room_height, colors[5]);
            }
        }
        
        //draws player position as ball in the middle of map screen and inside current room
        DrawCircle(map_topX + map_width/2, map_topY + map_height/2, ball_rad, WHITE);

        EndDrawing();
    }
    
    CloseWindow();
}