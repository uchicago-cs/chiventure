/* Team RPG-Openworld
*
* Sample-Generation header file
*
* sample_generation.h: This file: function prototypes and purposes from
* the functions defined in chiventure/src/openworld/src/autogenerate.c
*
* Room module that autogenerates and adds room to a game when a "dead end"
* is reached (i.e. no outward paths from the current room)
*
* See sample_generation.c source code file to see function definitions
*/

#ifndef INCLUDE_AUTOGENERATE_H
#define INCLUDE_AUTOGENERATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game-state/game.h"
#include "gen_structs.h"
#include "default_rooms.h"

#define MAX_RAND_ITEMS (100)

/*
* path_exists_in_direction
* Is there any path in the given room that exists in the given direction?
* Return a boolean.
*
* parameters:
* - r: A room pointer for the input room. Should not be NULL.
* - direction: A string specifying the direction to check for
*              ("NORTH", "EAST", SOUTH", or "WEST")
*
* returns:
* - true if the room has a path with in the given direction
* - false if the room has no paths in the give direction
*/
bool path_exists_in_direction(room_t *r, char *direction);


/*
* roomspec_to_room
* Given a roomspec_t pointer (type roomspec_t*), returns
* a room_t pointer generated from its specifications, with a room_id that
* is uniquely generated from the given game (different from the game's rooms).
*
* Increments the num_built field of the given roomspec by 1
*
* parameters:
* - roomspec: A pointer to a roomspec_t (type gencontext_t*). Should not be NULL.
*
* returns:
* The generated room_t struct pointer.
*/
room_t* roomspec_to_room(roomspec_t *roomspec);


/** pick_random_direction
 * Picks random OPEN NESW (compass) direction around given room 
 * (open as in not filled with a path).
 * 
 * parameters:
 * - curr: pointer to a room. not NULL.
 * - out_direction_to_new: Random direction going OUT FROM curr. Outparameter.
 *                   Array must have enough space for any NESW direction. 
 * - out_direction_to_curr: Random direction going INTO curr. Outparameter.
 *                    Array must have enough space for any NESW direction. 
 * 
 * side effects:
 * - copies the forward-reverse pair of directions to the outparameter.
 * 
 * returns:
 * - SUCCESS: if an open direction is available
 * - FAILURE: otherwise
 */
int pick_random_direction(room_t *curr, char *out_direction_to_curr, char *out_direction_to_new);

/** room_generate
 * Generates a room based on the given roomspec and adds it to the game.
 * This new room will be attached at a given direction from a given 'curr' room. 
 * 
 * parameters:
 * - game: A pointer to a game struct. Should not be NULL.
 * - curr: A pointer to the room_t with which the newly generated room will be connected.
 *         Must be in the game->all_rooms hash. Should not be NULL.
 * - rspec_new: A roomspec for the to-be-generated room.
 * - direction_to_curr: Direction for path new -> curr. Should not be NULL.
 * - direction_to_new: Direction for path curr -> new. Should not be NULL
 *                     NOTE: MUST BE AN AVAILABLE DIRECTION!
 *                     (Available as in no path for that direction exists.)
 * 
 * side effects:
 * - Changes input game to hold the newly generated room. Allocated on the heap
 * 
 * returns:
 * - Always returns SUCCESS
 *   Any internal failure results in crash (by triggering an assert).
 */
int room_generate(game_t *game, room_t *curr, roomspec_t *rspec_new, 
                  char *direction_to_curr, char *direction_to_new);

/* roomspec_autogenerate
 * Given a roomspec, generates a new roomspec based on the adjacency matrix
 * that quantifies the similarity between different roomspecs.
 *
 * Parameters:
 * - context: A pointer to a gencontext_t (type gencontext_t*). Should not be NULL.
 * - roomspec: The roomspec of the current room 
 *
 *
 * returns:
 * - Returns a pointer to the newly generated roomspec
 */

roomspec_t* roomspec_autogenerate(gencontext_t *context, roomspec_t *roomspec);

/* room_autogenerate
 * Creates a room directly north, south, east, or west of a given room. 
 * The roomspec of the newly created room will be chosen using roomspec_autogenerate
 *
 * Parameters:
 * - game: A pointer to a game struct. Should not be NULL.
 * - context: A pointer to a gencontext_t (type gencontext_t*). Should not be NULL.
 * - curr: A pointer to the room_t with which the newly generated room will be connected.         
 *         Must be in the game->all_rooms hash. Should not be NULL.
 * - roomspec: The roomspec of the current room 
 * - direction_to_curr: Direction for the path from new -> curr. Should not be NULL.
 * - direction_to_new: Direction for the path from curr -> new. Should not be NULL.
 *   NOTE: MUST BE AN AVAILABLE DIRECTION! (Available as in no path for that direction exists.)
 *
 * * side effects:
 * - Changes input game to hold the newly generated room. Allocated on the heap.

 * returns:
 * - Always returns SUCCESS 
 *   Any internal failure results in crash (by triggering an assert).
 */

int room_autogenerate(game_t *game, gencontext_t *context, room_t *curr, roomspec_t *roomspec, 
                      char *direction_to_curr, char *direction_to_new);

/*
* multi_room_generate
* Iterate through all the rooms of the specgraph field of the given context
* (gencontext_t pointer) and create a "domain" of rooms around the current
* room. Only succeeds when the current room has no outward paths, i.e. is
* a "dead end".
*
* Connects the newly-generated room to the old room via paths.
*
* parameters:
* - game: A pointer to a game struct. Should not be NULL.
* - context: A pointer to a gencontext_t (type gencontext_t*). Should not be NULL.
* - room_id: A unique room_id string for the to-be-generated room.i
* - num_rooms: specifies how many new rooms will be generated
*
* side effects:
* - Changes input game to hold the newly generated room(s). Allocated on the heap
*
* returns:
* - SUCCESS if the new rooms were generated and added (SUCCESS)
* - FAILURE if the new rooms were not generated/added (FAILURE)
*/
int multi_room_generate(game_t *game, gencontext_t *context, char *room_id, int num_rooms);

/*
* random_room_lookup
* Iterate through all the roomspec of the specgraph a "random" number of times
* and returns one of these roomspecs.
*
* parameters:
* - specgraph_t *spec: the specgraph from which to pull a roomspec
*
* returns:
* - NULL if failure
* - roomspec_t* new roomspec from the specgraph
*/
roomspec_t *random_room_lookup(specgraph_t *spec);

/*
* random_items
* Adds 0-6 "random" items to the roomspec given. Uses the roomspec's
* allowed items hash to pull the acceptable items.
*
* parameters:
* - room: A single roomspec with a item_hash of ALL allowed items.
*
* returns:
* - NULL if failure
* - item_hash_t* new item hash
*/
item_hash_t *random_items(roomspec_t *room);

/*
* random_item_lookup
* Iterate through the src item hash table num_iters times and copy that
* item to the dst item hash. This is a helper function for random_items.
*
* parameters:
* - item_hash_t *dst is where you want to store the item you just found
* - item_hash_t *src is where you're looking up the item
* - num_iters is how many times you'll iterate through src to settle on an item.
*
* returns:
* - SUCCESS if items allowed in a room could be found (SUCCESS)
* - FAILURE if items allowed in a room could not be found (FAILURE)
*/
int random_item_lookup(item_hash_t **dst, item_hash_t *src, int num_iters);


/* generate_items
 * Generates an item hash according to the item_hash and itemspec_hash 
 * specified in in the given roomspec.
 * 
 * If the corresponding itemspec for an item is not defined,
 * generate_items resorts to default behavior: 
 * generate 1 item with 100% probability
 * 
 * parameter:
 * - rspec: A single roomspec.
 * 
 * returns:
 * - NULL if failure 
 *   (or if item_hash is empty,
 *    or if generate_items() decided not to spawn items,
 *    or if item_spec specified that no items should be added)
 * - item_hash_t* new item hash
 */
item_hash_t *generate_items(roomspec_t *rspec);



/* map_level_to_difficulty
 * Map from player level to difficulty level
 * 
 * Parameters:
 * - num_thresholds: the number of player level thresholds
 * - thresholds: an array of player level thresholds (see gen_structs.h for details)
 * - player_level: the player level
 * 
 * Returns:
 * - difficulty level corresponding to player level
 */
int map_level_to_difficulty(int num_thresholds, int *thresholds, int player_level);


/* roomspec_is_given_difficulty
 * Evaluates if the given roomspec is of the difficulty level
 * 
 * Parameters:
 * - roomlevels: pointer to the hash table of rooms
 * - roomspec: pointer to the roomspec to be evaluated
 * - int difficulty_level: difficulty_level
 *
 * Returns:
 *  - SUCCESS (0) if the given roomspec is of the difficulty level
 *  - 1 if the given roomspec is found but not of the difficulty level
 *  - 2 if the given roomspec is not found
 */
int roomspec_is_given_difficulty(roomlevel_hash_t **roomlevels, 
                                 roomspec_t *roomspec, 
                                 int difficulty_level);


/* filter_specgraph_with_difficulty
 * Creates a specgraph by filtering the given specgraph with a difficulty level
 * so that the returned specgraph only contains roomspecs of the given level
 * 
 * Notes:
 * - original specgraph is unaltered
 * - filtered specgraph uses roomspec pointers of original specgraph
 *   (in other words, no new roomspecs are declared/initialized)
 *
 * Parameters:
 * - specgraph: pointer to the specgraph we want to filter
 * - roomlevels: pointer to the hash table for room levels
 * - difficulty_level: the difficulty level
 * 
 * Returns:
 * - pointer to the filtered specgraph, NULL if no spec matches the level
 */
specgraph_t* filter_specgraph_with_difficulty(specgraph_t *specgraph, 
                                            roomlevel_hash_t **roomlevels, 
                                            int difficulty_level);


/* multi_room_level_generate
 * Level-oriented version of multi_room_generate.
 *
 * Parameters:
 * - game: pointer to a game struct. Should not be NULL.
 * - context: pointer to a gencontext_t (type gencontext_t*). Should not be NULL.
 * - room_id: a unique room_id string for the to-be-generated room.i
 * - num_rooms: specifies how many new rooms will be generated
 * - levelspec: pointer to a levelspec_t; contains info needed for level-oriented generation
 *
 * Side effects:
 * - Changes input game to hold the newly generated room(s),
 *   allocated on the heap
 *
 * Returns:
 * - SUCCESS if the new rooms were generated and added (SUCCESS)
 * - FAILURE if the new rooms were not generated/added (FAILURE)
 */
int multi_room_level_generate(game_t *game, gencontext_t *context, 
                              char *room_id, int num_rooms,
                              levelspec_t *levelspec);



/* recursive_generate
 * For a given radius n, generates rooms in a branchwise-fashion up to
 * 'n' paths away from the curr_room, also the 'pivot'
 *      pivot: the room around which more rooms will be generated
 *      branchwise: 1) for each pivot, we fill as many paths/branches around it with new rooms
 *                  (we specify which paths we fill using the directions parameter)
 *                  2) branches are disjoint from each other; we can cross from one branch to another
 *                  only by travelling through the pivot
 * 
 * Parameters:
 * - game: pointer to a game struct. Should not be NULL
 * - room_t *curr_room: pointer to the room to serve as the pivot
 * - gencontex_t *context: pointer to a gencontext. Should not be NULL.
 * - int radius: the max number of paths away from the current pivot that we wish to generate
 * - directions: an array of directions we wish to generate around each pivot
 *               (must be a subset of the default six: "NORTH", "EAST", "SOUTH", "WEST", "UP", "DOWN")
 * - num_directions: array length of directions, i.e. number of directions
 * - direction_to_parent: direction to the parent pivot. Should not be NULL.
 *       parent pivot: the room from which the current room was generated; when we call
 *       recursive_generate manually, the original room has no parent pivot, 
 *       i.e. its direction_to_parent == ""
 * 
 * Side effects:
 * - Changes input game to hold the newly generated room(s), allocated on the heap
 *
 * Returns:
 * Always returns SUCCESS.
 */
int recursive_generate(game_t *game, gencontext_t *context, room_t *curr_room,
                       int radius, char **directions, int num_directions, char *direction_to_parent);
                               
#endif /* INCLUDE_AUTOGENERATE_H */


