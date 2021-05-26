#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#include "ui/draw_images.h"
#include "game-state/room.h"
#include "game-state/game.h"

#define MAX_FILENAME_LEN (100)

/* See draw_images.h for documentation */
void draw_room_gui(int width, int height, int pos_x, int  pos_y, room_t *curr_room)
{
    // BeginDrawing();

    char filename[MAX_FILENAME_LEN] = "/home/grkapoor/cs220/chiventure/tests/wdl/examples/wdl/";

    strcat(filename, curr_room->room_id);

    strcat(filename, ".png");

    // snprintf(filename, MAX_FILENAME_LEN, "/home/grkapoor/cs220/chiventure/tests/wdl/examples/wdl/%s.png", room_id);

    // filename = “/home/grkapoor/cs220/chiventure/tests/wdl/examples/wdl/%s.png”, ctx->game->curr_room->room_id);

    Image room = LoadImage(filename);   
        
    ImageResize(&room, width, height);
          
    Texture2D texture = LoadTextureFromImage(room);
    // Image converted to texture, uploaded to GPU memory (VRAM)
        
    UnloadImage(room);   
    // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    DrawTexture(texture, pos_x, pos_y, WHITE);

    // EndDrawing();

}

// Color* colors_list()
// {
//     Color colors[8];

//     colors[0] = RED;
//     colors[1] = PINK;
//     colors[2] = PURPLE;
//     colors[3] = BLUE;
//     colors[4] = YELLOW;
//     colors[5] = GREEN;
//     colors[6] = ORANGE;
//     colors[7] = DARKGREEN;

//     return colors;
// }

// bool in_array(room_t room, room_t *list, int len)
// {
//     bool ret = false;
//     for (int i = 0; i < len; i++)
//     {
//         if (room == list[i])
//         {
//             return true;
//         }
//     }
//     return ret;
// }

// int num_rooms(game_t *game)
// {
//     int count = 0;
//     room_list_t *rooms = get_all_rooms(game);
//     while(rooms->next != NULL)
//     {
//         count++;
//         rooms = rooms->next;
//     }
//     return count;
// }

void draw_map(int width, int height, room_t *curr_room)
{
    int map_width, map_height, map_room_width, map_room_height, map_centX, map_centY, ball_rad;
    map_width = width / 10;
    map_height = height / 5;
    map_room_width = map_width / 3;
    map_room_height = map_height / 3;
    map_centX = map_width/2;
    map_centY = -1 * (map_height/2);   
    ball_rad = map_room_width / 5;
    
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
    
}

/* See draw_images.h for documentation */
void draw_object(char *item_id)
{
    
}
