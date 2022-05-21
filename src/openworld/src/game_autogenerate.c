/* Team RPG-Openworld
*
* Sample-Game-Generation header file
*
* sample_generation.h: This file: function prototypes and purposes from
* the functions defined in chiventure/src/openworld/src/game_autogenerate.c
*
*/

#ifndef INCLUDE_GAME_AUTOGENERATE_H
#define INCLUDE_GAME_AUTOGENERATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common/uthash.h"
#include "game-state/game.h"
#include "gen_structs.h"
#include "default_rooms.h"
#include "autogenerate.h"

#define MAX_RAND_ITEMS (100)

/* random_first_room
* given a specgraph struct, and a game struct, updates the 
* game struct to include a random first room based on the specgraph
*
* parameters:
* - context: A pointer to a gencontext_t (type gencontext_t*). Should not be NULL.
* - game_t* game: a pointer to the game struct that needs to be updated. Should not contain any rooms.
*
* returns:
* SUCCESS - if the game was successfully updated
* FAILURE - if the function failed to update the game struct
*/
roomspec_t* random_first_room(game_t* game, gencontext_t* context){

    if(context==NULL){
        return FAILURE;
    }

    specgraph_t* specgraph=context->specgraph;

    if(specgraph==NULL){
        return FAILURE;
    }

    roomspec_t** roomspecs=specgraph->roomspecs;

    if(roomspecs==NULL){
        return FAILURE;
    }

    int num_roomspecs=specgraph->num_roomspecs;
    int randomint=rand() % num_roomspecs;  
    int count=0;
    roomspec_t *newroomspec;

    newroomspec=roomspecs[randomint];

    room_t *new_room = roomspec_to_room(newroomspec);

    assert(add_room_to_game(game, new_room) == SUCCESS);
        
    return SUCCESS;
}

/* random_room_from_game
* given a game struct, chooses a random room from the game
*
* parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
*
* returns:
* SUCCESS - if a random room was successfully chosen
* FAILURE - if a rnadom room could not be chosen (e.g. if game is null or if game contains no rooms)
*/
/*
roomspec_t* random_first_room(game_t* game){
    if(game==NULL){
        return FAILURE;
    }

    int randomint=rand() % num_roomspecs;  
*/



