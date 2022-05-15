#include "raylib.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#include "npc_graphics.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* See npc_graphics.h*/
npc_action_t* ActionNew(char* action_name, char* action_image_path, unsigned frame_number,
                       double switch_frequency) {
    npc_action_t* res = (npc_action_t*)malloc(sizeof(npc_action_t));
    int rc = ActionInit(res, action_name, action_image_path, frame_number, switch_frequency);
    assert(rc);
    return res;
}

/* See npc_graphics.h*/
int ActionInit(npc_action_t* pointer, char* action_name, char* action_image_path, unsigned frame_number,
                       double switch_frequency) {
    assert(pointer != NULL);
    pointer->action_name = action_name;
    pointer->action_image_path = action_image_path;
    pointer->frame_number = frame_number;
    pointer->switch_frequency = switch_frequency;
    pointer->next = NULL;
    return 1;
}

/* See npc_graphics.h*/
int ActionFree(npc_action_t* pointer) {
    assert(pointer != NULL);
    free(pointer);
    return 1;
}


/* See npc.h */
npc_action_t* GetAction(char* action_name, npc_info_t* npc_graphics) {
    npc_action_t* current_action = npc_graphics->head_action;
    do {
        if(!strcmp(action_name, current_action->action_name)) {
            return current_action;
        }
    } while((current_action = current_action->next));
    return NULL;
}


/* See npc_graphics.h*/
npc_line_t* LineNew(char* line_name, const char* line) {
    npc_line_t* res = (npc_line_t*)malloc(sizeof(npc_line_t));
    int rc = LineInit(res, line_name, line);
    assert(rc);
    return res;
}

/* See npc_graphics.h*/
int LineInit(npc_line_t* pointer, char* line_name, const char* line) {
    assert(pointer != NULL);
    pointer->line_name = line_name;
    pointer->line= line;
    pointer->next = NULL;
    return 1;
}

/* See npc_graphics.h*/
int LineFree(npc_line_t* pointer) {
    assert(pointer != NULL);
    free(pointer);
    return 1;
}


/* See npc.h */
npc_line_t* GetLine(char* line_name, npc_info_t* npc_graphics) {
    npc_line_t* current_line = npc_graphics->head_line;
    do {
        if(!strcmp(line_name, current_line->line_name)) {
            return current_line;
        }
    } while((current_line = current_line->next));
    return NULL;
}

/* See npc.h */
npc_info_t* GetNPC(char* NPC_name, npc_info_t* npcs) {
    npc_info_t* current_npc = npcs;
    do {
        if(!(strcmp(NPC_name,current_npc->npc_name))) {
            return current_npc;
        }
    } while ((current_npc = current_npc->next));
    return NULL;
}

/* A testing input for NPC graphics */
npc_info_t* synthesizeTest() {
    npc_info_t* res;
    res = malloc(sizeof(npc_info_t));
    res->npc_name = "Dhirpal";
    res->head_action = ActionNew("Default","testimages/dhirpal/action/default.png",3,3);
    res->head_line = LineNew("TedTalk", "Welcome to my Ted Talk");
    return res;
}

/* Another testing input for NPC graphics */
npc_info_t* synthesizeTest2() {
    npc_info_t* res;
    res = malloc(sizeof(npc_info_t));
    res->npc_name = "GangnamStyle";
    res->head_action = ActionNew("Dance","testimages/GangnamStyle/Dance/GangnamStyle.png",22,7);
    res->head_line = LineNew("Default", "Let's Dance");
    return res;
}

/* Another testing input for NPC graphics */
npc_info_t* synthesizeTest3() {
    npc_info_t* res;
    res = malloc(sizeof(npc_info_t));
    res->npc_name = "Fire";
    res->head_action = ActionNew("Burn","testimages/Fire/Default/fire.png",6,6);
    res->head_line = LineNew("Crack", "Crack crack...");
    return res;
}

void runNPCGraphics(npc_graphics_t* npc_graphics) {

 // Initialization
    //--------------------------------------------------------------------------------------


    npc_info_t* current_npc = GetNPC(npc_graphics->current_npc,npc_graphics->npc_linkedlist);
    

    const int screenWidth = npc_graphics->WindowSize.x;
    const int screenHeight = npc_graphics->WindowSize.y;

    InitWindow(screenWidth, screenHeight, current_npc->npc_name);
    SetWindowPosition(npc_graphics->WindowPos.x, npc_graphics->WindowPos.y);

    Texture2D texture = LoadTexture((const char*)current_npc->head_action->action_image_path);
    

    float textureSize[2] = { (float)texture.width, (float)texture.height };
    
    // Set shader values (they can be changed later)

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    int numframe = current_npc->head_action->frame_number;
    Rectangle frameRec = { 0.0f, 0.0f, (float)texture.width/numframe, (float)texture.height };
    int currentFrame = 0;

    int framescounter = 0;
    double frameSpeed = current_npc->head_action->switch_frequency;

    const char* NPC_line = (GetLine(npc_graphics->current_line,current_npc))->line;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        framescounter ++;

        if (framescounter >= 60/frameSpeed) {
            framescounter = 0;
            currentFrame ++;

            if (currentFrame > numframe) currentFrame = 0;
            frameRec.x = (float)currentFrame*(float)texture.width/numframe;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
                DrawTextureRec(texture, frameRec,(Vector2){0,0},RAYWHITE);
                DrawRectangle(0,(GetScreenHeight()-60),GetScreenWidth(),GetScreenHeight(),WHITE);
                DrawText(NPC_line, 20, (GetScreenHeight()-40), 20, npc_graphics->textcolor);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}



int main(void)
{   
    //npc_info_t* current_npc = synthesizeTest();

    //runNPCGraphics(&current_npc, "Dhirpal", "Default","Tedtalk", (Vector2){800,0},(Vector2){600,400},BLACK);
    //npc_info_t* current_npc = synthesizeTest2();


    //runNPCGraphics(&current_npc, "Dhirpal", "Default","Default", (Vector2){800,0},(Vector2){600,400},BLACK);
    //npc_info_t* current_npc = synthesizeTest2();

    npc_info_t* npc_1 = synthesizeTest();
    npc_info_t* npc_2 = synthesizeTest2();
    npc_info_t* npc_3 = synthesizeTest3();
    npc_info_t* npcs = npc_1;
    npcs->next = npc_2;
    npcs->next->next = npc_3;
    npc_graphics_t npc_graphics = {(Vector2){1200,0},(Vector2){160,500},RED,"Fire","Burn","Crack",npcs};
    runNPCGraphics(&npc_graphics);


    return 0;
}
