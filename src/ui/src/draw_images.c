#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#include "ui/draw_images.h"

#define MAX_FILENAME_LEN (100)

/* See draw_images.h for documentation */
void draw_room_gui(int width, int height, int pos_x, int  pos_y, char *room_id)
{
    // BeginDrawing();

    char filename[MAX_FILENAME_LEN] = "/home/grkapoor/cs220/chiventure/tests/wdl/examples/wdl/";

    strcat(filename, room_id);

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

/* See draw_images.h for documentation */
void draw_object(char *item_id)
{
    
}