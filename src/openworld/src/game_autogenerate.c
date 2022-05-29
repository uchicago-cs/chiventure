/* Team RPG-Openworld
*
* Sample-Game-Generation header file
*
* sample_generation.h: This file: function prototypes and purposes from
* the functions defined in chiventure/src/openworld/src/game_autogenerate.c
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common/utlist.h"
#include "common/uthash.h"
#include "game-state/room.h"
#include "game-state/game.h"
#include "openworld/gen_structs.h"
#include "openworld/default_rooms.h"
#include "openworld/autogenerate.h"
#include "openworld/game_autogenerate.h"

#define MAX_RAND_ITEMS (100)

/*See autogenerate.h*/
int random_first_room(game_t* game, specgraph_t *specgraph){

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
    roomspec_t *newroomspec=(roomspec_t*)malloc(sizeof(roomspec_t));

    newroomspec=roomspecs[randomint];
    int tag=newroomspec->tag;

    coords_t *coords=coords_new(0,0);
    room_t *new_room = roomspec_to_room(newroomspec, coords);

    assert(add_room_to_game(game, new_room) == SUCCESS);

    free(new_room);

    return SUCCESS;
}

/*See autogenerate.h*/
room_t* random_room_from_game(game_t* game){

    int num_rooms=HASH_COUNT(game->all_rooms);

    int randomint=rand() % num_rooms; 

    int count=0;

    char** keys=(char**)malloc(sizeof(char*)*num_rooms);

    //room_t** rooms=(room_t**)malloc(num_rooms*sizeof(room_t*));

    room_hash_t *curr, *tmp;
    char* curr_id;

    HASH_ITER(hh, game->all_rooms, curr, tmp) {

        curr_id=curr->room_id;

        keys[count]=(char*)malloc(strlen(curr_id)+1);
        count++;
    }

    char* room_id=keys[randomint];

    char* random_id=(char*)malloc(strlen(room_id)+1);
    random_id=room_id;
    
    //room_t* random_room=(room_t*)malloc(sizeof(room_t));
    room_t* random_room=find_room_from_game(game, random_id);

    for(int i=0; i<num_rooms; i++){
        free(keys[i]);
    }

    free(keys);

    return random_room;
} 

/*
* path_generate
* Automatically determines whether to generate a path between a given room and an adjacent room
* The probability that a path is generated is determined based on the adjacency matrix
*
* parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
* - specgraph: A pointer to a specgraph_t. Should not be NULL.
* - curr: A pointer to the room_t from which the algorithm will determine whether to generate paths to adjacent rooms
* - adjacentroom: A pointer to the adjacent room we are considering making paths to
*
* returns:
* true - if a path should be created
* false - if a path should not be created
*/

bool path_generate(game_t* game, specgraph_t *specgraph, room_t* curr, room_t* adjacentroom){

    int num_roomspecs=specgraph->num_roomspecs;  
    roomspec_t **roomspecs=(roomspec_t**)malloc(num_roomspecs*sizeof(roomspec_t*));
    roomspecs=specgraph->roomspecs;

    roomspec_t *currspec=(roomspec_t*)malloc(sizeof(roomspec_t));
    roomspec_t *adjacentspec=(roomspec_t*)malloc(sizeof(roomspec_t));    
    currspec=roomspecs[curr->tag];    
    adjacentspec=roomspecs[adjacentroom->tag];

    int correlation=roomspec_correlation(specgraph, currspec, adjacentspec);

    int randomint=rand() % 5;

    if(randomint<correlation){
        free(roomspecs);
        free(currspec);
        free(adjacentspec);
        return true;
    }

    free(roomspecs);
    free(currspec);
    free(adjacentspec);
    return false;
}


/*
* path_autogenerate
* Automatically determines whether to generate a path between a given room and all adjacent rooms in a game
* The probability that a path is generated is determined based on the adjacency matrix
*
* parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
* - specgraph: A pointer to a specgraph_t. Should not be NULL.
* - curr: A pointer to the room_t from which the algorithm will determine whether to generate paths to adjacent rooms
*
* returns:
* SUCCESS - if the algorithm ran successfully
* FAILURE - if the algorithm did not run successfully (e.g. if the game, specgraph, or room are invalid)
*/

int path_autogenerate(game_t* game, specgraph_t *specgraph, room_t* curr){

    int num_roomspecs=specgraph->num_roomspecs;  
    roomspec_t **roomspecs=(roomspec_t**)malloc(num_roomspecs*sizeof(roomspec_t*));
    roomspecs=specgraph->roomspecs;

    roomspec_t *currspec=(roomspec_t*)malloc(sizeof(roomspec_t));
    currspec=roomspecs[curr->tag];

    coords_t *coords=find_coords_of_room(curr);
    int x=coords->x;
    int y=coords->y;

    room_t *adjacentroom;

    path_t *pathtocurr;
    path_t *pathtoadjacent;

    if(room_exists_in_direction(game, curr, "north")){
        adjacentroom=find_room_in_direction(game, curr, "north");
        if(path_generate(game, specgraph, curr, adjacentroom)){
            pathtoadjacent=path_new(adjacentroom, "north");
            add_path_to_room(adjacentroom, pathtoadjacent);
        }

        if(path_generate(game, specgraph, curr, adjacentroom)){
            pathtocurr=path_new(curr, "south");
            add_path_to_room(curr, pathtocurr);            
        }
    }

    if(room_exists_in_direction(game, curr, "south")){
        adjacentroom=find_room_in_direction(game, curr, "south");
        if(path_generate(game, specgraph, curr, adjacentroom)){
            pathtoadjacent=path_new(adjacentroom, "south");
            add_path_to_room(adjacentroom, pathtoadjacent);
        }

        if(path_generate(game, specgraph, curr, adjacentroom)){
            pathtocurr=path_new(curr, "north");
            add_path_to_room(curr, pathtocurr);            
        }
    }

    if(room_exists_in_direction(game, curr, "east")){
        adjacentroom=find_room_in_direction(game, curr, "east");
        if(path_generate(game, specgraph, curr, adjacentroom)){
            pathtoadjacent=path_new(adjacentroom, "east");
            add_path_to_room(adjacentroom, pathtoadjacent);
        }

        if(path_generate(game, specgraph, curr, adjacentroom)){
            pathtocurr=path_new(curr, "west");
            add_path_to_room(curr, pathtocurr);            
        }
    }

    if(room_exists_in_direction(game, curr, "west")){
        adjacentroom=find_room_in_direction(game, curr, "west");
        if(path_generate(game, specgraph, curr, adjacentroom)){
            pathtoadjacent=path_new(adjacentroom, "west");
            add_path_to_room(adjacentroom, pathtoadjacent);
        }

        if(path_generate(game, specgraph, curr, adjacentroom)){
            pathtocurr=path_new(curr, "east");
            add_path_to_room(curr, pathtocurr);            
        }
    }

    free(currspec);
    free(roomspecs);
    return SUCCESS;
}

/*See autogenerate.h*/
int autogenerate_room_in_game(game_t* game, specgraph_t *specgraph){

    int num_roomspecs=specgraph->num_roomspecs;

    roomspec_t **roomspecs=(roomspec_t**)malloc(num_roomspecs*sizeof(roomspec_t));
    roomspecs=specgraph->roomspecs;

    if(game==NULL){
        return -1;
    }

    if(specgraph==NULL){
        return -1;
    }

    room_t* curr=random_room_from_game(game);

    char* direction_to_new;
    char* direction_to_curr;  

    int rc=pick_random_direction(game, curr, direction_to_curr, direction_to_new);

    if(rc==FAILURE){
        free(roomspecs);
        return 0;
    }
 
    room_autogenerate(game, specgraph, curr, 
                      direction_to_curr, direction_to_new);
    return 1;    
    path_autogenerate(game, specgraph, curr);

    free(roomspecs);

    return 1;
}

/*See autogenerate.h*/

int game_autogenerate_static(game_t* g, specgraph_t *specgraph, int num_rooms, char* first_room){
    
    int num_roomspecs=specgraph->num_roomspecs;

    roomspec_t **roomspecs=(roomspec_t**)malloc(num_roomspecs*sizeof(roomspec_t));
    roomspecs=specgraph->roomspecs;

    roomspec_t *currspec=(roomspec_t*)malloc(sizeof(roomspec_t));
    char* specname;
    coords_t *coords=coords_new(0,0);

    //Generate first room
    if(strcmp(first_room, "pickrandomly")==0){
        random_first_room(g, specgraph);
    }

    else{
        for(int i=0; i<num_roomspecs; i++){

            currspec=roomspecs[i];
            specname=currspec->room_name;
            if(strcmp(first_room, specname)==0){
                room_t* firstroom=roomspec_to_room(currspec, coords);
                add_room_to_game(g, firstroom);
            }
        }
    }

    //Keep generating until we have enough rooms
    int count=0;
    int rc;

    while(count<num_rooms){
        rc=0;
        while(rc==0){
            rc=autogenerate_room_in_game(g, specgraph);
            if(rc==-1){
                fprintf(stderr, "Invalid input parameters");
            }
        }
        count++;
    }

    return SUCCESS;
}
