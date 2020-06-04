#include <string.h>
#include <stdio.h>
#include "game-state/game.h"
#include "game-state/room.h"
#include "raylib.h"

/* This is a sample 5 room map that displays the location of the player. The player is located in room 2. */
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Chiventure 5 Room Map Example");

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

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
            if (game->curr_room != NULL)
            {
                DrawRectangle(screenWidth/4*2 - 90, 170, 180, 130, RED);
                DrawCircle(screenWidth/4*2, screenWidth/4*2 - 160, 15, WHITE);
            }

            /*starting at a room, draw a room that either exists near it in any direction */
            if (find_room_from_dir(room1 , "WEST") != NULL)
            {
                DrawRectangle(screenWidth/4 - 70, 170, 180, 130, BLUE);
            }

            if (find_room_from_dir(game->curr_room, "EAST") != NULL)
            {
                DrawRectangle(screenWidth/4 + 290, 170, 180, 130, GREEN);       
            }
            
            if (find_room_from_dir(room3, "NORTH") != NULL)
            {
                DrawRectangle(screenWidth/4 + 290, 40, 180, 130, GOLD);       
            }

            if (find_room_from_dir(room3, "SOUTH") != NULL)
            {
                DrawRectangle(screenWidth/4 + 290, 300, 180, 130, GRAY);       
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}