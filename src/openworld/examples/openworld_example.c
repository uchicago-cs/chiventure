/*
 * This example program runs a full instance of chiventure with an in-memory game.
 * The CLI is monkey-patched to accept functions that serve to showcase room generation.
 * 
 *  - LEVELGEN: This is a CLI-level operation that triggers level-oriented generation. 
 *              Someday, we hope chiventure will internally use this functionality 
 *              to allow rooms to be automatically generated in a level-oriented way.
 *  - RECURGEN: This is a CLI-level operation that triggers recursive generation. 
 *              Someday, we hope chiventure will internally use this functionality 
 *              to allow rooms within a radius to be generated.
 */

#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "openworld/autogenerate.h"


#define OUTPUT_BUFFER_SIZE 50


const char *banner = "THIS IS AN OPENWORLD EXAMPLE PROGRAM";


/* Creates a sample in-memory game */
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


/* Defines a new CLI operation that triggers level-oriented generation*/
char *level_gen(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    /* This operation has to be called without parameter */
    if(tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }
    
    /* Create speclist */
    roomspec_t *roomspec0 = roomspec_new("level_0_room", "A level-0 room.", "A room with difficulty level 0.", NULL);
    roomspec_t *roomspec1 = roomspec_new("level_1_room", "A level-1 room.", "A room with difficulty level 1.", NULL);
    roomspec_t *roomspec2 = roomspec_new("level_2_room", "A level-2 room.", "A room with difficulty level 2.", NULL);
    roomspec_t *roomspec3 = roomspec_new("level_3_room", "A level-3 room.", "A room with difficulty level 3.", NULL);
    
    speclist_t *spec0 = speclist_new(roomspec0);
    speclist_t *spec1 = speclist_new(roomspec1);
    speclist_t *spec2 = speclist_new(roomspec2);
    speclist_t *spec3 = speclist_new(roomspec3);

    speclist_t *spec = NULL;
    DL_APPEND(spec, spec0);
    DL_APPEND(spec, spec1);
    DL_APPEND(spec, spec2);
    DL_APPEND(spec, spec3);

    /* Create levelspec */
    int thresholds[4] = {1, 2, 3, 4};
    levelspec_t *levelspec = levelspec_new(4, thresholds);

    /* Set roomspecs to different difficulty levels */
    add_roomlevel_to_hash(&(levelspec->roomlevels), "level_0_room", 0);
    add_roomlevel_to_hash(&(levelspec->roomlevels), "level_1_room", 1);
    add_roomlevel_to_hash(&(levelspec->roomlevels), "level_2_room", 2);
    add_roomlevel_to_hash(&(levelspec->roomlevels), "level_3_room", 3);

    /* Set directions for room generation */
    char *directions[] = {"NORTH", "SOUTH", "EAST", "WEST"};
    
    /* Generate one room for each level */
    int check = 0;
    gencontext_t *context = gencontext_new(NULL, 1, 0, spec);
    for (int i = 1; i <= 4; i++)
    {
        context->level = i;
        check += multi_room_level_generate(ctx->game, context, "level", 1, levelspec);
    }

    if (check == SUCCESS)
    {
        return "Rooms for difficulty levels 0-3 generated";
    } else
    {
        /* Format the output message */
        static char buffer[OUTPUT_BUFFER_SIZE];
        snprintf(buffer, OUTPUT_BUFFER_SIZE, "%d rooms generated", (4-check));
        return buffer;
    }
}


/* Defines a new CLI operation that triggers recursive generation */
char *recursive_gen(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    /* This operation has to be called with one parameter */
    if(tokens[2] != NULL)
    {
        return "I do not know what you mean.";
    }

    int radius = atoi(tokens[1]);

    /* Create gencontext */
    roomspec_t *roomspec = roomspec_new("simple_room", "A simple room with nothing.", "A simple room with nothing.", NULL);
    speclist_t *spec = speclist_new(roomspec);
    gencontext_t *context = gencontext_new(NULL, 1, 0, spec);

    /* Generate 2 layers of rooms around room1 */
    char *directions[] = {"NORTH", "SOUTH", "EAST", "WEST"};
    int check = recursive_generate(ctx->game, context, ctx->game->curr_room, radius, directions, 4, "");
    
    if (check == SUCCESS)
    {
        /* Format the output message */
        static char buffer[OUTPUT_BUFFER_SIZE];
        snprintf(buffer, OUTPUT_BUFFER_SIZE, "Generated rooms within radius %d", radius);
        return buffer;
    } else
    {
        return "Nothing happened";
    }
}


int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    add_entry("LEVELGEN", level_gen, NULL, ctx->table);
    add_entry("RECURGEN", recursive_gen, NULL, ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
