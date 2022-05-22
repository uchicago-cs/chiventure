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
#include "game-state/room.h"
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
* given a game struct and a gencontext struct, autogenerates a new room in the game 
* by choosing a random room and direction and creating the new room based on the adjacency matrix.
* parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
*
* returns:
* SUCCESS - if a random room was successfully chosen
* FAILURE - if a random room could not be chosen (e.g. if game is null or if game contains no rooms)
*/

roomspec_t* random_room_from_game(game_t* game){
    if(game==NULL){
        return FAILURE;
    }

    room_hash_t *rooms=game->all_rooms;
    int num_rooms=HASH_COUNT(rooms);

    int randomint=rand() % num_rooms; 

    int count=0;
    room_t* random_room;

    room_hash_t *current, *tmp;
    HASH_ITER(hh, game->all_rooms, current, tmp) {

        if(count==randomint){
            random_room=current;
            return random_room;
        }
        i++;
    }
} 



/* autogenerate_room_in_game
* given a game struct, chooses a random room from the game
*
* parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
* - context: A pointer to a gencontext_t (type gencontext_t*). Should not be NULL.
* returns:
* SUCCESS - if a random room was successfully generated
* FAILURE - if a random room could not be generate 
* (e.g. if game is null, if game contains no rooms, or the chosen room has no empty directions)
*/

int autogenerate_room_in_game(game_t* game, gencontext_t* context){
    if(game==NULL){
        return FAILURE;
    }

    if(context==NULL){
        return FAILURE;
    }

    room_t* curr=random_room_from_game(game);
    char* direction_to_new=pick_random_direction(game, curr);
    char*direction_to_curr;

    if((strcmp(direction_to_new), "north")==0){
        direction_to_curr="south";
    }

    else if((strcmp(direction_to_new), "south")==0){
        direction_to_curr="north";
    }

    else if((strcmp(direction_to_new), "east")==0){
        direction_to_curr="west";
    }

    else if((strcmp(direction_to_new), "west")==0){
        direction_to_curr="east";
    }

    specgraph=context->specgraph;
    roomspec_t **roomspecs=specgraph->roomspecs;
    roomspec_t *currroomspec=roomspecs[curr->tag];

    int rc=room_autogenerate(game, context, curr, currroomspec, 
                      direction_to_curr, direction_to_new);
    
    return rc;
}

/*
* path_generate
* Automatically determines whether to generate a path between a given room and an adjacent room
* The probability that a path is generated is determined based on the adjacency matrix
*
* parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
* - context: A pointer to a gencontext_t (type gencontext_t*). Should not be NULL.
* - curr: A pointer to the room_t from which the algorithm will determine whether to generate paths to adjacent rooms
* - adjacentroom: A pointer to the adjacent room we are considering making paths to
*
* returns:
* true - if a path should be created
* false - if a path should not be created
*/

bool path_generate(game_t* game, gencontext_t* context, room_t* curr, room_t* adjacentroom){

    specgraph_t *specgraph=context->specgraph;
    roomspec_t **roomspecs=specgraph->roomspecs;

    roomspec_t *currspec=roomspecs[curr->tag];
    roomspec_t *adjacentspec=roomspecs[adjacent->tag];

    int correlation=roomspec_correlation(specgraph, currspec, adjacentspec);

    int randomint=rand() % 5;

    if(randomint<correlation){
        return true;
    }

    return false;
}


/*
* path_autogenerate
* Automatically determines whether to generate a path between a given room and all adjacent rooms in a game
* The probability that a path is generated is determined based on the adjacency matrix
*
* parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
* - context: A pointer to a gencontext_t (type gencontext_t*). Should not be NULL.
* - curr: A pointer to the room_t from which the algorithm will determine whether to generate paths to adjacent rooms
*
* returns:
* SUCCESS - if the algorithm ran successfully
* FAILURE - if the algorithm did not run successfully (e.g. if the game, context, or room are invalid)
*/

int path_autogenerate(game_t* game, gencontext_t* context, room_t* curr){
    
    specgraph_t *specgraph=context->specgraph;
    roomspec_t **roomspecs=specgraph->roomspecs;

    roomspec_t *currspec=roomspecs[curr->tag];

    coords_t *coords=find_coords_of_room(curr);
    int x=coords->x;
    int y=coords->y;

    room_t *adjacentroom;

    path_t *pathtocurr;
    path_t *pathtoadjacent

    if(room_exists_in_direction(curr, "north")){
        adjacentroom=find_room_in_direction(game, curr, "north");
        if(path_generate(specgraph, curr, adjacent)){
            pathtoadjacent=path_new(adjacentroom, "north");
            add_path_to_room(adjacentroom, pathtoadjacent);
        }

        if(path_generate(specgraph, adjacent, curr)){
            pathtocurr=path_new(curr, "south");
            add_path_to_room(curr, pathtocurr);            
        }
    }

    if(room_exists_in_direction(curr, "south")){
        adjacentroom=find_room_in_direction(game, curr, "south");
        if(path_generate(specgraph, curr, adjacent)){
            pathtoadjacent=path_new(adjacentroom, "south");
            add_path_to_room(adjacentroom, pathtoadjacent);
        }

        if(path_generate(specgraph, adjacent, curr)){
            pathtocurr=path_new(curr, "north");
            add_path_to_room(curr, pathtocurr);            
        }
    }

    if(room_exists_in_direction(curr, "east")){
        adjacentroom=find_room_in_direction(game, curr, "east");
        if(path_generate(specgraph, curr, adjacent)){
            pathtoadjacent=path_new(adjacentroom, "east");
            add_path_to_room(adjacentroom, pathtoadjacent);
        }

        if(path_generate(specgraph, adjacent, curr)){
            pathtocurr=path_new(curr, "west");
            add_path_to_room(curr, pathtocurr);            
        }
    }

    if(room_exists_in_direction(curr, "west")){
        adjacentroom=find_room_in_direction(game, curr, "west");
        if(path_generate(specgraph, curr, adjacent)){
            pathtoadjacent=path_new(adjacentroom, "west");
            add_path_to_room(adjacentroom, pathtoadjacent);
        }

        if(path_generate(specgraph, adjacent, curr)){
            pathtocurr=path_new(curr, "east");
            add_path_to_room(curr, pathtocurr);            
        }
    }
}
