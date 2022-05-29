#define NUM_COMPASS_DIRECTIONS 4
#define NUM_DIRECTIONS 6
#define MAX_DIRECTION_STRLEN 6


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
#include "common/utlist.h"
#include "common/uthash.h"
#include "game-state/room.h"
#include "openworld/autogenerate.h"
#include "openworld/gen_structs.h"
#include "openworld/default_rooms.h"


/* See autogenerate.h */
bool path_exists_in_direction(room_t *r, char *direction)
{
    /* No paths case */
    if (r->paths == NULL) {
        return false;
    }

    path_hash_t *current, *tmp;
    HASH_ITER(hh, r->paths, current, tmp) {
        /* If the path has the given direction, return true */
        if (strcmp(current->direction, direction) == 0) {
            return true;
        }
    }
    return false;
}

/* See autogenerate.h */
bool room_exists_in_direction(game_t* game, room_t *r, char *direction)
{
    /*Find coordinates of current room*/
    int x=r->coords->x;
    int y=r->coords->y;

    if (strcmp("north", direction) == 0){
        y+=1;
    }

    else if (strcmp("south", direction) == 0){
        y-=1;
    }

    else if (strcmp("east", direction) == 0){
        x+=1;
    }

    else if (strcmp("west", direction) == 0){
        x-=1;
    }

    /*Determine whether there is a room in the given direction*/
    room_hash_t *current, *tmp;
    int currx;
    int curry;

    HASH_ITER(hh, game->all_rooms, current, tmp) {
        /* If the room is adjacent to the current room and in the correct direction, return true */

        currx=current->coords->x;
        curry=current->coords->y;

        if(currx==x && curry==y){
            return true;
        }
    }
    return false;
}

room_t* find_room_in_direction(game_t* game, room_t *r, char *direction)
{
    /*Find coordinates of current room*/
    coords_t *coords=r->coords;
    int x=coords->x;
    int y=coords->y;

    room_t* adjacentroom=(room_t*)malloc(sizeof(room_t));

    if (strcmp("north", direction) == 0){
        y+=1;
    }

    else if (strcmp("south", direction) == 0){
        y-=1;
    }

    else if (strcmp("east", direction) == 0){
        x+=1;
    }

    else if (strcmp("west", direction) == 0){
        x-=1;
    }

    /*Determine whether there is a room in the given direction*/
    room_hash_t *current, *tmp;
    HASH_ITER(hh, game->all_rooms, current, tmp) {
        /* If the room is adjacent to the current room and in the correct direction, return a pointer to it */

        coords_t *coords=current->coords;
        int currx=coords->x;
        int curry=coords->y;

        if(currx==x && curry==y){
            adjacentroom=current;
            return adjacentroom;
        }
    }
    free(adjacentroom);
    fprintf(stderr, "A room does not exist in the given direction. Use exists_room_in_direction first to confirm a room in the given direction exists");
    exit(1);
}

/* See autogenerate.h */
room_t* roomspec_to_room(roomspec_t *roomspec, coords_t* coords)
{
    /* moved- generate the unique room id here and pass it to the room; don't mess with the roomspec */
    char buff[MAX_SDESC_LEN + 1] = { 0 }; // Will hold unique room_id
    snprintf(buff, MAX_SDESC_LEN, "%s%d", roomspec->room_name, roomspec->num_built);
    roomspec->num_built++;

    /* we use buff for the room name instead */
    room_t *res = room_new(buff, roomspec->short_desc, roomspec->long_desc);
    
    /* instead of taking all the items, just take a few of them */
    res->items = generate_items(roomspec);

    /* tag to show roomspec position in roomspec list in specgraph */
    res->tag = roomspec->tag;

    res->paths = NULL;
    res->coords=coords;
    res->tag= roomspec->tag;
    return res;
}

/* See autogenerate.h */ 
int pick_random_direction(game_t *game, room_t *curr, char *out_direction_to_curr, char *out_direction_to_new)
{
    /* 2D array of possible directions */
    char** directions=(char**)malloc(NUM_COMPASS_DIRECTIONS*sizeof(char*));
 
    directions[0]=malloc(6);
    directions[1]=malloc(5);
    directions[2]=malloc(6);
    directions[3]=malloc(5);    

    strcpy(directions[0], "north");
    strcpy(directions[1], "east");
    strcpy(directions[2], "south");
    strcpy(directions[3], "west");

    /* Random initial direction */
    unsigned int initial_direction = rand() % NUM_COMPASS_DIRECTIONS;

    /* Bump directions index by 1 if a path with that direction already exists */
    unsigned int bump;
 
    for (bump = 0; bump < NUM_COMPASS_DIRECTIONS; bump++) {
        /* Forwards direction + bump */
        unsigned int forwards = (initial_direction + bump) % NUM_COMPASS_DIRECTIONS;
        /* If path in that direction exists in curr, bump. Else, create the path */
        if (room_exists_in_direction(game, curr, directions[forwards])) {
            /* Bump if the room already has a path in the given direction */
            continue;
        }
        unsigned int backwards = (forwards + 2) % NUM_COMPASS_DIRECTIONS;

        if(strlen(directions[backwards])==5){

            out_direction_to_new=(char*)malloc(6);
            out_direction_to_curr=(char*)malloc(6);            
            strcpy(out_direction_to_curr, directions[backwards]);
            strcpy(out_direction_to_new, directions[forwards]);
        }

        if(strlen(directions[backwards])==4){

            out_direction_to_new=(char*)malloc(5);
            out_direction_to_curr=(char*)malloc(5);            
            strcpy(out_direction_to_curr, directions[backwards]);
            strcpy(out_direction_to_new, directions[forwards]);
        }

        for(int i=0; i<NUM_COMPASS_DIRECTIONS; i++){
            free(directions[i]);
        }
        free(directions);

        return SUCCESS; // direction was picked
    }

    for(int i=0; i<NUM_COMPASS_DIRECTIONS; i++){
        free(directions[i]);
    }
    free(directions);

    return FAILURE; // no open direction
}

/* See autogenerate.h */
int room_generate(game_t *game, room_t *curr, roomspec_t *rspec_new,
                  char *direction_to_curr, char *direction_to_new)
{
    /* Find coords of new room */
    int x=curr->coords->x;
    int y=curr->coords->y;

    if (strcmp("north", direction_to_new) == 0){
        y+=1;
    }

    else if (strcmp("south", direction_to_new) == 0){
        y-=1;
    }

    else if (strcmp("east", direction_to_new) == 0){
        x+=1;
    }

    else if (strcmp("west", direction_to_new) == 0){
        x-=1;
    }

    coords_t *coords=coords_new(x, y);    

    /* create new combination of rooms/items from randomly picked roomspec
    Adds one generated room from the head of specgraph only */
    room_t *new_room = roomspec_to_room(rspec_new, coords);
    assert(add_room_to_game(game, new_room) == SUCCESS);

    free(coords);
    return SUCCESS;
}

/* See autogenerate.h */
roomspec_t* roomspec_autogenerate(specgraph_t *specgraph, int tag){

    int num_roomspecs=specgraph->num_roomspecs;
    roomspec_t **roomspecs=specgraph->roomspecs;
    int **edges=specgraph->edges;

    int rowcount=0;

    int *row=edges[tag];
    int count=0;
    int sum;

    for(int count=0; count<num_roomspecs; count++){
        sum+=row[count];
    }
 
    int randomint=rand() % sum;  
    count=0;
    roomspec_t *newroomspec=(roomspec_t*)malloc(sizeof(roomspec_t));

    while(randomint>=0){
        if(randomint<row[count])
            newroomspec=roomspecs[count];
        randomint-=row[count];
        count++;
    }
        
    return newroomspec;
}


/* See autogenerate.h */
int room_autogenerate(game_t *game, specgraph_t *specgraph, room_t *curr,
                      char *direction_to_curr, char *direction_to_new){

    int currtag=curr->tag;
    roomspec_t *newroomspec=roomspec_autogenerate(specgraph, currtag);    
    assert(room_generate(game, curr, newroomspec, direction_to_curr, direction_to_new)==SUCCESS);

    return SUCCESS;
}

/* See autogenerate.h */
roomspec_t *random_room_lookup(specgraph_t *specgraph)
{
    roomspec_t **roomspecs=specgraph->roomspecs;
    int num_rooms=specgraph->num_roomspecs;
    int count;
    int idx = rand() % num_rooms, i = 0;

    for(int i=0; i<num_rooms; i++){
        if(i == idx){
            return roomspecs[i];
        }
    }

    return NULL;
}

/* See autogenerate.h */
item_hash_t *random_items(roomspec_t *room)
{
    if (room == NULL) {
        return NULL;
    }

    int count = HASH_COUNT(room->items);
    if (count == 0) {
        return NULL; // otherwise we have a zero division error
    }

    int num_items = rand() % MAX_RAND_ITEMS;
    int num_iters = rand() % count;

    item_hash_t *items = NULL;
    for (int i = 0; i < num_items; i++) {
        int rc = random_item_lookup(&items, room->items, num_iters);
    }
    /* note that items could be NULL */
    return items;
}

/* See autogenerate.h */
int random_item_lookup(item_hash_t **dst, item_hash_t *src, int num_iters)
{
    item_hash_t *current = NULL;
    item_hash_t *tmp = NULL;

    int i = 0;

    HASH_ITER(hh, src, current, tmp) {
        if (i == num_iters) {
            copy_item_to_hash(dst, src, current->item_id);
            return SUCCESS;
        }
        i++;
    }

    return FAILURE;
}


/* See autogenerate.h */
item_hash_t *generate_items(roomspec_t *rspec)
{
    if (rspec == NULL) {
        return NULL;
    }

    int total_count = 0;
    item_t *curr, *tmp;
    item_hash_t *new_items = NULL;
    HASH_ITER(hh, rspec->items, curr, tmp) {
        if (total_count == MAX_RAND_ITEMS)
            break;

        /*
        Default values are set to 1 to mimic the behavior of random_items 
        (the previous item generation function that was called by roomspec_to_room);
        random_items spawns 1 instance of each item specified in the roomspec item hash. 
         
        Note that the behavior is still slightly different: 
        random_items() picks a random subset of the item hash, while generate_items 
        iterates through the item hash and picks items in a consistent order.
        */
        double spawn_chance = 1;
        unsigned int max_num = 1; // the max possible item spawn quantity
        unsigned int min_num = 1; // the min possible item spawn quantity 

        itemspec_t *itemspec;
        HASH_FIND_STR(rspec->itemspecs, curr->item_id, itemspec);
        if (itemspec) {
            spawn_chance = itemspec->spawn_chance;
            max_num = itemspec->max_num; 
            min_num = itemspec->min_num;
        }
        /*
        Computes the number of possible item spawn quantities;
        e.g. [2, 4] has 4 - 2 + 1 = 3 possible values: 2, 3, and 4.
        */
        int num_quantities = max_num - min_num + 1;

        int spawn_num = min_num;
        if ((((double) rand()) / RAND_MAX) <= spawn_chance) {
            spawn_num += rand() % num_quantities;
        } else {
            spawn_num = 0;
        }
        spawn_num = (spawn_num < (MAX_RAND_ITEMS - total_count)) ? 
                     spawn_num : (MAX_RAND_ITEMS - total_count);

        for (int i = 0; i < spawn_num; i++) {
            copy_item_to_hash(&new_items, rspec->items, curr->item_id);
        }
        total_count += spawn_num; 
    }

    return new_items;
}



/* See autogenerate.h */
int map_level_to_difficulty(int num_thresholds, int *thresholds, int player_level)
{   
    /* Iterate from start (lowest point) of threshold array... */
    for (int i = 0; i < num_thresholds; i++) {
        /* ...to find the first or minimum threshold which exceeds the given player level: */
        if (player_level < thresholds[i]) {
            /* Player lvl must be in difficulty level directly below it (-1)... */
            return (i - 1);
        }
    }
    /* ...OR equal/exceeding the max threshold, in which case print max difficulty: */
    return num_thresholds - 1; // -1 to convert array len -> max index
}


/* See autogenerate.h */
int roomspec_is_given_difficulty(roomlevel_hash_t **roomlevels, 
                                 roomspec_t *roomspec, 
                                 int difficulty_level)
{
    roomlevel_t *elt;

    HASH_FIND_STR(*roomlevels, roomspec->room_name, elt); 
    if (elt) {
        if (elt->difficulty_level == difficulty_level) {
            return SUCCESS;
        } else {
            return 1; // roomspec found but not of given difficulty level
        }
    }
    return 2; // roomspec not found
}


/* See autogenerate.h */
/*specgraph_t* filter_specgraph_with_difficulty(specgraph_t *specgraph, 
                                            roomlevel_hash_t **roomlevels, 
                                            int difficulty_level)
{    
    specgraph_t *curr, *tmp;
    specgraph_t *filtered_specgraph = NULL;

    DL_FOREACH_SAFE(specgraph, curr, tmp) { 
        int is_given_difficulty = roomspec_is_given_difficulty(roomlevels, 
                                                               curr->spec, 
                                                               difficulty_level);
        if (is_given_difficulty == SUCCESS) {
            // Create a copy of the node to add to the filtered specgraph output. 
            //This resolves an earlier issue in which it was removing nodes from the unfiltered specgraph
            //a node cannot exist in two lists simultaneously. 
            specgraph_t *curr_copy = specgraph_new(curr->spec); 
            DL_APPEND(filtered_specgraph, curr_copy);    
        }
    }

    return filtered_specgraph;
}*/

/* See autogenerate.h */
/*int multi_room_level_generate(game_t *game, gencontext_t *context, 
                              char *room_id, int num_rooms,
                              levelspec_t *levelspec)
{
    // If there are no roomspec_t elements in specgraph, then do not autogenerate 
    if (specgraph == NULL) {
        return FAILURE;
    }

    // compute the difficulty corresponding to player level 
    int difficulty_level = map_level_to_difficulty(levelspec->num_thresholds,
                                                   levelspec->thresholds,
                                                   context->level);

    // filter the given specgraph according to difficulty 
    specgraph_t *filtered_specgraph = filter_specgraph_with_difficulty(context->specgraph,
                                                                    &(levelspec->roomlevels), 
                                                                    difficulty_level);

    // filtered gencontext 
    gencontext_t* filtered_context = gencontext_new(context->open_paths,
                                                    context->level,
                                                    context->num_open_paths,
                                                    filtered_specgraph);

    int result = multi_room_generate(game, filtered_context, room_id, num_rooms); 
    specgraph_free(filtered_specgraph);

    return result;
}*/



