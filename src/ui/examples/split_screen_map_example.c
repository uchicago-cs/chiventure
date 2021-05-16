#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game-state/game.h"
#include "game-state/room.h"
#include "raylib.h"
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

    /* This begins the visual of the map portion */
    
        const int mapWidth = WindowWidth/10;
    const int mapHeight = WindowHeight/10;
    const int roomHeight = mapHeight/5;
    const int roomWidth = mapWidth/5;
    int centerYPos, centerXPos, radius;
    int posX = ScreenWidth/4, posY = 170;

    InitWindow(ScreenWidth, ScreenHeight, "Chiventure 5 Room Map Example (with cursor)");

    /* This is for initialization of a movable ball that could later function as a pointer/cursor for the player. */
    Vector2 cursorBallPosition = {(float) mapWidth/ 2, (float) ((mapHeight / 2) - roomHeight)};
    Color cursorBallColor = WHITE;
    
    /* This value corresponds to the sensitivity of the cursor. Increasing move_unit increases the distance it covers
     * while keys are pressed.
     */
    float move_unit = 5.0;
    
    float cursorBallRadius = 2;
    

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room. It is Blue.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room. It is Red.");
    room_t *room3 = room_new("room3", "This is room 3", "Precisely, this is the third room. It is Green.");
    room_t *room4 = room_new("room4", "This is room 4", "Precisely, this is the third room. It is Gold.");
    room_t *room5 = room_new("room5", "This is room 5", "Precisely, this is the third room. It is Gray.");

    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    add_room_to_game(game, room4);
    add_room_to_game(game, room5);

    game->curr_room = room2;
    game->final_room = room5;

    /* build 5 room map connection */
    create_connection(game, "room1", "room2", "WEST");
    create_connection(game, "room2", "room3", "EAST");
    create_connection(game, "room3", "room2", "WEST");
    create_connection(game, "room3", "room4", "NORTH");
    create_connection(game, "room3", "room5", "SOUTH");

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

        //Draw Map Image
        BeginDrawing();
        int heightbuf2 = 150;
        int rectHeight = 120;

        ClearBackground(RAYWHITE);

        // Drawing the Color Rectangles for each room
        if (!(strcmp(ctx->game->curr_room->room_id, "room1")))
            DrawRectangle (ScreenWidth/4, ScreenHeight/10, ScreenWidth/2, ScreenHeight/2, DARKBLUE);
        else if (!(strcmp(ctx->game->curr_room->room_id, "room2"))) 
            DrawRectangle (ScreenWidth/4, ScreenHeight/10, ScreenWidth/2, ScreenHeight/2, MAROON);
        else if (!(strcmp(ctx->game->curr_room->room_id, "room3"))) 
            DrawRectangle (ScreenWidth/4, ScreenHeight/10, ScreenWidth/2, ScreenHeight/2, DARKGREEN);
        else 
            DrawRectangle (ScreenWidth/4, ScreenHeight/10, ScreenWidth/2, ScreenHeight/2, DARKBROWN); 

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

        /* Updates ball cursor with arrow keys or WASD*/
        if (IsKeyDown(KEY_RIGHT)) cursorBallPosition.x += move_unit;
        if (IsKeyDown(KEY_LEFT)) cursorBallPosition.x -= move_unit;
        if (IsKeyDown(KEY_UP)) cursorBallPosition.y -= move_unit;
        if (IsKeyDown(KEY_DOWN)) cursorBallPosition.y += move_unit;

        if (IsKeyDown(KEY_D)) cursorBallPosition.x += move_unit;
        if (IsKeyDown(KEY_A)) cursorBallPosition.x -= move_unit;
        if (IsKeyDown(KEY_W)) cursorBallPosition.y -= move_unit;
        if (IsKeyDown(KEY_S)) cursorBallPosition.y += move_unit;

        BeginDrawing();

        ClearBackground(BLACK);

        posY = 17; //starting map Y position
            
        if (game->curr_room != NULL)
        {
            centerXPos = mapWidth/4*2;
            centerYPos = mapWidth/4*2 - 160;
            radius = 1;

            DrawRectangle(mapWidth/4*2 - 9, 17, roomWidth, roomHeight, RED);
            DrawCircle(centerXPos, centerYPos, radius, LIGHTGRAY);
        }

        /*starting at a room, draw a room that either exists near it in any direction */
        if (find_room_from_dir(room1 , "WEST") != NULL)
        {
            posX = mapWidth/4;

            DrawRectangle(posX, posY, roomWidth, roomHeight, BLUE);
        }

        posX = mapWidth/4 + 45;

        if (find_room_from_dir(game->curr_room, "EAST") != NULL)
        {
            DrawRectangle(posX, posY, roomWidth, roomHeight, GREEN);       
        }
            
        if (find_room_from_dir(room3, "NORTH") != NULL)
        {
            posY = 4;

            DrawRectangle(posX, posY, roomWidth, roomHeight, GOLD);       
        }

        if (find_room_from_dir(room3, "SOUTH") != NULL)
        {
            posY = 30;

            DrawRectangle(posX, posY, roomWidth, roomHeight, GRAY);       
        }

        /* Draws the ball cursor in the current position according to user input */
        DrawCircleV(cursorBallPosition, cursorBallRadius, cursorBallColor);


        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
