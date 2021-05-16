#include <string.h>
#include <stdio.h>
#include "game-state/game.h"
#include "game-state/room.h"
#include "raylib.h"
#include "common/ctx.h"
#include "ui/ui_ctx.h"
#include "game-state/room.h"

/* This is a sample 5 room map that displays the location of the player. The player is located in room 2. */
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int roomHeight = 130;
    const int roomWidth = 180;
    int centerYPos, centerXPos, radius;
    int posX = screenWidth/4, posY = 170;

    InitWindow(screenWidth, screenHeight, "Chiventure 5 Room Map Example (with cursor)");

    /* This is for initialization of a movable ball that could later function as a pointer/cursor for the player. */
    //Vector2 cursorBallPosition = {(float) screenWidth / 2, (float) screenHeight / 2};
    //Color cursorBallColor = WHITE;
    
    /* This value corresponds to the sensitivity of the cursor. Increasing move_unit increases the distance it covers
     * while keys are pressed.
     */
    //float move_unit = 5.0;
    
    //float cursorBallRadius = 8;
    

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

    chiventure_ctx_t *ctx = chiventure_ctx_new(game);
    
    ui_ctx_t *ui_ctx = ui_ctx_new(game);
    ui_ctx_init(ui_ctx, game);


    // Set the screen location of the map
    map_set_displaywin(ctx->ui_ctx->map, 0, 0, COLS, LINES-1);
    
    // Refresh the map centered on room 0,0,0
    //map_center_on(ctx, 0, 0, 0);

    CloseWindow();

    return 0;
}
