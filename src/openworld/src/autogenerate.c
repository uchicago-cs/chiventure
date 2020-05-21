/* Team RPG-Openworld
 * 
 * autogenerate.c: This file. Function definitions of the functions 
 * specified in chiventure/include/autogenerate.h
 * 
 * Room module that autogenerates string of rooms connected via paths when 
 * a "dead-end" room is entered
 * 
 * See chiventure/include/autogenerate.h header file to see function 
 * prototypes and purposes
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../../include/openworld/autogenerate.h"

/* See autogenerate.h */
bool any_paths(room_t *r) {
    assert(r != NULL && "any_paths: Given room is NULL");
    return (r->paths != NULL);
}

/* See autogenerate.h */
room_t* roomspec_to_room(game_t *game, roomspec_t *roomspec) {

    /* CHANGE THIS LATER TO BE UNIQUELY GENERATED TO BE DIFFERENT FROM ROOMS IN game */
    char* room_id = (char*) calloc(3, 1);
    // hi
    room_id[0] = 'h';
    room_id[1] = 'i';
    room_id[2] = '\0';

    room_t *res = room_new(room_id, roomspec->short_desc, roomspec->long_desc);
    res->items = roomspec->items;
    res->paths = roomspec->paths;

    return res;
}

/* See autogenerate.h */
int pop_speclist(gencontext_t *context) {
    assert(context != NULL && "pop_speclist: Given context is NULL");
    assert(context->speclist != NULL && 
    "pop_speclist: Given context's speclist field is NULL");

    speclist_t *prev = context->speclist;
    context->speclist = context->speclist->next; // Doesn't matter if next is NULL

    if (prev->spec->paths == NULL) goto fin;
    else delete_all_paths(prev->spec->paths);
    if (prev->spec->items == NULL) goto fin;
    else delete_all_items(&prev->spec->items);

    fin:
        free(prev->spec->short_desc);
        free(prev->spec->long_desc);
        free(prev->spec);
        free(prev);
    return 0;
}

/* See autogenerate.h */
int room_generate(game_t *game, gencontext_t *context) {
    /* Implement simple single-room autogeneration */
    if (!any_paths(game->curr_room)) {
        speclist_t *prev = context->speclist;
        room_t *newRoom = roomspec_to_room(game, prev->spec);
        assert( 0 == pop_speclist(context));

        // Add addRoom to gameNew
        assert(0 == add_room_to_game(game, newRoom));
        
        // Add path from the current room to addRoom
        path_t* path_to_room = path_new(newRoom, "to new room"); // For now
        assert (0 == add_path_to_room(game->curr_room, path_to_room));

        return 0; /* SUCCESS - room added */
    }

    return 1; /* room not added */
}

/* See autogenerate.h */
int autogen_algorithm(void) { // Save this for eventually adding multiple rooms at once
    /* TODO */

    /* Ideas: We should find a "random" library that pulls randomly from a 
     * given list of items (or structs). We can pull from a hard-coded list 
     * of structs randomly, only when desired. Should have a function that 
     * uses this random library to randomly pull from a given list/database/
     * hashtable (up for discussion) when the user chooses to. Does nothing 
     * when a new room is not desired */

    return 1; // Depends algorithm module to be created
}