#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#include "ui/draw_images.h"
#include "game-state/room.h"
#include "game-state/game.h"

#define MAX_FILENAME_LEN (100)

/* See draw_images.h for documentation */
void draw_room(int width, int height, int pos_x, int  pos_yt, room_t room, game_t game)
{   
    
    BeginDrawing();

    char filename[MAX_FILENAME_LEN];

    snprintf(filename, MAX_FILENAME_LEN, "images/%s.png", room->room_id);

    Image room = LoadImage(filename);   
        
    ImageResize(&room, width, height);
          
    Texture2D texture = LoadTextureFromImage(room);
    // Image converted to texture, uploaded to GPU memory (VRAM)
        
    UnloadImage(room);   
    // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    DrawTexture(texture, pos_x, pos_y, WHITE);

    EndDrawing();

}

int* colors_list(int len)
{
    static int colors[len];

    for (int i = 0; i < len; i++)
    {
        colors[i] = rand();
    }

    return colors;
}

bool in_array(room_t room, room_t *list, int len)
{
    bool ret = false;
    for (int i = 0; i < len; i++)
    {
        if (room == list[i])
        {
            return true;
        }
    }
    return ret;
}

int num_rooms(game_t *game)
{
    int count = 0;
    room_list_t *rooms = get_all_rooms(game);
    while(rooms->next != NULL)
    {
        count++;
        rooms = rooms->next;
    }
    return count;
}

void draw_map(int width, int height, int pos_x, int pos_yt, room_t room, game_t *game) 
{
    int map_width, map_height, map_posx, map_posy, map_room_width, map_room_height, number_rooms;

    number_rooms = num_rooms(game);
    map_width = width/10;
    map_height = height/5; 
    map_room_width = map_width/ (number_rooms + 1);
    map_room_height = map_height/ (number_rooms + 1);

    int colors[number_rooms] = colors_list(number_rooms);

    room_list_t *rooms = get_all_rooms(game);
    room_t curr_room = rooms->room;
    int count_E = 0;
    int count_W = 0; 
    int count_S = 0; 
    int count_N = 0;
    if (rooms->next != NULL)
    {
        rooms = rooms->next;
    }

    while (find_room_from_dir(curr_room, "EAST") != NULL)
    {
        count_E++;
        curr_room = (find_room_from_dir(curr_room, "EAST");
    }

    curr_room = rooms[0];
    while (find_room_from_dir(curr_room, "WEST") != NULL)
    {
        count_W++;
        curr_room = (find_room_from_dir(curr_room, "WEST");
    }

    curr_room = rooms[0];
    while (find_room_from_dir(curr_room, "SOUTH") != NULL)
    {
        count_S++;
        curr_room = (find_room_from_dir(curr_room, "SOUTH");
    }

    curr_room = rooms[0];
    while (find_room_from_dir(curr_room, "NORTH") != NULL)
    {
        count_N++;
        curr_room = (find_room_from_dir(curr_room, "NORTH");
    }


    posX = (map_width/2) + count_E - count_W;
    posY = (map_height/2) + count_N - count_S; 

    room_t visited[number_rooms];
    counter j = 0;
    while (visited[number_rooms] != NULL)
    {
        while (rooms->next != NULL)
        {
            curr_room = rooms->room;
            visited[j] = curr_room;
            if (!in_array(curr_room, visited, number_rooms)
            {
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[j]);
            }
            j++;
            
            if ((find_room_from_dir(curr_room, "EAST") != NULL) && 
                    (!in_array((find_room_from_dir(curr_room, "EAST"), visited, number_rooms))
            {
                visited[j] = find_room_from_dir(curr_room, "EAST");
                posX += map_room_width;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[j]);
                j++;
            }
            if ((find_room_from_dir(curr_room, "WEST") != NULL) && 
                    (!in_array((find_room_from_dir(curr_room, "WEST"), visited, number_rooms))
            {
                visited[j] = find_room_from_dir(curr_room, "WEST");
                posX -= map_room_width;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[j]);
                j++;
            }
            if ((find_room_from_dir(curr_room, "SOUTH") != NULL) && 
                    (!in_array((find_room_from_dir(curr_room, "SOUTH"), visited, number_rooms))
            {
                visited[j] = find_room_from_dir(curr_room, "SOUTH");
                posY -= map_room_height;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[j]);
                j++;
            }

            if ((find_room_from_dir(curr_room, "NORTH") != NULL) && 
                    (!in_array((find_room_from_dir(curr_room, "NORTH"), visited, number_rooms))
            {
                visited[j] = find_room_from_dir(curr_room, "NORTH");
                posY += map_room_height;
                DrawRectangle(posX, posY, map_room_width, map_room_height, colors[j]);
                j++;
            }
        
            rooms = rooms->next;
        }
    }
    


/* See draw_images.h for documentation */
void draw_object(char *item_id)
{
    
}