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

/* See npc_graphics.h*/
npc_info_t* NewNPCInfo(char* npc_name, npc_action_t* head_action, npc_line_t* head_line, 
                       npc_info_t* next) 
{
    npc_info_t* res = (npc_info_t*)malloc(sizeof(npc_info_t));
    int rc = InitNPCInfo(res,npc_name,head_action,head_line,next);
    assert(rc);
    return res;
}

/* See npc_graphics.h*/
int InitNPCInfo(npc_info_t* pointer, char* npc_name, npc_action_t* head_action, npc_line_t* head_line, 
                npc_info_t* next)
{
    assert(pointer != NULL);
    pointer->head_action=head_action;
    pointer->head_line=head_line;
    pointer->npc_name=npc_name;
    pointer->next=next;
}

int FreeNPCInfo(npc_info_t* pointer)
{
    assert(pointer != NULL);
    npc_line_t* current_line = pointer->head_line;
    npc_line_t* line_tmp;
    npc_action_t* current_action = pointer->head_action;
    npc_action_t* action_tmp;
    while((line_tmp=current_line)!=NULL) {
        current_line = current_line->next;
        LineFree(line_tmp);
    }
    while((action_tmp=current_action)!=NULL) {
        current_action = current_action->next;
        ActionFree(action_tmp);
    }
    free(pointer);
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

