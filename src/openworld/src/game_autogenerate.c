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
#include "openworld/game_autogenerate.h"
#include "openworld/autogenerate.h"
#include "openworld/gen_structs.h"
#include "openworld/default_rooms.h"

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
    roomspec_t *newroomspec;

    newroomspec=roomspecs[randomint];
    int tag=newroomspec->tag;

    coords_t *coords=coords_new(0,0);
    room_t *new_room = roomspec_to_room(newroomspec, coords);
    new_room->tag=tag;

    assert(add_room_to_game(game, new_room) == SUCCESS);
        
    return SUCCESS;
}

/* random_room_from_game
* given a game struct, randomly picks a new room from the game 
* parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
*
* returns:
* random_room: A pointer to the randomly chosen room
*/

room_t* random_room_from_game(game_t* game){

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
    }
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

bool path_generate(game_t* game, specgraph_t *specgraph, room_t* curr, room_t* adjacentroom){

    roomspec_t **roomspecs=specgraph->roomspecs;

    roomspec_t *currspec=roomspecs[curr->tag];
    roomspec_t *adjacentspec=roomspecs[adjacentroom->tag];

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

int path_autogenerate(game_t* game, specgraph_t *specgraph, room_t* curr){
    
    roomspec_t **roomspecs=specgraph->roomspecs;

    roomspec_t *currspec=roomspecs[curr->tag];

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
}

/* autogenerate_room_in_game
* given a game struct and gencontext struct, generates a random room in the game by 
* choosing a random room with random_room_in_game and generating a room from that room
* using the adjacency matrix. ALso generates any new associated paths using 
* path_autogenerate
*
* parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
* - context: A pointer to a gencontext_t (type gencontext_t*). Should not be NULL.
* returns:
* 1 - if a random room was successfully generated
* 0 - if a random room could not be generated due to having no empty directions
* -1 - if a random room could not be generate due to invalid inputs 
* (e.g. if game is null, if game contains no rooms, etc.)
*/

int autogenerate_room_in_game(game_t* game, specgraph_t *specgraph){

    roomspec_t **roomspecs=specgraph->roomspecs;

    if(game==NULL){
        return -1;
    }

    if(specgraph==NULL){
        return -1;
    }

    room_t* curr=random_room_from_game(game);
    roomspec_t *currroomspec=roomspecs[curr->tag];

    char* direction_to_new;
    char* direction_to_curr;
    int rc=pick_random_direction(game, curr, direction_to_curr, direction_to_new);
    
    if(rc==FAILURE){
        return 0;
    }
    coords_t *coords=curr->coords;
    int x=coords->x;
    int y=coords->y;

    if(strcmp(direction_to_new, "north")==0){
        direction_to_curr="south";
        y+=1;
    }

    else if(strcmp(direction_to_new, "south")==0){
        direction_to_curr="north";
        y-=1;
    }

    else if(strcmp(direction_to_new, "east")==0){
        direction_to_curr="west";
        x+=1;
    }

    else if(strcmp(direction_to_new, "west")==0){
        direction_to_curr="east";
        x-=1;
    }
    coords_t *newcoords=coords_new(x, y);

    room_autogenerate(game, specgraph, curr, currroomspec, 
                      direction_to_curr, direction_to_new);
    
    path_autogenerate(game, specgraph, curr);

    return 1;
}

/*See autogenerate.h*/

int game_autogenerate_static(game_t* g, specgraph_t *specgraph, int num_rooms, char* first_room){
    
    int num_roomspecs=specgraph->num_roomspecs;
    roomspec_t **roomspecs=specgraph->roomspecs;
    int **edges=specgraph->edges;

    roomspec_t *currspec;
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
