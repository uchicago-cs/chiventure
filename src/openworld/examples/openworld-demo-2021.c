/*
Main CMAKE file lines 14-15:

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)

/*
Openworld 2021 demo makefile

set(OPENWORLD_EXAMPLES openworld-demo-2022)

add_executable(openworld-demo-2022
               openworld-demo-2022.c)

# Link with chiventure libraries
foreach(example ${OPENWORLD_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(openworld-examples
        DEPENDS ${OPENWORLD_EXAMPLES})
*/        


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
/*
#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "openworld/autogenerate.h"
#include "game-state/path.h"


#define OUTPUT_BUFFER_SIZE 100


const char *banner = "THIS IS AN OPENWORLD EXAMPLE PROGRAM";


/* ==== Placeholder sample struct variables ====
These will be initialized in initialize_sample_structs().
IMPORTANT: 
In full integration, these structs must be added to the ctx.
It is advisable to refactor all autogeneration-associated structs into gencontext before doing so. */

/* ROOMSPECS
   Pre-declaring roomspecs like this is important as we need to preserve 
   num_built between function calls in order to generate unique rooms. */
/*roomspec_t *rspec_lvl0 = NULL;
roomspec_t *rspec_lvl1 = NULL;
roomspec_t *rspec_lvl2 = NULL;
roomspec_t *rspec_lvl3 = NULL;

// SPECLIST 
speclist_t *speclist = NULL;

// GENCONTEXT 
gencontext_t *context = NULL;

// LEVELSPEC 
levelspec_t *levelspec = NULL;



/* ==== Functions ==== */

/* Initializes the sample, "in-memory", gencontext and other component structs. 
   Uses placeholder variables declared above. */
/*void initialize_sample_structs()
{
    // Initialize roomspecs 
    rspec_lvl0 = roomspec_new("level 0 room #", "A level 0 room.", "A room of difficulty level 0.", NULL);
    rspec_lvl1 = roomspec_new("level 1 room #", "A level 1 room.", "A room of difficulty level 1.", NULL);
    rspec_lvl2 = roomspec_new("level 2 room #", "A level 2 room.", "A room of difficulty level 2.", NULL);
    rspec_lvl3 = roomspec_new("level 3 room #", "A level 3 room.", "A room of difficulty level 3.", NULL);

    // Initialize speclist (nodes and final list) 
    speclist_t *specnode0 = speclist_new(rspec_lvl0);
    speclist_t *specnode1 = speclist_new(rspec_lvl1);
    speclist_t *specnode2 = speclist_new(rspec_lvl2);
    speclist_t *specnode3 = speclist_new(rspec_lvl3);
    DL_APPEND(speclist, specnode0);
    DL_APPEND(speclist, specnode1);
    DL_APPEND(speclist, specnode2);
    DL_APPEND(speclist, specnode3);

    // Initialize gencontext 
    context = gencontext_new(NULL, 0, 0, speclist);

    // Initialize levelspec 
    int thresholds[4] = {0, 10, 20, 30};
    levelspec = levelspec_new(4, thresholds);
    add_roomlevel_to_hash(&(levelspec->roomlevels), "level 0 room #", 0);
    add_roomlevel_to_hash(&(levelspec->roomlevels), "level 1 room #", 1);
    add_roomlevel_to_hash(&(levelspec->roomlevels), "level 2 room #", 2);
    add_roomlevel_to_hash(&(levelspec->roomlevels), "level 3 room #", 3); 
}

// Creates a sample in-memory game 
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");

    load_normal_mode(game);
    
    /* Create room1, the initial room */
//  room_t *room1 = room_new("room1", "This is room 1", "This is the first room.");
//  add_room_to_game(game, room1);
//  game->curr_room = room1;

    /* Create context */
//  chiventure_ctx_t *ctx = chiventure_ctx_new(game);

//  return ctx;
//}

/* Defines a new CLI operation that:
   - Deletes/frees all rooms in hash except for the original room "room1"
   - Reset all roomspecs' num_built fields to 0 */
/*char *nuke(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    // This operation has to be called without a parameter 
    if(tokens[1] != NULL) {
        return "Please speak english! So uncivilized...";
    }
    
    // Original room "room1" 
    room_t *orig_room;
    HASH_FIND_STR(ctx->game->all_rooms, "room1", orig_room);
    assert(orig_room);

    // Remove paths from original room. 
    delete_all_paths(orig_room->paths); 
    orig_room->paths = NULL;

    // Temporarily remove original room from hash. 
    HASH_DEL(ctx->game->all_rooms, orig_room);

    // Delete and free all other rooms in hash. */
 /* delete_all_rooms(&(ctx->game->all_rooms));

    // Reinsert original room into hash. 
    add_room_to_game(ctx->game, orig_room);
    ctx->game->curr_room = orig_room;
    
    speclist_t *curr_node, *tmp_node;
    DL_FOREACH_SAFE(context->speclist, curr_node, tmp_node) {
        curr_node->spec->num_built = 0;
    }

    int count = HASH_COUNT(ctx->game->all_rooms);
    static char buffer[OUTPUT_BUFFER_SIZE];
    snprintf(buffer, OUTPUT_BUFFER_SIZE, "Nuked game. Game now has %d room.", count);
    return buffer;
}

// Defines a new CLI operation that: 
   Outputs current player level and room difficulty level. 
char *level_check(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    if (tokens[1] != NULL) {
        return "Please speak english! So uncivilized...";
    }

    int diff_level = map_level_to_difficulty(4, levelspec->thresholds, context->level);
    
    static char buffer[OUTPUT_BUFFER_SIZE];
    snprintf(buffer, OUTPUT_BUFFER_SIZE, "Player level is %d; you will face level %d rooms.", context->level, diff_level);
    return buffer;
}

/* Defines a new CLI operation that:
   Updates player level (in gencontext) to given integer 
char *level_new(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    if(tokens[2] != NULL) {
        return "Please speak english! So uncivilized...";
    }

    if (tokens[1] == NULL) {
        return "Please specify new level.";
    }

    int new_level = atoi(tokens[1]);
    int prev_level = context->level;
    context->level = new_level;

    int change = new_level - prev_level;
    static char buffer[OUTPUT_BUFFER_SIZE];
    if (change == 0) {
        snprintf(buffer, OUTPUT_BUFFER_SIZE, "Player level unchanged at %d.", new_level);
        return buffer;
    } else if (change > 0) {
        snprintf(buffer, OUTPUT_BUFFER_SIZE, "Player level increased to %d from %d.", new_level, prev_level);
        return buffer;
    } else {
        snprintf(buffer, OUTPUT_BUFFER_SIZE, "Player level decreased to %d from %d.", new_level, prev_level);
        return buffer;   
    }
}

/* Defines a new CLI operation that:
   Triggers level-oriented generation of given number of rooms (second token is interpreted as num_rooms)
   Uses current (player) level value in gencontext. 
char *level_gen(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{   
    if(tokens[2] != NULL) {
        return "Please speak english! So uncivilized...";
    }

    if (tokens[1] == NULL) {
        return "Please specify number of rooms to generate.";
    }
    int num_rooms = atoi(tokens[1]);

    /* Set directions for room generation 
    char *directions[] = {"north", "south", "east", "west"};
    
    /* Generate specified number of rooms for each level 
    int initial_count = HASH_COUNT(ctx->game->all_rooms);
    int check = multi_room_level_generate(ctx->game, context, "", num_rooms, levelspec);
    int final_count = HASH_COUNT(ctx->game->all_rooms);

    int difficulty_level = map_level_to_difficulty(4, levelspec->thresholds, context->level);

    static char buffer[OUTPUT_BUFFER_SIZE];
    if (check == SUCCESS) {
        snprintf(buffer, OUTPUT_BUFFER_SIZE,  "Generated %d lvl %d rooms. Game now has %d rooms.", 
                 final_count - initial_count, difficulty_level, final_count);
        return buffer;
    } else {
        /* Format the output message 
        snprintf(buffer, OUTPUT_BUFFER_SIZE, "[FAILURE] Generated only %d lvl %d rooms. Game now has %d rooms.", 
                 final_count - initial_count, difficulty_level, final_count);
        return buffer;
    }
}


// Defines a new CLI operation that:
// Triggers recursive generation within the given radius (second token is interpreted as the integer radius) 
char *recursive_gen(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    /* This operation has to be called with one parameter 
    if (tokens[2] != NULL) {
        return "Please speak english! So uncivilized...";
    }

    if (tokens[1] == NULL) {
        return "Please specify the generation radius.";
    }

    int radius = atoi(tokens[1]);

    /* Generate layers of rooms around room1 
    char *directions[] = {"north", "south", "east", "west"};
    int check = recursive_generate(ctx->game, context, ctx->game->curr_room, radius, directions, 4, "");
    
    if (check == SUCCESS) {
        /* Format the output message 
        static char buffer[OUTPUT_BUFFER_SIZE];
        int count = HASH_COUNT(ctx->game->all_rooms);
        snprintf(buffer, OUTPUT_BUFFER_SIZE, "Generated within radius %d. Game now has %d rooms.", radius, count);
        return buffer;
    } else {
        return "Nothing happened";
    }
}

// Defines a new CLI operation that:
   Counts the number of rooms in the game. The output is in the form of a {} array, 
   where each index corresponds to the difficulty level of the roomspec and each
   value indicates the number of rooms. 
char *count_rooms(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    if (tokens[1] != NULL) {
        return "Please speak english! So uncivilized...";
    }
    
    roomspec_t *rspecs[] = {rspec_lvl0, rspec_lvl1, rspec_lvl2, rspec_lvl3};
    int count[] = {0, 0, 0, 0};
    int total = 0;

    room_t *curr, *tmp;
    HASH_ITER(hh, ctx->game->all_rooms, curr, tmp) {
        int i = curr->room_id[6] - '0';
        count[i]++;
        total++;
    }
    static char buffer[OUTPUT_BUFFER_SIZE];
    snprintf(buffer, OUTPUT_BUFFER_SIZE, "total: %d || per level: {%d, %d, %d, %d} + 1 (room1)", total, count[0], count[1], count[2], count[3]);
    return buffer;
}


int main(int argc, char **argv)
{   
    initialize_sample_structs();      
    
    chiventure_ctx_t *ctx = create_sample_ctx();

    add_entry("LEVELGEN", level_gen, NULL, ctx->cli_ctx->table);
    add_entry("RECURGEN", recursive_gen, NULL, ctx->cli_ctx->table);
    add_entry("LEVELNEW", level_new, NULL, ctx->cli_ctx->table);
    add_entry("NUKE", nuke, NULL, ctx->cli_ctx->table);
    add_entry("LEVELCHECK", level_check, NULL, ctx->cli_ctx->table);
    add_entry("COUNT", count_rooms, NULL, ctx->cli_ctx->table);

    // Start chiventure 
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}*/


