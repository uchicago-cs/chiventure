#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "ui/draw_images.h"


#define MAX_FILENAME_LEN (100)

/* See draw_images.h for documentation */
void draw_room_gui(int width, int height, int pos_x, int pos_y, char *filepath, room_t *curr_room)
{

    strcat(filepath, curr_room->room_id);

    strcat(filepath, ".png");

    Image room = LoadImage(filepath);   
        
    ImageResize(&room, width, height);

    /* Image converted to texture, uploaded to GPU memory (VRAM) */
    Texture2D texture = LoadTextureFromImage(room);
    
    /* Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM */
    UnloadImage(room);   

    DrawTexture(texture, pos_x, pos_y, WHITE);


}

/* See draw_images.h for documentation */
void draw_map(int width, int height, room_t *curr_room)
{
    int map_width, map_height, map_room_width, map_room_height, map_topX, map_topY, ball_rad;
    map_width = height / 2;
    map_height = width / 5;
    map_room_width = map_width / 3;
    map_room_height = map_height / 3;
    map_topX = 5;
    map_topY = 5;
    ball_rad = map_room_width / 10;

    Color colors[8];

    colors[0] = RED;
    colors[1] = PINK;
    colors[2] = PURPLE;
    colors[3] = BLUE;
    colors[4] = YELLOW;
    colors[5] = GREEN;
    colors[6] = ORANGE;
    colors[7] = DARKGREEN;

    /* map background */
    DrawRectangle(map_topX, map_topY, map_width, map_height, BLACK);

    int posX = map_topX + map_width / 2 - map_room_width / 2;
    int posY = map_topY + map_height / 2 - map_room_height / 2;
    /* draw current room */
    DrawRectangle(posX, posY, map_room_width, map_room_height, colors[0]);

    /* draw surrounding rooms around current room */
    if (find_room_from_dir(curr_room, "EAST") != NULL)
    {
        int tempX = posX + map_room_width;
        DrawRectangle(tempX, posY, map_room_width, map_room_height, colors[1]);

        room_t *east = find_room_from_dir(curr_room, "EAST");
        /* draw rooms above and below the room that is east of the current room
        northeast and southeast rooms to the current room */
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
        /* draw rooms above and below the room that is west of the current room
        northwest and southwest rooms to the current room */
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
        /* draw rooms next to the room that is south of the current room
        southeast and southwest rooms to the current room */
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
        /* draw rooms next to the room that is north of the current room
        northeast and northwest rooms to the current room */
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

    /* draws player position as ball in the middle of map screen and inside current room */
    DrawCircle(map_topX + map_width / 2, map_topY + map_height / 2, ball_rad, WHITE);
}


