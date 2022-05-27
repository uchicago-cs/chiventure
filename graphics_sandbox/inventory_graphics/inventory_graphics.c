#include "raylib.h"
#include "inventory_graphics.h"
#include "stdio.h"
#include "stdlib.h"


#define MAX_INVENTORY    21          // Maximum Number of Inventory Items


/* See iventory_graphics.h */
slot_t **populate_items(player_t *p, graphics_t *graphics)
{
    unsigned int rows = graphics->inventory->rows;
    unsigned int columns = graphics->inventory->columns;

    item_list_t *itemlst = get_all_items_in_inventory(p);
    
    slot_t **inv = (slot_t**)malloc(sizeof(slot_t*) * rows);
    
    for(unsigned int i = 0; i < rows; i++){
        inv[i] = (slot_t*)malloc(sizeof(slot_t*) * columns);
    }
    
    while(itemlst->next != NULL){
        for (unsigned int i = 0; i < rows; i++){
            for(unsigned int j = 0; j < columns; j++){
                inv[i][j].status = FULL;
                inv[i][j].item = itemlst->item;
                inv[i][j].item->inventory_x_pos = i;
                inv[i][j].item->inventory_y_pos = j;
            }
        }
    itemlst = itemlst->next;
    } 
    
    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < columns; j++){
            if (inv[i][j].status != FULL){
                inv[i][j].status = EMPTY;
            }
        }
    }
    return inv;
}

/* See inventory_graphics.h */
slot_t *new_slot(status s, item_t *item)
{
    slot_t *slot;
    int rc;

    slot = malloc(sizeof(slot_t));

    if (slot == NULL){
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }	

    rc = init_slot(slot,s,item);

    if (rc != SUCCESS){
        fprintf(stderr, "Could not initialize slot_t");
        return NULL;
    }
    
    return slot;
}

/* See inventory_graphics.h */
int init_slot(slot_t *slot, status s, item_t *item)
{
    assert(slot != NULL);
    
    slot->status = s;
    slot->item = item;

    return SUCCESS;
}

/* See inventory_graphics.h */
int free_slot(slot_t *slot)
{
    free(slot->item);
    free(slot);

    return SUCCESS;
}

/* See inventory_graphics.h */
player_inventory_t *new_player_inventory(graphics_t *graphics, slot_t **slots)
{
    player_inventory_t *inventory;
    int rc;

    inventory = (player_inventory_t*)malloc(sizeof(player_inventory_t));
    
    if (inventory == NULL){
        fprintf(stderr, "Could not allcoate memory for player_inventory");
        return NULL;
    }

    rc = init_player_inventory(inventory, graphics, slots);
    
    if (rc != SUCCESS){
        fprintf(stderr, "Initialization for player_inventory failed");
        return NULL;
    }    

    return inventory;
}

/* See inventory_graphics.h */
int init_player_inventory(player_inventory_t *player_inventory, 
                          graphics_t *graphics, slot_t **slots)
{
    assert(player_inventory != NULL);
    
    player_inventory->display = graphics->inventory;
    player_inventory->slots = slots;

    return SUCCESS;
}


/* See inventory_graphics.h */
int free_player_inventory(player_inventory_t *player_inventory)
{
    for(unsigned int i = 0; i < player_inventory->display->rows; i++){
        free(player_inventory->slots[i]);
    }
    free(player_inventory->slots);
    free(player_inventory->display);
    free(player_inventory);
    return SUCCESS;
}


/* See inventory_graphics.h */
int add_item_inventory(player_inventory_t *player_inventory, item_t *item)
{
    int change = 0;
    for(unsigned int i = 0; i < player_inventory->display->rows; i++) {
        for(unsigned int j = 0; j < player_inventory->display->columns; j++) {
            if (player_inventory->slots[i][j].status == EMPTY) {
                player_inventory->slots[i][j].item = item;
                change = 1;
                break;
            }
        }
        if (change == 1) {
            break;
        }
    }
    if (change == 0) {
        fprintf(stderr, "inventory full");
    }
    return SUCCESS;
}



/* See inventory_graphics.h */
int remove_item_inventory(player_inventory_t *player_inventory, item_t *item)
{
    if (player_inventory->slots[item->inventory_x_pos][item->inventory_y_pos].status != EMPTY) {
        free(player_inventory->slots[item->inventory_x_pos][item->inventory_y_pos].item);
        player_inventory->slots[item->inventory_x_pos][item->inventory_y_pos].status = EMPTY;
    } 
    else {
        fprintf(stderr, "inventory empty at position (%d,%d)\n", item->inventory_x_pos, item->inventory_y_pos);
    }
    return SUCCESS;
}


void runInventoryGrahpics(Vector2 screeDimension, Vector2 windowPosition, unsigned max_inventory
                          )
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Player Inventory Screen");


    Image balloonimg = LoadImage("test_images/balloon.png");
    ImageResize(&balloonimg,100,100);
    Texture2D cheems = LoadTextureFromImage(balloonimg);

    Rectangle slots[MAX_INVENTORY] = { 0 };     // Rectangles array
    
    for (int i = 0; i < MAX_INVENTORY; i++)
    {
        slots[i].x = 20.0f + 100.0f *(i%7) + 10.0f *(i%7);
        slots[i].y = 80.0f + 100.0f *(i/7) + 10.0f *(i/7);
        slots[i].width = 100.0f;
        slots[i].height = 100.0f;
    }

    int colorState[MAX_INVENTORY] = { 0 };           // Color state: 0-DEFAULT, 1-MOUSE_HOVER

    Vector2 mousePoint = { 0.0f, 0.0f };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePoint = GetMousePosition();

        for (int i = 0; i < MAX_INVENTORY; i++)
        {
            if (CheckCollisionPointRec(mousePoint, slots[i])) colorState[i] = 1;
            else colorState[i] = 0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Inventory", 350, 42, 20, BLACK);
            DrawText("press SPACE to see all items", GetScreenWidth() - 180, GetScreenHeight() - 40, 10, GRAY);
        


        for (int i = 0; i < MAX_INVENTORY; i++)    // Draw all rectangles
            {
                // draw the rectangles (all just grey for now)
                //DrawRectangleRec(slots[i], Fade(LIGHTGRAY, colorState[i]? 0.6f : 1.0f));
                DrawTextureRec(cheems, (Rectangle){0.0f,0.0f,slots[i].width, slots[i].height}, (Vector2){slots[i].x, slots[i].y}, WHITE);

                if (IsKeyDown(KEY_SPACE) || colorState[i])  // display text if mouse is hovering or SPACE is held
                {   
                    DrawRectangle((int)slots[i].x, (int)(slots[i].y + slots[i].height - 26), (int)slots[i].width, 20, BLACK);
                    DrawRectangleLinesEx(slots[i], 6, Fade(BLACK, 0.3f));
                    /*DrawText(colorNames[i], (int)(slots[i].x + slots[i].width - MeasureText(colorNames[i], 10) - 12),
                        (int)(slots[i].y + slots[i].height - 20), 10, colors[i]);*/

                }
            }


        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    UnloadTexture(cheems);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


}

int main()
{
}
