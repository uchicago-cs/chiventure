/*
 * This example program runs a full instance of chiventure with an in-memory game.
 * The CLI is monkey-patched to accept functions that serve to showcase room generation.
 * 
 *  Purpose of demo: Display versatility and efficiency of new specgraph_t struct, especially
 *  with respects to its edges attribute
 */

#include <stdio.h>
#include <string.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "openworld/autogenerate.h"
#include "openworld/game_autogenerate.h"
#include "game-state/path.h"


#define OUTPUT_BUFFER_SIZE 200

/* ROOMSPECS
   Pre-declaring roomspecs like this is important as we need to preserve 
   num_built between function calls in order to generate unique rooms. */
roomspec_t *rspec_lvl0 = NULL;
roomspec_t *rspec_lvl1 = NULL;
roomspec_t *rspec_lvl2 = NULL;
roomspec_t *rspec_lvl3 = NULL;

//Declaring the array that will contain all of the roomspecs
roomspec_t** roomspecs = NULL;

//EDGES: This will contain all of the edges for the specgraph
int** edges;

//SPECGRAPH: This will be the main specgraph struct that is used throughout the demo
specgraph_t* specgraph;

//Game used for demo
game_t* game;

/* Initializes the sample, "in-memory", gencontext and other component structs. 
   Uses placeholder variables declared above. */
void initialize_sample_structs() {
    rspec_lvl0 = roomspec_new("library", "JCL", "John Crerar Library", NULL);
    rspec_lvl0->tag = 0;
    rspec_lvl1 = roomspec_new("dungeon", "Ryerson 251", "Where CS students' dreams go to die", NULL);
    rspec_lvl1->tag = 1;
    rspec_lvl2 = roomspec_new("bar", "Jimmy's", "Formally known as Woodlawn Tap", NULL);
    rspec_lvl2->tag = 2;
    rspec_lvl3 = roomspec_new("beach", "57th St. Beach", "Not a real beach ", NULL);
    rspec_lvl3->tag = 3;

    roomspecs = (roomspec_t**)malloc(sizeof(roomspec_t*) * 4);
    roomspecs[0] = rspec_lvl0;
    roomspecs[1] = rspec_lvl1;
    roomspecs[2] = rspec_lvl2;
    roomspecs[3] = rspec_lvl3;

    int* array=(int*)malloc(16*sizeof(int));
    for (unsigned int i = 0; i < 16; i++)
    {
        array[i] = 1;
    }

    edges = edges_new(array, 4, 4);
    edges[0][1] = 0;
    edges[1][0] = 0;
    edges[3][2] = 4;
    edges[2][3] = 4;

    specgraph = specgraph_new(4, roomspecs, edges);
}

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    game = game_new("Welcome to Chiventure!");
    game->specgraph = specgraph;

    load_normal_mode(game);

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}


const char *banner = "THIS IS AN OPENWORLD EXAMPLE PROGRAM";

/* Defines a new CLI operation that: 
   Outputs current number of roomspecs within a specgraph. */
char *count_rooms(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx) {
    if (tokens[1] != NULL) {
        return "Please speak english! So uncivilized...";
    }

    int count = specgraph->num_roomspecs;

    static char buffer[OUTPUT_BUFFER_SIZE];
    snprintf(buffer, OUTPUT_BUFFER_SIZE, "total number of rooms: %d", count);
    return buffer;
}
/* Defines a new CLI operation that: 
   Outputs the list of the names of the rooms in roomspecs. */
char *list_roomspecs(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    if (tokens[1] != NULL) {
        return "Please speak english! So uncivilized...";
    }
    static char buffer[OUTPUT_BUFFER_SIZE];

    snprintf(buffer, OUTPUT_BUFFER_SIZE, "1. %s\n2. %s\n3. %s\n4. %s", roomspecs[0]->room_name, roomspecs[1]->room_name,
        roomspecs[2]->room_name, roomspecs[3]->room_name);

    return buffer;
}

/* Defines a new CLI operation that: 
   Outputs information about a specified room */
char *room_info(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx) {
    if (tokens[2] != NULL) {
        return "Please speak english! So uncivilized...";
    }
    if (tokens[1] == NULL) {
        return "Please pick a room to learn more about";
    }

    int index = atoi(tokens[1]) - 1;

    if (index >= specgraph->num_roomspecs)
    {
        return "There aren't that many rooms";
    }

    static char buffer[OUTPUT_BUFFER_SIZE];
    snprintf(buffer, OUTPUT_BUFFER_SIZE, "Room Spec Name: %s || Short Description: %s || Long Description: %s", 
        roomspecs[index]->room_name, roomspecs[index]->short_desc, roomspecs[index]->long_desc);
    return buffer;
}

/* Defines a new CLI operation that: 
   Outputs how likely two rooms are to generate next to each other. */
char *relation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx) {
    if (tokens[3] != NULL) {
        return "Please speak english! So uncivilized...";
    }
    if (tokens[1] == NULL) {
        return "Please specify two rooms";
    }
    if (tokens[2] == NULL) {
        return "Please specify a second room";
    }

    int index1 = -1;
    int index2 = -1;

    for (unsigned int i = 0; i < 4; i++)
    {
        if (strcmp(tokens[1], roomspecs[i]->room_name) == 0)
        {
            index1 = roomspecs[i]->tag;
        }
        else if (strcmp(tokens[2], roomspecs[i]->room_name) == 0)
        {
            index2 = roomspecs[i]->tag;
        }
    }


    if (index1 == -1  || index2 == -1) {
        return "Not a valid input";
    }


    int prob = edges[index1][index2];
    static char buffer[OUTPUT_BUFFER_SIZE];
    snprintf(buffer, OUTPUT_BUFFER_SIZE, "The chances of a %s and a %s spawning next to each other is %d out of 5", tokens[1], tokens[2], prob);
    return buffer;
}

/* Defines a new CLI operation that: 
   Randomly generates a first room and outputs the room name. */
char *first_room(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx) {
    random_first_room(game);

    room_list_t* rooms = NULL;
    rooms = get_all_rooms(game);

    room_t* first = rooms->room;
    
    static char buffer[OUTPUT_BUFFER_SIZE];
    snprintf(buffer, OUTPUT_BUFFER_SIZE, "The first room generated is the %s at coordinates (%d, %d)", 
                first->room_id, first->coords->x, first->coords->y);
    return buffer;

    return "No first room";

}

int main(int argc, char **argv)
{   

    initialize_sample_structs();

    chiventure_ctx_t *ctx = create_sample_ctx();

    add_entry("COUNT", count_rooms, NULL, ctx->cli_ctx->table);
    add_entry("ROOMS", list_roomspecs, NULL, ctx->cli_ctx->table);
    add_entry("ROOMINFO", room_info, NULL, ctx->cli_ctx->table);
    add_entry("RELATION", relation, NULL, ctx->cli_ctx->table);
    add_entry("FIRST", first_room, NULL, ctx->cli_ctx->table);
    
    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}