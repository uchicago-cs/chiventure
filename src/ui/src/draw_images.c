#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#include "ui/draw_images.h"

#define MAX_FILENAME_LEN (100)

/* See draw_images.h for documentation */
void draw_room(int width, int height, int pos_x, int  pos_yt, char *room_id)
{
    BeginDrawing();

    char filename[MAX_FILENAME_LEN];

    snprintf(filename, MAX_FILENAME_LEN, "images/%s.png", room_id);

    Image room = LoadImage(filename);   
        
    ImageResize(&room, width, height);
          
    Texture2D texture = LoadTextureFromImage(room);
    // Image converted to texture, uploaded to GPU memory (VRAM)
        
    UnloadImage(room);   
    // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    DrawTexture(texture, pos_x, pos_y, WHITE);

    EndDrawing();

}

/* See draw_images.h for documentation */
void draw_object(char *item_id)
{
    
}