/*
 * This example program runs a full instance of chiventure with an in-memory game.
 * The CLI is monkey-patched to accept functions that serve to showcase room generation.
 * 
 *  Functions in demo: EDGES_NEW, SPECGRAPH_NEW, ROOMSPEC_CORRELATION, ROOM_EXISTS_IN_DIRECTION, FIND_ROOM_IN_DIRECTION
 *  RANDOM_FIRST_ROOM
 */

#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "openworld/autogenerate.h"
#include "game-state/path.h"


#define OUTPUT_BUFFER_SIZE 200

/* ROOMSPECS
   Pre-declaring roomspecs like this is important as we need to preserve 
   num_built between function calls in order to generate unique rooms. */
roomspec_t *rspec_lvl0 = NULL;
roomspec_t *rspec_lvl1 = NULL;
roomspec_t *rspec_lvl2 = NULL;
roomspec_t *rspec_lvl3 = NULL;

roomspec_t** roomspecs = NULL;

int** edges;

specgraph_t* specgraph;

void initialize_sample_structs() {
    rspec_lvl0 = roomspec_new("Library", "JCL", "John Crerar Library", NULL, 1);
    rspec_lvl1 = roomspec_new("Dungeon", "Ryerson 251", "Where CS students switch majors to bizcon", NULL, 2);
    rspec_lvl2 = roomspec_new("Bar", "Jimmy's", "Formally known as Woodlawn Tap", NULL, 3);
    rspec_lvl3 = roomspec_new("Beach", "57th St. Beach", "Not a real beach ", NULL, 4);

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

    specgraph = specgraph_new(4, roomspecs, edges);
}

chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");

    load_normal_mode(game);

    /* Create room1, the initial room */
    room_t *room1 = room_new("room1", "This is room 1", "This is the first room.");
    add_room_to_game(game, room1);
    game->curr_room = room1;

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}


const char *banner = "THIS IS AN OPENWORLD EXAMPLE PROGRAM";

char *count_rooms(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx) {
    if (tokens[1] != NULL) {
        return "Please speak english! So uncivilized...";
    }

    int count = specgraph->num_roomspecs;

    static char buffer[OUTPUT_BUFFER_SIZE];
    snprintf(buffer, OUTPUT_BUFFER_SIZE, "total number of rooms: %d", count);
    return buffer;
}

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
    snprintf(buffer, OUTPUT_BUFFER_SIZE, "Room Name: %s || Short Description: %s || Long Description: %s", 
        roomspecs[index]->room_name, roomspecs[index]->short_desc, roomspecs[index]->long_desc);
    return buffer;
}

int main(int argc, char **argv)
{   

    initialize_sample_structs();

    chiventure_ctx_t *ctx = create_sample_ctx();

    add_entry("COUNT", count_rooms, NULL, ctx->cli_ctx->table);
    add_entry("ROOMS", list_roomspecs, NULL, ctx->cli_ctx->table);
    add_entry("ROOMINFO", room_info, NULL, ctx->cli_ctx->table);
    
    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    if (rspec_lvl0 == NULL) {
        printf("Failed\n");
    }

    printf("%s\n", roomspecs[1]->short_desc);

    return 0;
}
