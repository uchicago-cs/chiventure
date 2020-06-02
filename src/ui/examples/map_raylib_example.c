#include <string.h>
#include <stdio.h>
#include "game-state/game.h"
#include "game-state/room.h"
#include "raylib.h"

/* Create a sample map for a chiventure game
 *
 * Parameters: None
 *
 */


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const char *banner = "THIS IS AN EXAMPLE PROGRAM";

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    room_t *room3 = room_new("room2", "This is room 2", "Precisely, this is the third room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");
    create_connection(game, "room1", "room3", "SOUTH");


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (find_room_from_dir(room1, "North") != NULL)
            {
                DrawRectangle(screenWidth/4*2 - 60, 100, 120, 60, RED);
            }
            if (find_room_from_dir(room1, "South") != NULL)
            {
            DrawRectangleGradientH(screenWidth/4*2 - 90, 170, 180, 130, MAROON, GOLD);
            }

        /* Free default game and replace it with ours */
        EndDrawing();
            //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
      // Close window and OpenGL context
    //-----------------


    return 0;
}